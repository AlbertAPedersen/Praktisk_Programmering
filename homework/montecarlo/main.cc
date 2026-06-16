#include<iostream>
#include<vector>
#include<tuple>
#include"montecarlo.h"
#include"../packages/matrix_QR.h"
#include<cmath>
#include<functional>
#include<cstdlib>


const double PI = 3.141592653589793238;

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


//TASK B

std::function<double(const std::vector<double>&)> integral = [](const std::vector<double>& x){

const double& x0 = x[0]*PI;
const double& x1 = x[1]*PI;
const double& x2 = x[2]*PI;

double denom = (1-std::cos(x0)*std::cos(x1)*std::cos(x2)); 
if (std::abs(denom) < 1e-12) {
    return 0.0;
}


return 1.0/denom;
};

const double res_B = 1.3932039296856768591842462603255;

//Error estimate function (non singular)


// 3. The smooth test function lambda
auto test_func = [](const std::vector<double>& x) -> double {
//f=x^2+y*z, integrates from bounds [0,1] [0,2] [0,3] to 13.0.
    return (x[0] * x[0]) + (x[1] * x[2]);
};
double test_value = 11.0; 






int main(){
    double PI = 3.14159265359;
    long long seed = 24;
    pp::lcg RNG = pp::lcg(seed);

    std::vector<double> a = {-1.0,-1.0};
    std::vector<double> b = {1.0,1.0};

//even distribution on 1/sqrt(N):
int K = 100;
double x_min = 1 / std::sqrt(100000.0);
double x_max = 1 / std::sqrt(100.0);

for (int k = 0; k < K; ++k) {
    double x = x_min + k * (x_max - x_min) / (K - 1);
    int N = static_cast<int>(std::round(1.0 / (x*x)));

    auto area = pp::plainmc(circle, a, b, static_cast<int>(N), RNG, 0);
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


auto area = pp::plainmc(ellipsoid, a, b, static_cast<int>(N), RNG,0);
std::cout << "N: " << N 
            << " Area :"<< area[0]
            << " Estimated error: " << area[1]
            <<" Actual error: " << std::abs(area[0]-area_true) << "\n";

//TASK B
std::cout << "\n\n";

pp::halton h; // Initialize struct


a = {0,0,0};
b= {1,1,1};


for (int N = 100; N < 100000; N*=1.2) {
    std::vector<std::vector<double>> halton_seq = h.sequence(3,N);
    auto quasi_result = pp::quasimc(integral, a, b, halton_seq);
    auto plain_result = pp::plainmc(integral, a, b, static_cast<int>(N), RNG, 0);
    std::cout << 1.0 / std::sqrt(N) << " " 
              << quasi_result[0] << " " 
              << std::abs(quasi_result[0]-res_B)/res_B << " " 
              << plain_result[0] << " " 
              << std::abs(plain_result[0]-res_B)/res_B << "\n";
}

std::cout << "\n\n";

a = {0,0,0};
b= {1,2,3};

for (int N = 100; N < 100000; N*=1.2) {

    std::vector<std::vector<double>> halton_seq = h.sequence(3,N);
    auto quasi_result = pp::quasimc(test_func, a, b, halton_seq);
    auto plain_result = pp::plainmc(test_func, a, b, static_cast<int>(N), RNG, 0);
    auto C_RNG_result = pp::plainmc(test_func, a, b, static_cast<int>(N), RNG, 1);

    std::cout << 1.0 / std::sqrt(N) << " " 
              << std::abs(quasi_result[0]-test_value)/test_value << " " 
              << std::abs(plain_result[0]-test_value)/test_value << " "
              << std::abs(C_RNG_result [0]-test_value)/test_value << "\n";

}

    return 0;
}

