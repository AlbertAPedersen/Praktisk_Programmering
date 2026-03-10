#include<iostream>
#include<vector>
#include"../packages/matrix_QR.h"
#include"jacobi.h"

int main(){
    
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

return 0;
}