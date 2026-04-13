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
        return (2.0 / std::sqrt(PI)) * pp::integrate(f_small, 0.0, x, acc, eps)[0];
    }
    else{
        auto f_large = [x](double t){
            if (t==0) return 0.0;
            double exponent = -(x+(1.0-t)/t)*(x+(1.0-t)/t);
            return std::exp(exponent)/(t*t);
        };
        return 1.0-2.0/std::sqrt(PI)*pp::integrate(f_large,0,1, acc, eps)[0];
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

//Infinite convergence
std::function<double(double)> gauss = [](double x){
  ncalls+=1;
  return std::exp(-x*x);
};

//TASK C - difficult functions
std::function<double(double)> fC_1 = [](double x){
  ncalls+=1;
  return std::sin(std::pow(x,10));
};

std::function<double(double)> fC_2 = [](double x){
  ncalls+=1;
  return std::sin(1/x);
};

std::function<double(double)> fC_3 = [](double x){
  ncalls+=1;
  return std::sin(10000/(x));
};


int main(){
    std::cout << "TASK A\n";

    ncalls=0;
    acc=0.0001;
    eps=0.0001;
    double Q_A1=pp::integrate(fA_1, 0,1, acc, eps)[0];
    std::cout << "Number of calls: " << ncalls << " integral value A_1: " << Q_A1 << "\n";

    ncalls=0;
    double Q_A2=pp::integrate(fA_2,0,1, acc, eps)[0];
    std::cout << "Number of calls: " << ncalls << " integral value A_2: " << Q_A2 << "\n";

    ncalls=0;
    double Q_A3=pp::integrate(fA_3,0,1, acc, eps)[0];
    std::cout << "Number of calls: " << ncalls << " integral value A_3: " << Q_A3 << "\n";

    ncalls=0;
    double Q_A4=pp::integrate(fA_4,0,1, acc, eps)[0];
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
    std::cout << "\n \n TASK B\n";
    //TASK B
    double a=0;
    double b=1;
    eps=1e-10;
    acc=1e-10;
    ncalls=0;
    double QB_1 = pp::CC_integrate(fB_1,a,b,acc,eps)[0];
    ncalls=0;
    double QB_2 = pp::CC_integrate(fB_2,a,b,acc,eps)[0];
    std::cout << "Number of calls: " << ncalls << " integral value B_1: " << QB_1 << "\n";
    std::cout << "Number of calls: " << ncalls << " integral value B_2: " << QB_2 << "\n";


    // infinite tests
    std::cout << "\n \n TASK B INFINITE\n";
    ncalls=0;
    double Gauss1 = pp::CC_integrate(gauss,-INFINITY,INFINITY,acc,eps)[0];
    ncalls=0;
    double Gauss2 = pp::CC_integrate(gauss,0,INFINITY,acc,eps)[0];
    ncalls=0;
    double Gauss3 = pp::CC_integrate(gauss,-INFINITY,0,acc,eps)[0];
    std::cout << "INF B, a=0: Gaussian: " << Gauss2 << " Number of calls: " << ncalls << "\n" 
              << "INF A, b=0: Gaussian: " << Gauss3 <<  " Number of calls: " << ncalls <<"\n"
              << "INF A & B: Gaussian: " << Gauss1 << " Number of calls: " << ncalls << " Error compared to analytical: "<< std::abs(std::sqrt(PI)-Gauss1)<< "\n"
              << "Python quad with same acc and eps with -INF to INF gave 390 calls with 2e-16 error \n";

    //GNU block
    std::cout << "\n \n TASK C\n";
    //TASK C
    eps=1e-7;
    acc=1e-7;

    pp::vector C1 = pp::CC_integrate(fC_1,-4,4,acc,eps);
    double C1_python = 0.17138676205825268;
    double diff_C1 = std::abs(C1[0]-C1_python);
    std::cout << "sin(x^10) from -4 to 4, eps,acc=1e7: " << C1[0] << " +- " << C1[1]
              << "\n Actual error compared to value from scipy.quad: " << diff_C1<< "\n\n";


    pp::vector C2 = pp::CC_integrate(fC_2,0,1,acc,eps);
    double C2_python = 0.5024347471020827;
    double diff_C2 = std::abs(C2[0]-C2_python);
    std::cout << "sin(1/x) from 0 to 1, eps,acc=1e7: " << C2[0] << " +- " << C2[1]
              << "\n Actual error compared to value from scipy.quad: " << diff_C2<< "\n\n";

    pp::vector C3 = pp::CC_integrate(fC_3,0,1,acc,eps);
    double C3_python = -0.08023582237622202;
    double diff_C3 = std::abs(C3[0]-C3_python);
    std::cout << "sin(10000/x) from 0 to 1, eps,acc=1e7: " << C3[0] << " +- " << C3[1]
              << "\n Actual error compared to value from scipy.quad: " << diff_C3<< "\n";
    

    return 0;
}