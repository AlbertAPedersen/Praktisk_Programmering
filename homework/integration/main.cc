#include<iostream>
#include<vector>
#include<tuple>
#include"integrate.h"
#include"../packages/matrix_QR.h"
#include<cmath>
#include<functional>

// TASK A

int ncalls=0;
double acc=0.001;
double eps=0.001;
double PI = 3.1415926535897932384626433;
std::function<double(double)> fA_1= [](double x){
    ncalls+=1;
    return std::sqrt(x);
};

std::function<double(double)> fA_2 = [](double x){
    ncalls+=1;
    return 1/std::sqrt(x);
};

std::function<double(double)> fA_3 = [](double x){
    ncalls+=1;
    return std::sqrt(1-x*x);
};

std::function<double(double)> fA_4 = [](double x){
    ncalls+=1;
    return std::log(x)/std::sqrt(x);
};


std::function<double(double)> erfx = [](double x){
    ncalls+=1;
    if (x<0) return -erfx(-x);

    if (x<=1){
        auto f_small = [](double x){return std::exp(-x*x);};
        return (2.0 / std::sqrt(PI)) * pp::integrate(f_small, 0.0, x, acc, eps);
    }
    else{
        auto f_large = [x](double t){
            if (t==0) return 0.0;
            double exponent = -(x+(1.0-t)/t)*(x+(1.0-t)/t);
            return std::exp(exponent)/(t*t);
        };
        return 1.0-2.0/std::sqrt(PI)*pp::integrate(f_large,0,1, acc, eps);
    }
};



//TASK B
std::function<double(double)> fB_1 = [](double x){
  ncalls+=1;
  return 1/std::sqrt(x);
};

std::function<double(double)> fB_2 = [](double x){
  ncalls+=1;
  return std::log(x)/std::sqrt(x);
};



int main(){

    ncalls=0;
    acc=0.0001;
    eps=0.0001;
    double Q_A1=pp::integrate(fA_1, 0,1, acc, eps);
    std::cout << "Number of calls: " << ncalls << " integral value A_1: " << Q_A1 << "\n";

    ncalls=0;
    double Q_A2=pp::integrate(fA_2,0,1, acc, eps);
    std::cout << "Number of calls: " << ncalls << " integral value A_2: " << Q_A2 << "\n";

    ncalls=0;
    double Q_A3=pp::integrate(fA_3,0,1, acc, eps);
    std::cout << "Number of calls: " << ncalls << " integral value A_3: " << Q_A3 << "\n";

    ncalls=0;
    double Q_A4=pp::integrate(fA_4,0,1, acc, eps);
    std::cout << "Number of calls: " << ncalls << " integral value A_4: " << Q_A4 << "\n";
  

    //GNU block
    std::cout << "\n \n";

    //ERF task
    double erf_1_tab =  0.84270079294971486934;
    for (int i=1; i<16; i++){
        double a = std::pow(10,i);
        eps=0.0;
        acc=1.0/a;
        double erf_1 = erfx(1);
        double diff = std::abs(erf_1-erf_1_tab);
        std::cout << std::fixed << std::setprecision(18) << acc << " " << diff<< "\n";
    }

    //GNU block
    std::cout << "\n \n";
//TASK B
double a=0;
double b=1;
    eps=0.000001;
    acc=0.000001;
    ncalls=0;
    double QB_1 = pp::CC_integrate(fB_1,a,b,acc,eps);
    ncalls=0;
    double QB_2 = pp::CC_integrate(fB_2,a,b,acc,eps);
    std::cout << "Number of calls: " << ncalls << " integral value B_1: " << QB_1 << "\n";
    std::cout << "Number of calls: " << ncalls << " integral value B_2: " << QB_2 << "\n";
    
    return 0;
}