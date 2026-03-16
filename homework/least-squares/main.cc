#include<iostream>
#include<vector>
#include<string>
#include"../packages/matrix_QR.h"
#include<tuple>
#include"lsfit.h"


int main(){
    pp::vector time = {1.0,2.0,3.0,4.0,6.0,9.0,10.0,13.0,15.0};
    pp::vector activity = {117.0,100.0,88.0,72.0,53.0,29.5,25.5,15.2,11.1};
    pp::vector uncertainty = {6,5,4,4,4,3,3,2,2};
    pp::vector lnactivity = activity.map([](double x) {return std::log(x);});
    pp::vector lnuncertainty(uncertainty.size());
    for (int i=0;i<uncertainty.size();i++){
        lnuncertainty[i]=uncertainty[i]/activity[i]; 
    }
  
    std::vector<std::function<double(double)>> fs {
	[](double z) { return 1.0;},
	[](double z) { return -z;},
	};


    
    pp::lsfit fit = pp::lsfit(fs,time,lnactivity,lnuncertainty);
    pp::vector c = fit.coefficients;
    
    pp::matrix SIGMA = fit.covariance();
    pp::vector y_model(time.size());
    pp::vector y_lower(time.size());
    pp::vector y_upper(time.size());
    c.print("C");
    SIGMA.print("SIGMA");
    
    for (int i=0;i<y_model.size();i++) {
        y_model[i]=c[0]-c[1]*time[i];
        double dc0 = std::sqrt(SIGMA[0,0]);
        double dc1 = std::sqrt(SIGMA[1,1]);
        // Low intercept, high slope
        y_lower[i]=(c[0]+dc0)-(c[1]-dc1)*time[i];
        // High intercept, low slope
        y_upper[i]=(c[0]-dc0)-(c[1]+dc1)*time[i];
    }

    
    double halftime = std::log(2)/c[1];
    c.print("Coefficients");
    std::cout<< "Measured halftime is: " << halftime << "Days. Actual value: 3.632 Days" ; 


    //output for plotting
    
    std::cout<< "\n\n\n"; // GNU block
    for (int i=0;i<time.size();i++){
        std::cout << time[i] << " " << lnactivity[i] << " "<< lnuncertainty[i] <<"\n" ; // Raw values
    }

    std::cout<< "\n\n\n"; // GNU block
    for (int i=0;i<time.size();i++){
        std::cout << time[i] << " " << y_model[i] << " " 
        << y_lower[i] << " " << y_upper[i] << "\n"; // Fitted values
    } 


    std::cout<< "\n\n\n"; // GNU block
    for (int i=0;i<time.size();i++){
        std::cout << time[i] << " " << activity[i] << " "<< uncertainty[i] <<"\n" ; // Raw values
    }

    std::cout<< "\n\n\n"; // GNU block
    for (int i=0;i<time.size();i++){
        std::cout << time[i] << " " << std::exp(y_model[i]) << " " 
        << std::exp(y_lower[i]) << " " << std::exp(y_upper[i]) << "\n"; // Fitted values
    } 

    

    

    
return 0;
}