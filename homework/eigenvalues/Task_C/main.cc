#include<iostream>
#include<vector>
#include<string>
#include"../../packages/matrix_QR.h"
#include"../jacobi.h"



int main(int argc, char* argv[]){
    int size = std::stoi(argv[1]);
pp::matrix A = pp::randomsymmetric(size);

pp::EVD decomp = pp::EVD(A);

return 0;
}