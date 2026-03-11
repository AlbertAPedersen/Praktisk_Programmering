#include<iostream>
#include<vector>
#include<string>
#include"../packages/matrix_QR.h"
#include"jacobi.h"

int main(int argc, char* argv[]){
    
pp::matrix A = pp::randomsymmetric(8);

A.print("Matrix A");

pp::EVD result=pp::EVD(A);



result.V.print("V");
result.w.print("w");
result.D.print("D");

((result.V.transpose()*A*result.V).round(1e-5)).print("VTAV=D");
((result.V*result.D*result.V.transpose()).round(1e-5)).print("VDVT=A");
((result.V.transpose()*result.V).round(1e-5)).print("VTV=1");
((result.V*result.V.transpose()).round(1e-5)).print("VVT=1");

//Task B
//Outer loop to gain single epsilon0
pp::vector epsilon0;
for(int n=0;n<x;n+??){
        double rmax=1;
        double dr=0.1;
    for(int i=0;i<argc;i++){
        std::string arg=argv[i];
        if(arg=="-rmax" && i+1<argc) rmax=std::stod(argv[i+1]);
        if(arg=="-dr"&& i+1<argc) dr=std::stod(argv[i+1]);
    }

    std::cout<< "rmax: "<< rmax << " dr: " << dr<<"\n";


    int npoints = (int)(rmax/dr)-1;
    pp::vector r(npoints);
    pp::matrix H(npoints,npoints);
    for(int i=0;i<npoints;i++)r[i]=dr*(i+1);

    for(int i=0;i<npoints-1;i++){
    H[i,i]  =-2*(-0.5/dr/dr);
    H[i,i+1]= 1*(-0.5/dr/dr);
    H[i+1,i]= 1*(-0.5/dr/dr);
    } //Construct K, loops to n-1
    H[npoints-1,npoints-1]=-2*(-0.5/dr/dr); //Sets last value (wouldn't work otherwise due to off-diagonals)
    for(int i=0;i<npoints;i++)H[i,i]+=-1/r[i]; //Add W

    H.print("H");

    pp::EVD solution=pp::EVD(H);
    pp::vector eigenvalues=solution.w;

    epsilon[n]=eigenvalues[0]
}//end outer loop


//New block for GNU

std::cout<< "\n \n";





return 0;
}



