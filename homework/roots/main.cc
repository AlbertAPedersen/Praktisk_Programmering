#include<iostream>
#include<vector>
#include"../packages/matrix_QR.h"
#include"../packages/ode.h"
#include "roots.h"
#include<cmath>
#include<functional>

pp::vector quadratic(const pp::vector& x){
    double x0 = x[0];
    double x1 = x[1];
    pp::vector grad = pp::vector(2);

    grad[0] = 2*(x0+5);
    grad[1] = 2*(x1-2);

    return grad;
}

pp::vector Rosenbruck(const pp::vector& x){
    double x0 = x[0];
    double x1 = x[1];
    pp::vector grad = pp::vector(2);

    grad[0] = 2*(200*x0*x0*x0-200*x0*x1+x0-1);
    grad[1] = 200*(x1-x0*x0);

    return grad;
}

pp::vector Himmelblau(const pp::vector& x){
    double x0 =x[0];
    double x1 =x[1];
    pp::vector grad = pp::vector(2);

    grad[0] = 2*(2*x0*(x0*x0+x1-11)+x0+x1*x1-7);
    grad[1] = 2*(x0*x0+2*x1*(x0+x1*x1-7)+x1-11);


    return grad;
}



double E_ODE;

//TASK B

std::function<pp::vector(double,pp::vector)> hydrogen = [&E_ODE](double r, pp::vector y){ //Fits the ODE driver function
    //f''=-2f(E+1/r)
    //y1=f
    //y2=f'
    //y3=f''

    double y1 = y[0];
    double y2 = y[1];
    double y3 = -2*(E_ODE+1/r)*y1;
    pp::vector grad = pp::vector{y2,y3};

    return grad;
};

double rmin,rmax,hinit,acc,eps;
pp::vector yinit;

pp::vector aux_function(const pp::vector& E_newton){
    E_ODE=E_newton[0];
    pp::matrix result = pp::ode::driver(hydrogen,rmin,rmax,yinit,hinit,acc,eps); 

    double f = result[result.size1()-1,result.size2()-2];

    return pp::vector{f};
}





int main(){
    pp::vector x_max = pp::vector{0,-1};
    pp::vector x_min1 = pp::vector{-4,4};
    pp::vector x_min2 = pp::vector{3,3};
    pp::vector x_min3 = pp::vector{-4,-3};
    pp::vector x_min4 = pp::vector{4,-2};


    pp::vector solution_max = newton(Himmelblau,x_max);
    pp::vector solution_min1 = newton(Himmelblau,x_min1);
    pp::vector solution_min2 = newton(Himmelblau,x_min2);
    pp::vector solution_min3 = newton(Himmelblau,x_min3);
    pp::vector solution_min4 = newton(Himmelblau,x_min4);



    solution_max.print("Himmelblau local max");
    solution_min1.print("Himmelblau local min1");
    solution_min2.print("Himmelblau local min2");
    solution_min3.print("Himmelblau local min3");
    solution_min4.print("Himmelblau local min4");

    pp::vector x_Rosenbruck = pp::vector{0,0};
    pp::vector solution_Rosenbruck = newton(Rosenbruck,x_max);
    solution_Rosenbruck.print("Rosenbruck min");

    //Task B

    
    std::cout << "\n\n";
    //Constant values for convergence and for the ODE driver
    double E_guess=-2;
    
    rmin = 1e-4;
    double f1init = rmin-rmin*rmin; // f at rmin
    double f2init = 1-2*rmin; // f' at rmin
    yinit={f1init,f2init}; //initial position and value of f

    hinit = rmin/10; //Stepsize
    acc=10e-5; //Change
    eps=10e-5; //change

    //Root  function parameters
    double root_acc = 1e-4;
    double root_alpha_min = 1e-4;
    double root_max_iter = 1000;
    //rmax convergence:
    for (rmax=1; rmax<13; rmax++){
        
        pp::vector solution_hydrogen = newton(aux_function,pp::vector{E_guess}, root_acc,root_alpha_min, root_max_iter);

        std::cout << rmax << " " << solution_hydrogen[0] << "\n";
    }
    std::cout << "\n\n";

    rmax=8;
    //rmin convergence:
    for (rmin=1e-5; rmin<rmax; rmin*=5){
        pp::vector solution_hydrogen = newton(aux_function,pp::vector{E_guess}, root_acc,root_alpha_min, root_max_iter);

        std::cout << rmin << " " << solution_hydrogen[0] << "\n";
    }
    std::cout << "\n\n";

     rmin=1e-4;
    //acc convergence
     for (acc=100; acc>1e-7; acc/=10){
        eps=acc;
        pp::vector solution_hydrogen = newton(aux_function,pp::vector{E_guess}, root_acc,root_alpha_min, root_max_iter);

        std::cout << acc << " " << solution_hydrogen[0] << "\n";
    }
    std::cout << "\n\n";

    // plot of E0 function, first E0 is found from converging conditions,
    //  then is is plotted using the driver to generate points
    acc=10e-5;
    acc=10e-5;
    pp::vector solution_hydrogen = newton(aux_function,pp::vector{E_guess}, root_acc,root_alpha_min, root_max_iter);
    double E0 = solution_hydrogen[0];
    
    pp::matrix plot = pp::ode::driver(hydrogen,rmin,rmax,yinit,hinit,acc,eps);
    plot.print();


    


    return 0;
}

