#include<iomanip>
#include<iostream>
#include<cmath>
#include<vector>
#include<complex>

const double PI = 3.1415926535;
const double e  = 2.7182818284590452;
double erf(double x){
// single precision error function (Abramowitz and Stegun, from Wikipedia)
if(x<0) return -erf(-x);
std::vector<double> a {0.254829592,-0.284496736,1.421413741,-1.453152027,1.061405429};
double t=1/(1+0.3275911*x);
double sum=t*(a[0]+t*(a[1]+t*(a[2]+t*(a[3]+t*a[4]))));/* the right thing */
return 1-sum*std::exp(-x*x);
}

double sgamma(double x){

if(x<0)return PI/std::sin(PI*x)/sgamma(1-x);
if(x<9)return sgamma(x+1)/x;
double lnsgamma=std::log(2*PI)/2+(x-0.5)*std::log(x)-x
    +(1.0/12)/x-(1.0/360)/(x*x*x)+(1.0/1260)/(x*x*x*x*x);
return std::exp(lnsgamma);
}


std::complex<double> cgamma(std::complex<double> z){

    if(z.real()<0.0)return PI/std::sin(PI*z)/cgamma(1.0-z);
    if(z.real()<9.0)return cgamma(z+1.0)/z;
    std::complex<double> lncgamma=std::log(2.0*PI)/2.0+(z-0.5)*std::log(z)-z
        +(1.0/12.0)/z-(1.0/360.0)/(z*z*z)+(1.0/1260.0)/(z*z*z*z*z);
    return std::exp(lncgamma);
}

int main(int argc, char** argv) {
    double xmin=-2, xmax=2, dx=0.125, imin=-2, imax=2, di=0.125;
    std::vector<double> x_tab {0.5,1,1.5,2};
    std::vector<double> y_tab_erf {0.520499878,0.842700793,0.966105146,0.995322265};
    std::vector<double> y_tab_sgamma {1.77245,1,0.886227,1};


    for(int i=0;i<argc;i++){
    std::string arg=argv[i];
    if(arg=="-xmin" && i+1<argc) xmin=std::stod(argv[i+1]);
    if(arg=="-xmax" && i+1<argc) xmax=std::stod(argv[i+1]);
    if(arg=="-dx" && i+1<argc) dx=std::stod(argv[i+1]);

    if(arg=="-imin" && i+1<argc) imin=std::stod(argv[i+1]);
    if(arg=="-imax" && i+1<argc) imax=std::stod(argv[i+1]);
    if(arg=="-di" && i+1<argc) di=std::stod(argv[i+1]);
    
    }

    std::cout<<std::scientific;

    for(double x=xmin;x<xmax;x+=dx){
        std::cout<< x <<" "<< erf(x) <<" "<<sgamma(x)<< "\n";
    }
    std::cout<< "\n\n"; //next block for GNU
    
    for(int i=0;i<x_tab.size();i++){
    std::cout<< x_tab[i] << " " << y_tab_erf[i] << " " << y_tab_sgamma[i]<<"\n";
    }

    std::cout<< "\n\n"; //next block for GNU
    for(double x=xmin;x<xmax;x+=dx){    
        for (double i=imin;i<imax;i+=di){
            std::complex<double> Z(x,i);
        std::cout<< x << " " << i << " " << std::norm(cgamma(Z)) << "\n";
        }
        std::cout << "\n";
    }
    




return 0;
}