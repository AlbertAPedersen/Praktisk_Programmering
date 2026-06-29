#include<iostream>
#include<vector>
#include<tuple>
#include"ode.h"
#include"../homework/packages/matrix_QR.h"
#include<cmath>
#include<functional>

// TASK A

/*
For the function u''=-u:
y0=f
y1=f'
The derivative is thus
y0'=y1
y1'=-y0
*/
std::function<pp::vector(double,pp::vector)> harmonic= [](double x, pp::vector y){
    double dy0 = y[1];
    double dy1 = -y[0];
    pp::vector dy = pp::vector{dy0,dy1};
    return dy;
};

std::function<pp::vector(double)> analytical_harmonic = [](double x){
    double dy0 = sin(x);
    double dy1 = cos(x);
    pp::vector dy = pp::vector{dy0,dy1};
    return dy;
};


void output(std::function<pp::vector(double,pp::vector)> f,
    double a, double b, double hinit,
    pp::vector yinit,
    bool two_step,
    bool correction_status,
    double acc,
    double eps
){
    pp::matrix result = pp::ode::driver(f,a,b,yinit,two_step,correction_status,hinit,acc,eps); //twostep with correction
    double resid=0;
    double resid_weighted=0;
    for (int i=0; i<result.size1();i++){
        double& x = result[i,0];
        double& y = result[i,1];
        double analytic = analytical_harmonic(x)[0];
        resid+= (y-analytic)*(y-analytic);
        resid_weighted+= (y-analytic)*(y-analytic)/(static_cast<double>(result.size1()+1));
     
        std::cout << x << " " << y << " " << analytic << " " 
                  << resid << " " <<  resid_weighted << " "
                  << analytic-y << "\n";    
    }
    if(!two_step){
    std::cerr << "Onestep (cubic Heun) method used " << result.size1() << " Iterations to solve ODE\n";
    }
    if(two_step){
        if (correction_status){
            std::cerr << "Corrected twostep method used " << result.size1() << " Iterations to solve ODE\n";
        }
        if (!correction_status){
            std::cerr << "Uncorrected twostep method used " << result.size1() << " Iterations to solve ODE\n";
        }
    }
    std::cout << "\n\n";
}



int main(){
    double a=0;
    double b=10;
    pp::vector yinit = pp::vector{0,1};
    double hinit=0.001;
    double acc=0.001;
    double eps=0.001;
    bool two_step = true;
    bool correction_status = false;

    // NOTE: The ODE driver outputs a matrix with columns x,y0,y1
    output(harmonic,a,b,hinit,yinit,two_step,correction_status,acc,eps);

    correction_status=true;
    output(harmonic,a,b,hinit,yinit,two_step,correction_status,acc,eps);
    two_step=0;
    output(harmonic,a,b,hinit,yinit,two_step,correction_status,acc,eps);


    return 0;
}