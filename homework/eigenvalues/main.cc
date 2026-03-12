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
/*for(int n=0;n<x;n+??){
        double rmax=1;
        double dr=0.1;
    */


int max_index=1;
int dr_index=1;
for(int i=0;i<argc;i++){ //find index for -rmax and -dr to determine number of values in input
    std::string arg=argv[i]; 
    if(arg=="-rmax") max_index = i;
    if(arg=="-dr") dr_index = i;
    //std::cout <<arg <<"\n"<<"i"<< i<<"\n"; // For debugging
    }
int max_len = dr_index-max_index-1;
int dr_len = argc-dr_index-1;

//std::cout <<"max_len: "<< max_len <<"\n"; // For debugging
//std::cout <<"dr_len: "<< dr_len <<"\n"; // For debugging

pp::vector DR(dr_len); //Initialisation of lists. pp::vector used for convenience/familiarity
pp::vector MAX(max_len);

for(int i=0; i<argc;i++){
    std::string arg=argv[i]; 
    if(arg=="-rmax"){
        for(int j=1;j<=max_len;j++){
            MAX[j-1]=std::stod(argv[i+j]);
        }
    }
    if(arg=="-dr"){
        for(int j=1;j<=dr_len;j++){
            DR[j-1]=std::stod(argv[i+j]);
        }
    }
}
DR.print("dr"); //Debugging
//MAX.print("max"); // Debugging

//BLOCK FOR GNU
std::cout << "\n\n";


double max_fixed=5;
for(int j=0;j<DR.size();j++){
    double dr=DR[j];
    double rmax=max_fixed;

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

    pp::EVD solution=pp::EVD(H);
    pp::vector eigenvalues=solution.w;

    std::cout << rmax << " " << dr << " " << eigenvalues[0] << "\n";
  
}//end outer loop

//BLOCK FOR GNU
std::cout << "\n\n";


double dr_fixed=0.2;
for(int j=0;j<MAX.size();j++){
    double dr=dr_fixed;
    double rmax=MAX[j];

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

    pp::EVD solution=pp::EVD(H);
    pp::vector eigenvalues=solution.w;

    std::cout << rmax << " " << dr << " " << eigenvalues[0] << "\n";
  
}//end outer loop



return 0;
}



