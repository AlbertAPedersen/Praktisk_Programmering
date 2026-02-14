#include<cmath>
#include<numbers> // c++20
#include"sfuns.h"
#include<limits>
namespace sfuns{
constexpr double PI = std::numbers::pi; // c++20
// constexpr double PI = 3.14159265358979323846; // pre- c++20
double fgamma(double x){
	if(x<0)return PI/std::sin(PI*x)/fgamma(1-x);
	if(x<9)return fgamma(x+1)/x;
	double lnfgamma=x*std::log(x+1/(12*x-1/x/10))-x+std::log(2*PI/x)/2;
	return std::exp(lnfgamma);
	}


double lngamma(double x){
	constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
	if(x <= 0) return NaN; // Not-a-Number
	if(x<9)return lngamma(x+1)-std::log(x);
	double lnfgamma=x*std::log(x+1/(12*x-1/x/10))-x+std::log(2*PI/x)/2;
	return lnfgamma;
	} 
 bool approx(double a, double b, double acc, double eps) {
    double diff = std::abs(a - b);
    double max_ab = std::max(std::abs(a), std::abs(b));
    
    if (diff <= acc){ return true;}  // absolute tolerance
    else if(diff <= eps * max_ab){return true;} // Relative tolerance
    else {return false;}
}

}

