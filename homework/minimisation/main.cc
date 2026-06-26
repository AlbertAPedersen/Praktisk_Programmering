#include<iostream>
#include<vector>
#include"../packages/matrix_QR.h"
#include"../packages/ode.h"
#include "../packages/roots.h"
#include "min.h"
#include<cmath>
#include<functional>

double quadratic(const pp::vector& x){
    double x0 = x[0];
    double x1 = x[1];

    return 2*x0*x0+x1*x1;
}

double Rosenbruck(const pp::vector& x){
    double x0 = x[0];
    double x1 = x[1];

    return (1-x0)*(1-x0)+100*(x1-x0*x0)*(x1-x0*x0);
}

double Himmelblau(const pp::vector& x){
    double x0 =x[0];
    double x1 =x[1];


    return (x0*x0+x1-11)*(x0*x0+x1-11)+(x0+x1*x1-7)*(x0+x1*x1-7);
}

double Breit_Wigner(double E, double m, double gamma, double A){
    double denom = (E-m)*(E-m)+gamma*gamma/4;

    return A/denom;
}

double residual(const pp::vector& c, double E, double signal, double error){
    double m=c[0];
    double gamma=c[1];
    double A=c[2];
    
    return (Breit_Wigner(E,m,gamma,A)-signal)/error;
}

pp::vector E, signal, error;

auto chi2 = [&E,&signal,&error](const pp::vector& c){
    double resid=0;
    for (int i=0;i<E.size();i++){
        double res_i=residual(c,E[i],signal[i],error[i]);
        resid+=res_i*res_i;
    }
    return  resid;
};
    

int main(){
   std::cout<< "\n";
    pp::vector x = pp::vector{30,20};
    double acc=1e-3;
    pp::newton res_rosenbruck(Rosenbruck,x,acc);
    pp::newton res_himmelblau(Himmelblau,x,acc);

    x.print("Starting guess:");
    res_rosenbruck.x.print("Rosenbruck min:");
    std::cout << "n_steps: " << res_rosenbruck.steps << "\n\n";

    res_himmelblau.x.print("Himmelblau min:");
    std::cout << "n_steps: " << res_himmelblau.steps <<"\n";




    //task 2
    
    std::vector<double> E_std, signal_std, error_std;
    double data1,data2,data3;
    while (std::cin >> data1 >> data2 >> data3) {
        E_std.push_back(data1); signal_std.push_back(data2); error_std.push_back(data3);     
    }
    

    E = pp::vector(E_std);
    signal = pp::vector(signal_std);
    error = pp::vector(error_std);



    pp::vector c_guess = pp::vector{150,20,45};
    pp::newton res_higgs(chi2,c_guess,acc);
    pp::vector params = res_higgs.x;

    params.print("Higgs parameters (m,gamma,A)");

    std::cout << "n_steps: " << res_higgs.steps <<"\n";



    pp::newton res_higgs_central(chi2,c_guess,acc,1);
    pp::vector params_central = res_higgs_central.x;
    params_central.print("Higgs parameters central differences (m,gamma,A)");

    std::cout << "n_steps: " << res_higgs_central.steps <<"\n";

    //Plotting section:
    std::cout <<"\n\n";
    for (int i=0;i<E.size();i++){
        std::cout << E[i] << " " << signal[i] << " " << error[i] << "\n";
    }

        std::cout <<"\n\n";
    for (int i=0;i<E.size();i++){
            std::cout << E[i] << " " << Breit_Wigner(E[i], params[0], params[1],params[2]) << "\n";
    }

    std::cout <<"\n\n";
    for (int i=0;i<E.size();i++){
            std::cout << E[i] << " " << Breit_Wigner(E[i], params_central[0], params_central[1],params_central[2]) << "\n";
    }



    return 0;

}

