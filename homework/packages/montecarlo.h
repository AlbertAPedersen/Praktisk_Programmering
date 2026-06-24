#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include"../packages/matrix_QR.h"
#include<functional>
#include<cstdlib>


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


    struct halton{
        int n;
        int b;
        int dim;

        double corput(int n,int b=2){
            double q=0.0;
            double bk=1.0/b;
            while (n>0){
                q+= n % b * bk;
                n/=b;
                n=floor(n);
                bk/=b;
            } 
            return q;
    }
    std::vector<int> prime_numbers(int n){
        std::vector<int> primes{};
        int candidate=2;
        while (primes.size()<n){
            bool candidate_is_prime=true;
            for (int p=0; p<primes.size();p++){
                if (p*p>candidate) break;
                if (candidate%primes[p]==0){
                    candidate_is_prime=false;
                    break;
                }
            }
            if (candidate_is_prime){
                primes.push_back(candidate);
            }
                candidate+=1;
            }
    return primes;
    }

    std::vector<std::vector<double>> sequence(int dim, int n){
        std::vector<int> bases=prime_numbers(dim);

        std::vector<std::vector<double>> output(dim);
        for (b=0;b<bases.size();b++){
            for (int i=0; i<n; i++){
            output[b].push_back(corput(i,bases[b]));
            }
        }
        return output;
    }
    

};//Halton


std::vector<double> plainmc(
    std::function<double(const std::vector<double>&)> f,
    std::vector<double>& a, 
    std::vector<double>& b, 
    int N,
    pp::lcg& gen,
    bool C_rand) //This bool makes me able to override the lcg gen for the c++ random number generator.. Not pretty but it works.
    {
        int dim = a.size();
        double V = 1;
        for (int i=0; i<dim;i++){
            V *= b[i] - a[i];
        } 
        double sum1 = 0.0;
        double sum2 = 0.0;
        std::vector<double> x(dim);
        if (C_rand){
            for (int j=0; j<N;j++){
                for (int i=0; i<dim;i++){
                    double random_value= static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
                    x[i] = a[i] + random_value * (b[i]-a[i]); 
                }
                double fx = f(x);
                sum1 += fx; 
                sum2 += fx * fx;
            }
        }
        else{
            for (int j=0; j<N;j++){
                for (int i=0; i<dim;i++){
                    x[i] = a[i] + gen.call() * (b[i]-a[i]);
                }

                double fx = f(x);
                sum1 += fx; 
                sum2 += fx * fx;
            }
        }

        double mean = sum1 / N;
        double sigma = std::sqrt(sum2 / N - mean * mean);
    return {mean * V, sigma * V / std::sqrt(N)};
    }; //C_rand
    

std::vector<double> quasimc(
    const std::function<double(const std::vector<double>&)> f,
    const std::vector<double>& a, 
    const std::vector<double>& b, 
    const std::vector<std::vector<double>>& seq){
        int dim = a.size();
        double V = 1;
        for (int i=0; i<dim;i++){
            V *= b[i] - a[i];
        } 
        double sum1 = 0.0;    
        std::vector<double> x(dim);
        int N=seq[0].size();
        
        for (int j=0; j<N;j++){
            for (int i=0; i<dim;i++){
                x[i] = a[i] + seq[i][j] * (b[i]-a[i]);
            }
            sum1 += f(x);
        }
        double mean = sum1 / N;
        return {mean * V, 0.0};
    }



}//namespace
