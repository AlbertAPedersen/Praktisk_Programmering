#include<iostream>
#include<iomanip>
#include<cmath>
#include"sfuns.h"
#include <numbers>

int main(){
    const double e  = std::numbers::e;
    const double pi = std::numbers::pi;

    std::cout << "Task 1:" << "\n";
    std::cout << "sqrt(2)=" << std::sqrt(2.0) << "\n"
              << "2^(1/5)=" << std::pow(2.0,1.0/5.0) << "\n"
              << "e^(pi)=" << std::pow(e,pi) << "\n"
              << "pi^e=" << std::pow(pi,e) << "\n";

    std::cout << "Task 2:" << "\n";
    for (int x = 0; x<11; x++){

        double y = sfuns::fgamma(x);
        std::cout << std::setprecision(6);
        std::cout
        <<"sfuns::fgamma(" << x << ")=" 
        << std::left << std::setw(12) << y

        << "std::tgamma("<< x << ")="   
        << std::left << std::setw(12) << std::tgamma(x)
        << "\n";
      

    }
    std::cout << "Task 3:" << "\n";
    for (int x = 0; x<11; x++){

        double y = sfuns::lngamma(x);
        std::cout << std::setprecision(6);
        std::cout
        <<"sfuns::lngamma(" << x << ")=" 
        << std::left << std::setw(12) << y

        << "std::lgamma("<< x << ")="   
        << std::left << std::setw(12) << std::lgamma(x)
        << "\n";
      

    }






        
    return 0;
}