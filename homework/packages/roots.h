#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include"../packages/matrix_QR.h"
#include<functional>
#include<cstdlib>



template <typename Func>
pp::matrix Jacobian(Func f,pp::vector x, pp::vector fx){
    int n = x.size();
    pp::vector dx = pp::vector(n);
    pp::vector df = pp::vector(n);

    for (int i=0; i<n; i++) dx[i] = std::max(std::abs(x[i]),1.0)*std::pow(2,-26);
    pp::matrix J(n,n);

    for (int j=0;j<n;j++){
        x[j]+=dx[j];
        df = f(x)-fx;

        for (int i=0; i<n; i++) J(i,j)=df[i]/dx[j];
        x[j]-=dx[j];

    }
    return J;
}

template <typename Func>
pp::vector newton(Func f,pp::vector x, double acc=1e-2,double alpha_min=1e-3, int max_iter=100){
    pp::vector fx = f(x);
    pp::vector fz = pp::vector(x.size());
    pp::vector z = pp::vector(x.size());

    for (int i=0; i<max_iter;i++){
        if (fx.norm() < acc) break;
        pp::matrix J = Jacobian(f,x,fx);
        pp::QR QRJ = pp::QR(J);
        pp::vector Dx = QRJ.solve(-fx); //newton step

        double alpha = 1.0;
        while (true){
            z = x+alpha*Dx;
            fz = f(z);
            if (fz.norm() < (1.0-alpha/2.0)*fx.norm()) break; // accept condition
            if (fz.norm() < fx.norm()) break; //step too big
            if (alpha  < alpha_min) break; //accept bad step
            alpha/=2;
        }
        x=z;
        fx=fz;
    }
    return x;
}



