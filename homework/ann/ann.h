#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include"../packages/matrix_QR.h"
#include"../packages/min.h"
#include"../packages/integrate.h"
#include<functional>
#include<cstdlib>
#include<tuple>



namespace pp{


template<typename func>
struct ann{
    int n; /* number of hidden neurons */
    func f; /* activation function */
    vector p; /*w, then a, then b each for N values*/

    ann(int n, func activation_function) : n(n), f(activation_function), p(3 * n){
        //initial guess are 1
        for (int i=0; i<3*n; i++){
            p[i]=1;
        }

    }




   double response(double x,vector p_now){  
    /* return the response of the network to the input signal x */
        double Fp=0;
        for (int i=0; i<n; i++){
            double Wi=p_now[i]; 
            double ai=p_now[i+n];
            double bi=p_now[i+2*n];

            double yi=f((x-ai)/bi)*Wi;
            Fp+=yi;
        }
        return Fp;
    }


    double d_response(double x,vector p_now){  
        double dx = (1+std::abs(x))*std::pow(2,(-10));
  
        return (response(x+dx,p_now)-response(x,p_now))/dx;
    }
    double dd_response(double x,vector p_now){
        double dx = (1+std::abs(x))*std::pow(2,(-10));
        
        return (response(x+2*dx,p_now)-2*response(x+dx,p_now)+response(x,p_now))/(dx*dx);
    }
    
    double ad_response(double x,vector p_now){
        auto int_func = [this,&p_now](double t){
            return response(t,p_now);
        };
        if(x>0){
        double integral = integrate(int_func,0,x)[0]; //evaluates integral from 0 using function "response"
        return integral;    
        }
        else{
            double integral = integrate(int_func,x,0)[0]; //evaluates integral from 0 using function "response"
        return -integral;    
        }

    }

 

   void train(const vector& x,const vector& y){
    /* train the network to interpolate the given table {x,y} */
        auto Fcost = [&x,&y, this](const vector& p_now){
            int N = x.size();
            double Cp = 0;

            for (int k=0;k<N;k++){
                double residual = response(x[k],p_now)-y[k];
                Cp+=residual*residual;
            }
            return Cp;
        };
        pp::newton minimizer(Fcost,p);
        p=minimizer.x;
    }
};//struct ann

        
} //namespace
