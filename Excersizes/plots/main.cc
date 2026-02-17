#include<iomanip>
#include<iostream>
#include<cmath>
#include<vector>

const double PI = 3.1415926535;
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



int main(int argc, char** argv) {
    double xmin=0, xmax=10, dx=0.125;
    std::vector<double> x_tab {0.5,1,1.5,2};
    std::vector<double> y_tab_erf {0.520499878,0.842700793,0.966105146,0.995322265};
    std::vector<double> y_tab_sgamma {1.77245,1,0.886227,1};


    for(int i=0;i<argc;i++){
    std::string arg=argv[i];
    if(arg=="-xmin" && i+1<argc) xmin=std::stod(argv[i+1]);
    if(arg=="-xmax" && i+1<argc) xmax=std::stod(argv[i+1]);
    if(arg=="-dx" && i+1<argc) dx=std::stod(argv[i+1]);
    }

    std::cout<<std::scientific;

    for(double x=xmin;x<xmax;x+=dx){
        std::cout<< x <<" "<< erf(x) <<" "<<sgamma(x)<<"\n";
    }
    std::cout<< "\n\n"; //next block for GNU
    
    for(int i=0;i<x_tab.size();i++){
    std::cout<< x_tab[i] << " " << y_tab_erf[i] << " " << y_tab_sgamma[i]<<"\n";
    }




return 0;
}