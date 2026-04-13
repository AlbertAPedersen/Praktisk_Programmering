#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include"../packages/matrix_QR.h"
#include<functional>
namespace pp{
    double PI = 3.1415926535897932384626433;
    vector integrate(
        std::function<double(double)> f,
        double a=0,
        double b=1,
        double acc= 0.001,
        double eps= 0.001,
        double f2 = NAN,
        double f3 = NAN  
    )//input
    {
        double h = b-a;
        if (h<1e-12) return vector{0,0}; //avoid infinite
        if (std::isnan(f2)){
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
            return vector{Q,err};}
        else {
            return integrate(f,  a    ,(a+b)/2, acc/std::sqrt(2),eps,f1,f2)+
		           integrate(f,(a+b)/2,   b   , acc/std::sqrt(2),eps,f3,f4);
            }
    } //Integrate

    vector CC_integrate(
        std::function<double(double)> f,
        double a=0,
        double b=1,
        double acc= 0.001,
        double eps= 0.001,
        double f2 = NAN,
        double f3 = NAN  
    )//input
    {
     //Infinite interval transformations::
     if (std::isinf(b)){ //Implementation assumes no funny business with a=inf or b=-inf.
        if (std::isinf(a)){
            auto f_new = [f](double t){
                double x = (t/(1-t*t));
                double factor = (1+t*t)/((1-t*t)*(1-t*t));
                return f(x)*factor;
            };
            return CC_integrate(f_new,-1,1,acc,eps);
        }//Double infinite
        else{// a finite and b infinite
            auto f_new = [a,f](double t){
                double x = (a+t/(1-t));
                double factor = 1/((1-t)*(1-t));
                return f(x)*factor;
            };
            return CC_integrate(f_new,0,1,acc,eps);
        }
        }
        else{ //b not infite
            if (std::isinf(a)){ //but a is:
                auto f_new = [b,f](double t){
                    double x = (b+t/(1+t));
                    double factor = 1/((1+t)*(1+t));
                    return f(x)*factor;
                };
                return CC_integrate(f_new,-1,0,acc,eps);
            }
        
            else{//everything normal
                auto CC_transform = [f,a,b](double theta){
                    double x=(a+b)/2+(b-a)/2*std::cos(theta);
                    double factor =std::sin(theta)*(b-a)/2.0;
                return f(x)*factor;
                };
                return integrate(CC_transform,0,PI,acc,eps,f2,f3);
            }
        }
    }//CC_integrate


}//namespace
