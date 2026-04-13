#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include"../packages/matrix_QR.h"
#include<functional>
namespace pp{
    double PI=  3.1415926535897932384626433;
    double integrate(
        std::function<double(double)> f,
        double a=0,
        double b=1,
        double acc= 0.001,
        double eps= 0.001,
        double f2 = 1.23456, //Very unlikely that the function has this value
        double f3 = 1.23456  //Very unlikely that the function has this value
    )//input
    {
        double h = b-a;
        if (h<1e-12) return 0; //avoid infinitelooping
        if (f2 == 1.23456){ //first call (likely)
            f2 = f(a+2*h/6);
            f3 = f(a+4*h/6);
        }
        double f1 = f(a+h/6);
        double f4 = f(a+5*h/6);
        
       	double Q = (2*f1+f2+f3+2*f4)/6*(b-a); // higher order rule
	    double q = (  f1+f2+f3+  f4)/4*(b-a); // lower order rule


	    double err = std::abs(Q-q);
        double tol = acc+eps*std::abs(Q);
        if (err < tol) {
            return Q;}
        else {
            return integrate(f,  a    ,(a+b)/2, acc/std::sqrt(2),eps,f1,f2)+
		           integrate(f,(a+b)/2,   b   , acc/std::sqrt(2),eps,f3,f4);
            }
    } //Integrate

    double CC_integrate(
        std::function<double(double)> f,
        double a=0,
        double b=1,
        double acc= 0.001,
        double eps= 0.001,
        double f2 = 1.23456, //Very unlikely that the function has this value
        double f3 = 1.23456  //Very unlikely that the function has this value
    )//input
    {
        auto CC_transform = [f,a,b](double theta){
            double x=(a+b)/2+(b-a)/2*std::cos(theta);
            double conversion =std::sin(theta)*(b-a)/2.0;
           return f(x)*conversion;
            
        };
        return integrate(CC_transform,0,PI,acc,eps,f2,f3);

    }//CC_integrate




}//namespace
