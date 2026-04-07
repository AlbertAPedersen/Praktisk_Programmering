#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include<assert.h>
#include"../packages/matrix_QR.h"

namespace pp{
    struct qspline{
        const int n;
        vector x,y;
        vector b,c,p;
        qspline(const vector& x, const vector& y) : n(x.size()), b(n-1), c(n-1), p(n-1), x(x),y(y){
            // calculate b and c

            //Forward recursion
            c[0]=0;
            for(int i=0; i<n-2; i++){
                double dy = y[i+1] - y[i];
                double dx = x[i+1] - x[i];
                double dy_next = y[i+2] - y[i+1];
                double dx_next = x[i+2] - x[i+1];
                p[i] = dy / dx;
                p[i+1] = dy_next / dx_next; // probably a bit inefficient as p is calculated twice...
                
                c[i+1] = (1.0/dx_next) * (p[i+1] - p[i] - c[i]*dx);
            }
            //Backward recursion.
            c[n-2]*=0.5;
            for(int i=n-3;i>=0;i--){
                double dy = y[i+1] - y[i];
                double dx = x[i+1] - x[i];
                double dy_next = y[i+2] - y[i+1];
                double dx_next = x[i+2] - x[i+1];

                p[i] = dy / dx;
                p[i+1] = dy_next / dx_next;
                
                c[i] = (1/dx) * (p[i+1] - p[i] - c[i+1]*dx_next);
            }
            //b value loop:
            for (int i=0;i<n-1;i++){
                double dx = x[i+1]-x[i];
                b[i] = p[i] - c[i] * dx;
            }
            
        }
       
        int binsearch(double z){/* locates the interval for z by bisection */ 
            assert( z>=x[0] && z<=x[x.size()-1] );//is z even in the range?
            int i=0, j=x.size()-1;
            while(j-i>1){
                int mid=(i+j)/2;
                if(z>x[mid]) i=mid; else j=mid;
                }
        return i; //i is always lower than j.
        }


        double eval(double z){
            int i = binsearch(z);
            double dx = z-x[i];
            double s = y[i] + b[i]*dx + c[i]*dx*dx; 
            return s;
        }
        double deriv(double z){
            int i = binsearch(z);
            double dx = z-x[i];
            double dsdx = b[i] + 2.0*c[i]*(dx); 
            return dsdx;
        }
        double integ(double z){
            int i = binsearch(z);
            double integral = 0;
            for (int j=0; j<i;j++){
                double dx = x[j+1]-x[j];

                integral+= y[j]*dx+0.5*b[j]*dx*dx+c[j]*dx*dx*dx/3;
            }
            //Last bit
            double dx = z-x[i];
            integral+= y[i]*dx+0.5*b[i]*dx*dx+c[i]*dx*dx*dx/3;
            return integral;
        }
        
    }; // struct spline
 struct cspline{
        const int n;
        vector x,y;
        vector b,D,Q,B,c,d,h,dy,p, D_tilde, B_tilde;

        cspline(const vector& x, const vector& y) : n(x.size()), b(n), D(n), Q(n-1), B(n), c(n), d(n), h(n), dy(n), p(n), D_tilde(n),B_tilde(n), x(x), y(y){
            for (int i=0;i<=n-2;i++){ // ALL INDECES ARE -1 AS INDECES START AT 0.
                h[i]=x[i+1]-x[i];
                dy[i]=y[i+1]-y[i];
                p[i]=dy[i]/h[i];
            }

            D[0] = 2.0;
            D_tilde[0] = D[0];

            Q[0] = 1.0;
            
            B[0] = 3.0 * p[0]; // FInd p1S
            B_tilde[0] = B[0];
        
            B[n-1] = 3 * p[n-2];
            D[n-1] = 2.0;
            
            for (int i=0; i<=n-3;i++){
                D[i+1] = 2*h[i]/h[i+1]+2;
                Q[i+1] = h[i]/h[i+1];
                B[i+1] = 3*(p[i]+p[i+1]*h[i]/h[i+1]);
            }

            for (int i=1;i<=n-1;i++){
                D_tilde[i] = D[i]-Q[i-1]/D_tilde[i-1];
                B_tilde[i] = B[i]-B_tilde[i-1]/D_tilde[i-1];
            }



            
            b[n-1] = B_tilde[n-1]/D_tilde[n-1];
            for (int i=n-2;i>=0;i--){
                b[i]=(B_tilde[i]-Q[i]*b[i+1])/D_tilde[i];
            }

    
            for (int i=0; i<=n-2; i++){
                c[i]=(-2.0*b[i]-b[i+1]+3.0*p[i])/h[i];
                d[i]=(b[i]+b[i+1]-2.0*p[i])/(h[i]*h[i]);
            }
        }

        int binsearch(double z){/* locates the interval for z by bisection */ 
        assert( z>=x[0] && z<=x[x.size()-1] );//is z even in the range?
        int i=0, j=x.size()-1;
        while(j-i>1){
            int mid=(i+j)/2;
            if(z>x[mid]) i=mid; else j=mid;
            }
        return i; //i is always lower than j.
        }


        double eval(double z){
            int i = binsearch(z);
            double dx = z-x[i];
            double s = y[i] + b[i]*dx + c[i]*dx*dx+d[i]*dx*dx*dx; 
            return s;
        }
        double deriv(double z){
            int i = binsearch(z);
            double dx = z-x[i];
            double dsdx = b[i] + 2.0*c[i]*(dx) + 3*d[i]*dx*dx; 
            return dsdx;
        }
        double integ(double z){
            int i = binsearch(z);
            double integral = 0;
            for (int j=0; j<i;j++){
                double dx = x[j+1]-x[j];

                integral+= y[j]*dx+0.5*b[j]*dx*dx+c[j]*dx*dx*dx/3+d[j]*dx*dx*dx*dx/4.0;
            }
            //Last bit
            double dx = z-x[i];
            integral+= y[i]*dx+0.5*b[i]*dx*dx+c[i]*dx*dx*dx/3.0+d[i]*dx*dx*dx*dx/4.0;;
            return integral;
        
        }



    }; //cspline
}//namespace
