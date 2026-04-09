#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include"../packages/matrix_QR.h"
#include<functional>
namespace pp{
    namespace ode{
        std::tuple<vector,vector> heun(
            std::function<vector(double,vector)> f, double x, vector y, double h, double alpha = 1.0/3.0, double beta= 2.0/3.0                    
            )
        {
            vector k0 = f(x,y);              
            vector k1 = f(x+alpha*h,y+k0*h*alpha);
            vector k2 = f(x+beta*h,y+(beta+(beta*beta/(2.0*alpha)))*k0*h+beta*beta/(2.0*alpha)*k1*h);

            vector y_cubic = y 
                + (1.0-1.0/(2.0*alpha)-1.0/(3.0*beta*beta)+1.0/(3.0*alpha*beta))*k0*h
                + (1.0/(2.0*alpha)-1/(3.0*alpha*beta))*k1*h 
                + 1.0/(3.0*beta*beta)*k2*h;
            vector y_quadratic = y 
                + (1.0-1.0/(2*alpha))*k0*h 
                + (1/(2.0*alpha))*k1*h;
            vector δy = y_cubic-y_quadratic;           /* Different order error estimate */
            return std::make_tuple(y_cubic,δy);
        }

        pp::matrix driver(
            std::function<vector(double,vector)> F,/* the f from dy/dx=f(x,y) */
            double a,double b,           /* initial-point,final-point */
            vector yinit,                /* y(initial-point) */
            double h=0.125,              /* initial step-size */
            double acc=0.01,             /* absolute accuracy goal */
            double eps=0.01             /* relative accuracy goal */ 
        ){
        double min_step_size = (b-a)/1e7;
        double x=a; vector y(yinit);
        //test
        std::cerr << "Step: " << x << " y[0]: " << y[0] << std::endl;

        std::vector<double> xlist; xlist.push_back(x);
        std::vector<vector> ylist; ylist.push_back(y);
        do{
            if(x>=b){
                int num_steps = xlist.size();
                int num_vars = ylist[0].size();
                //Convert to pp::matrix
                //first column is x_list
                vector ppxlist = vector(xlist);
                matrix result = matrix(num_steps,num_vars+1);
                result[0]=ppxlist;

                //debugging size
                std::cerr << result.size1()<< result.size2();
                

                //nest columns
                for (int i=0; i<num_steps;i++){
                    const pp::vector& row = ylist[i];
                    for (int j=0; j<num_vars;j++){
                        //result[row,column]
                        result(i,j+1)=row[j];
                    }
                }
            return result; /* job done */
            } 

            if(x+h>b) h=b-x;               /* last step should end at b */
            auto [yh,δy] = heun(F,x,y,h);
            double tol = (acc+eps*yh.norm()) * std::sqrt(h/(b-a));
            double err = δy.norm();
            if(err<=tol|| h<=min_step_size){ // accept step
                x+=h; y=yh;
                xlist.push_back(x);
                ylist.push_back(y);
                }
            if(err>0) h *= std::min(std::pow(tol/err,0.25)*0.95, 2.0); // readjust stepsize
            else h*=2.0;
            if (h < min_step_size) h = min_step_size;
            }while(true);
        }//driver

    }; // struct ODE



}//namespace
