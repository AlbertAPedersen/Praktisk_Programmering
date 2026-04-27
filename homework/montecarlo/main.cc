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

std::function<double(const std::vector<double>&)> circle = [](const std::vector<double>& x){
//x^2+y^2=r^2 with r being the bound
double x0 = x[0];
double x1 = x[1];
double x2 = x[2];
if (x0*x0+x1*x1 <= 1) return 1;
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

    return 0;
}