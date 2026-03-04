#include<iomanip>
#include<iostream>
#include<thread>
#include<vector>
#include"matrix.h"

int main(int argc, char **argv) {
/*
Task A 
*/
    std::cout<< "Task A2"<<"\n";

    pp::matrix A2=pp::randommatrix(10,4);

    A2.print("Matrix A");

    //Decomposing to QR
    pp::QR decomp2(A2); 
    pp::matrix Q2=decomp2.Q;
    pp::matrix R2=decomp2.R;
    Q2.print("Matrix Q:");
    R2.print("Matrix R:");
    //test transpose QtQ=1
    pp::matrix QtQ2=Q2.transpose()*Q2;
    //QtQ.print("QtQ");


    pp::matrix I2 = QtQ2;
    I2.setid();
    //I4.print();

    //Running tests with approx
    std::cout<< "approx(Q*R,A) returns "<< pp::approx(Q2*R2,A2) <<"\n";

    std::cout<< "approx(I4,QtQ) returns "<< pp::approx(I2,QtQ2) <<"\n";


    std::cout<< "Task A3 with 7x7" <<"\n";

    pp::matrix A3 = pp::randommatrix(7,7);
    pp::vector b3 = pp::randomvec(7);
    pp::QR decomp3(A3);
    pp::matrix Q3=decomp3.Q;
    pp::matrix R3=decomp3.R;

    pp::vector x3=decomp3.solve(b3);

    std::cout<< "approx(b, A*x) returns "<<pp::approx(b3,A3*x3)<<"\n";
    //R3.print();

    std::cout<< "Task A4" <<"\n";
    std::cout<< "Det(R) returns" << decomp3.det() << "\n";

/*
Task B
Uses same square matrix as A3 for the inverse (7x7)
*/
    std::cout<< "Task B"<<"\n";
    
    pp::matrix A3_inv = decomp3.inverse();

    pp::matrix prod = A3_inv*A3;
    pp::matrix I7(7,7);
    I7.setid();
    prod.print();
    std::cout<< "approx(I7,A3_inv*A3) returns " << pp::approx(I7,A3_inv*A3) << "\n";


/*
Task C
*/

for(int i=0; i<argc;i++){
    int N=1;
    std::string arg=argv[i];
    if (arg=="-size") N=std::stoi(argv[i+1]);
    
    pp::matrix A=pp::randommatrix(N,N);
    pp::QR datum(A);
}

return 0;
}
