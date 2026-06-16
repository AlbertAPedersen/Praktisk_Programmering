#include<iostream>
#include<vector>
#include<tuple>
#include"montecarlo.h"
#include"../packages/matrix_QR.h"
#include<cmath>
#include<functional>

// TASK A
std::function<double(const std::vector<double>&)> circle = [](const std::vector<double>& x){
//x^2+y^2=r^2 with r being the bound
double x0 = x[0];
double x1 = x[1];
if (x0*x0+x1*x1 <= 1) return 1;
else return 0;
};

std::function<double(const std::vector<double>&)> ellipsoid = [](const std::vector<double>& x){
//x^2+y^2=r^2 with r being the bound
double a=1;
double b=2;
double c=3;
const double& x0 = x[0];
const double& x1 = x[1];
const double& x2 = x[2];
const double& val = x0*x0/(a*a)+x1*x1/(b*b)+x2*x2/(c*c);
if (val<=1) return 1;
else return 0;
};



int main(){
    double PI = 3.14159265359;
    long long seed = 3;
    pp::lcg RNG = pp::lcg(seed);

    std::vector<double> a = {-1.0,-1.0};
    std::vector<double> b = {1.0,1.0};

for (double N = 10; N <= 10000; N *= 1.4) {
    auto area = pp::plainmc(circle, a, b, static_cast<int>(N), RNG);
    std::cout << 1.0 / std::sqrt(N) << " " 
              << area[0] << " " 
              << area[1] << " " 
              << std::abs(area[0] - PI) << "\n";
}

//GNU BLOCK
std::cout << "\n\n Ellipsoid\n";
//ELLIPSOID
double area_true = 4.0/3.0*PI*1*2*3;
a = {-1.0,-2.0,-3.0};
b = {1.0,2.0,3.0};
long long N=1000000;


auto area = pp::plainmc(ellipsoid, a, b, static_cast<int>(N), RNG);
std::cout << "N: " << N 
            << " Area :"<< area[0]
            << " Estimated error: " << area[1]
            <<" Actual error: " << std::abs(area[0]-area_true) << "\n";

//TASK B
std::cout << "\n\n";

pp::halton test = pp::halton();

auto A = test.sequence(3,10);

    return 0;
}

