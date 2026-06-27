#include<iostream>
#include<vector>
#include"../packages/matrix_QR.h"
#include"ann.h"
#include "../packages/min.h"
#include<cmath>
#include<functional>

double wavelet(const double x){
    return x*std::exp(-x*x);
}

double interesting_function(const double x){
    return std::cos(5*x-1)*std::exp(-x*x);
}

int main(){
    //generate analytical dataset for wavelet
    pp::vector x = pp::vector(100);
    pp::vector y = pp::vector(100);

    for (int i=0;i<100;i++){
        double a=-1+i/50.0;
        x[i]=a;
        y[i]=wavelet(x[i]);
    }

    pp::ann network(1, wavelet);
    network.train(x,y); 
    for (int i=0;i<x.size();i++){
        std::cout << x[i] << " " << y[i] << " " << network.response(x[i],network.p) << "\n";
    }
    std::cout << "\n\n";

    //Interesting function:
     for (int i=0;i<100;i++){
        double a=-1+i/50.0;
        x[i]=a;
        y[i]=interesting_function(x[i]);
    }

    for (int N=1; N<8; N+=2){ //number of neurons
        pp::ann network_interesting(N, wavelet);
        network_interesting.train(x,y); 
        for (int i=0;i<x.size();i++){
            std::cout << x[i] << " " << y[i] << " " << network_interesting.response(x[i],network_interesting.p) << "\n";
        }
    std::cout << "\n\n";
    }

    //ANN derivatives and antiderivative with 10 neurons, first tested against the wavelet
    pp::ann network_deriv_wave(10, wavelet);
        for (int i=0;i<100;i++){
        double a=-1+i/50.0;
        x[i]=a;
        y[i]=wavelet(x[i]);
    }

    network_deriv_wave.train(x,y); 
    for (int i=0;i<x.size();i++){ //value, derivative, double derivative, antiderivative
        std::cout << x[i] << " " 
        << network_deriv_wave.response(x[i],network_deriv_wave.p) << " "
        << network_deriv_wave.d_response(x[i],network_deriv_wave.p) << " "
        << network_deriv_wave.dd_response(x[i],network_deriv_wave.p)<< " "
        << network_deriv_wave.ad_response(x[i],network_deriv_wave.p) << "\n";
    }
    std::cout << "\n\n";

    //analytical solutions:
    for (int i=0;i<x.size();i++){ //value, derivative, double derivative, antiderivative with 8 neurons
        std::cout << x[i] << " " 
        << x[i]*std::exp(x[i]*-x[i]) << " " //standard
        << (1.0-2.0*x[i]*x[i])*std::exp(x[i]*-x[i]) << " " //derivative
        << 2.0*std::exp(x[i]*-x[i])*x[i]*(2*x[i]*x[i]-3)<< " "
        << -std::exp(-x[i]*x[i])/2.0 + 0.5<< "\n"; //integral
    }
     std::cout << "\n\n";

    //ANN derivatives and antiderivate for interesting function

     pp::ann network_deriv_interesting(10, wavelet);
        for (int i=0;i<100;i++){
        double a=-1+i/50.0;
        x[i]=a;
        y[i]=interesting_function(x[i]);
    }

    network_deriv_interesting.train(x,y); 
    for (int i=0;i<x.size();i++){ //value, derivative, double derivative, antiderivative
        std::cout << x[i] << " " 
        << network_deriv_interesting.response(x[i],network_deriv_interesting.p) << " "
        << network_deriv_interesting.d_response(x[i],network_deriv_interesting.p) << " "
        << network_deriv_interesting.dd_response(x[i],network_deriv_interesting.p)<< " "
        << network_deriv_interesting.ad_response(x[i],network_deriv_interesting.p) << "\n";
    }





    return 0;
}

