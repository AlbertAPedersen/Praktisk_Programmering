#include<iostream>
#include<cstdio>
#include"sfuns.h"

int main(){
    double x=0.3;
    double y = sfuns::fgamma(x);
    std::cout << "fgamma("<< x <<")=" << y << "\n";
    std::printf("gfamma(%g)=%g\n",x,y);
        
    return 0;
}