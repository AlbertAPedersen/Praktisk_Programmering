#pragma once
#include<iostream>
#include<vector>
#include"../packages/matrix_QR.h"
#include<cstdio>
#include<iomanip>
#include<cmath>


namespace pp{

struct EVD{

    //w,V constructor
	pp::vector w; pp::matrix V; pp::matrix D;

    //timesJ member functions
	static void timesJ(pp::matrix& A, int p, int q, double theta){
        double c=std::cos(theta), s=std::sin(theta);
        for(int i=0;i<A.size1();i++){
            double aip=A[i,p],aiq=A[i,q];
            A[i,p]=c*aip-s*aiq;
            A[i,q]=s*aip+c*aiq;
            }
    }
	static void Jtimes(pp::matrix& A, int p, int q, double theta){
        //Updates matrix A, multiplying it by J from the left
        double c=std::cos(theta),s=std::sin(theta);
        for(int j=0;j<A.size1();j++){
            double apj=A[p,j],aqj=A[q,j];
            A[p,j]= c*apj+s*aqj;
            A[q,j]=-s*apj+c*aqj;
            }
		}
    //EVD constructor
	EVD(matrix A) : w(A.size1()),V(A.size1(),A.size1()),D(A.size1(),A.size1()) {
        D=A;
        V.setid();
        int n=D.size2();
        int m=D.size1();
        //check square
        if(n!=m) throw std::runtime_error("non-square matrix\n");

        //Check symmetric
        //Could probably also just check transpose
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if (D(i,j)!=D(j,i)) throw std::runtime_error("Non-symmetric matrix for EVD\n");

            }
        }
        bool changed;
        do{
            changed=false;
            for(int p=0;p<n-1;p++){
                for (int q = p + 1; q < n; q++){
                    double apq=D[p,q], app=D[p,p], aqq=D[q,q];
                    double theta=0.5*std::atan2(2*apq,aqq-app);
                    double c=std::cos(theta),s=std::sin(theta);
                    double new_app=c*c*app-2*s*c*apq+s*s*aqq;
                    double new_aqq=s*s*app+2*s*c*apq+c*c*aqq;
                    if(pp::approx(new_app,app,1e-16,1e-16)!=true || pp::approx(new_aqq,aqq,1e-16,1e-16)!=true) // do rotation if APP and AQQ are changed
                    {
                    changed=true;
                    timesJ(D,p,q, theta); // A←A*J 
                    Jtimes(D,p,q,-theta); // A←JT*A 
                    timesJ(V,p,q, theta); // V←V*J
                    }
                }
            };
        }while(changed);
    for(int i=0;i<n;i++){
        w[i]=D[i,i];
        for(int j=0;j<n;j++){ // Clean up D
            if (i!=j){
                if(std::abs(D[i,j])<1e-7) D[i,j]=0;
            }
        }
    }
    }//EVD function
    
    //Functions to return V and w
    matrix getV(){
        return V;
    }
    matrix getD(){
        return D;
    }
    vector getw(){
        return w;
    }

    matrix covariance(){

        cvarmatrix=R.inverse()*((R.inverse()).transpose());
        return cvarmatrix;
    }
};//EVD struct

}; //pp