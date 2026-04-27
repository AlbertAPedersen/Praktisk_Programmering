#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include"../packages/matrix_QR.h"
#include<functional>
namespace pp{
    struct lcg{
        long long a;
        long long c;
        long long m;
        long long seed;

        lcg(long long _seed,
            long long _a=1664525,
            long long _c=1013904223,
            long long _m=std::pow(2,32)) : a(_a), c(_c), m(_m), seed(_seed){};

            double call(){
            seed = (a*seed+c) % m;
            return static_cast<double>(seed+1)/static_cast<double>(m+1);
        }
        
    }; //lcg

std::vector<double> plainmc(
    std::function<double(const std::vector<double>&)> f,
    std::vector<double>& a, 
    std::vector<double>& b, 
    int N,
    pp::lcg& gen){
        int dim = a.size();
        double V = 1;
        for (int i=0; i<dim;i++){
            V *= b[i] - a[i];
        } 
        double sum1 = 0.0;
        double sum2 = 0.0;
        std::vector<double> x(dim);

        for (int j=0; j<N;j++){
            for (int i=0; i<dim;i++){
                x[i] = a[i] + gen.call() * (b[i]-a[i]);
            }
            double fx = f(x);
            sum1 += fx; 
            sum2 += fx * fx;
        }
        double mean = sum1 / N;
        double sigma = std::sqrt(sum2 / N - mean * mean);
    return {mean * V, sigma * V / std::sqrt(N)};
    }



}//namespace
