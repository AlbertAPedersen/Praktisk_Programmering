#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include"../packages/matrix_QR.h"
#include<functional>
#include<cstdlib>
#include<tuple>



namespace pp{


template<typename func>
struct newton{
    vector x;
    int steps=0;
    newton(func& theta,vector& x_input,double acc=1e-3, bool central=0) : x(x_input) {
        while (steps<1000){ //NEWTON
            int n = x.size();
        vector g;
            matrix H;
            vector dx;
            double theta_x = theta(x);
            
            if (central){
                auto [g_temp,H_temp] = hessian_central(theta,x);
                g=g_temp;
                H=H_temp;
                if (g.norm() < acc) break;   // job 
                // done
                for (int i=0; i<n;i++) H[i,i]+=1e-1 ; // Levenberg regularization (1e-6 at first)
                dx = QR(H).solve(-g);
            }

            else{

                g = gradient(theta,x,theta_x);
                if (g.norm() < acc) break;   // job done
                H = hessian(theta,x,theta_x);
                for (int i=0; i<n;i++) H[i,i]+=1e-2; // Levenberg regularization (1e-6 at first)
                dx = QR(H).solve(-g);
            }

            for (int i = 0; i < n; i++) { //This check was implemeted with AI.
                if (dx[i] != dx[i] || g[i] != g[i]) {
                    std::cerr << "NaN IN Newton step";
                    break;
                }
            }
            

                double lambda = 1.0;
                while (lambda >= 1.0/2048.0){    // backtracking linesearch 
                    if (theta(x+lambda*dx) < theta_x) break; // good step
                    lambda/= 2;  
                }
                x=x+lambda*dx;
                steps+=1;
                std::cerr << "Newton step:" << steps << "\n";
            }
        }                


    vector gradient(func& theta,vector& x,double theta_x){
        vector g_theta = vector(x.size());

        double exponent =-25; // this value seemed good after some trial and error
        for (int i=0;i<x.size();i++){
            double dxi = (1+abs(x[i]))*std::pow(2,exponent); // δx~ε^(1/2)
            double inv_dxi = 1/dxi; 
                x[i]+=dxi;
                g_theta[i]=(theta(x)-theta_x)*inv_dxi; //Forward diff
                x[i]-=dxi;
        }
        return g_theta;
    }


    matrix hessian(func& theta,vector& x,double& theta_x){
        int n =x.size();
        matrix H = matrix(n,n);
        vector g_theta_x = gradient(theta,x,theta_x);
        double exponent = -26; // this value seemed good after some trial and error
        for (int j=0; j<n;j++){
            double dxj=(1+abs(x[j]))*std::pow(2,exponent); 
            double inv_dxj = 1/dxj;
            x[j]+=dxj;
            double theta_new=theta(x);
            vector dg_theta=gradient(theta,x,theta_new)-g_theta_x; 

            for (int i=0;i<n; i++){
                H[i,j]=dg_theta[i]*inv_dxj;
            }
            x[j]-=dxj; //reset
            }
        return H;
    }

      std::tuple<vector,matrix> hessian_central(func& theta,vector& x){
        int n =x.size();
        matrix H = matrix(n,n
        );
        double exponent = -17;
        vector g_theta_x = pp::vector(x.size());

         for (int k=0; k<n;k++){
            double dxk=(1+abs(x[k]))*std::pow(2,exponent); 
            for (int j=0; j<n; j++){
                double dxj=(1+abs(x[j]))*std::pow(2,exponent);
                double denom = 1/(4*dxk*dxj);
                if (j==k){ //gradient
                    x[k]+=dxk;
                    double theta_high=theta(x);
                    x[k]-=2*dxk;
                    double theta_low=theta(x);
                    x[k]+=dxk; //reset
                    g_theta_x[k]=(theta_high-theta_low)/(2.0*dxk);
                }

                x[k]+=dxk;
                x[j]+=dxj;
                double theta1 = theta(x); //+k+j

                x[j]-=2*dxj;
                double theta2 = theta(x); //+k-j

                x[k]-=2*dxk;
                double theta4 = theta(x); //-k-j

                x[j]+=2*dxj;
                double theta3 = theta(x); //-k+j

                x[j]-=dxj; //back to normal
                x[k]+=dxk;
                
                H[k,j]=(theta1-theta2-theta3+theta4)*denom;
            }
            
            }
        return {g_theta_x,H};
        
    }
}; //newton struct
} //namespace
