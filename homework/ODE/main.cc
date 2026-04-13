#include<iostream>
#include<vector>
#include<tuple>
#include"ode.h"
#include"../packages/matrix_QR.h"
#include<cmath>
#include<functional>

// TASK A

/*
For the function u''=-u:
y0=f
y1=f'
The derivative is thus
y0'=y1
y1'=-y0
*/
std::function<pp::vector(double,pp::vector)> u = [](double x, pp::vector y){
    double dy0 = y[1];
    double dy1 = -y[0];
    pp::vector dy = pp::vector{dy0,dy1};
    return dy;
};


std::function<pp::vector(double,pp::vector)> pendulum = [](double x, pp::vector y){
    double theta = y[0];
    double omega = y[1]; 
    pp::vector dydt = pp::vector{omega, -0.25*omega - 5.0*std::sin(theta)};
    return dydt; 
};

// TASK B
double epsilon;
std::function<pp::vector(double,pp::vector)> orbit = [](double x, pp::vector y){
    double dy0 = y[1];
    double dy1 = 1-y[0]+epsilon*y[0]*y[0]; 
    pp::vector dy = pp::vector{dy0,dy1};
    return dy; 
};

// TASK C
pp::vector m = pp::vector{1,1,1};
double G = 1.0; 


std::function<pp::vector(double,pp::vector)> body_3 = [](double x_null, pp::vector z){

    //pp::vector z = pp::vector(dx1,dy1,dx2,dy2,dx3,dy3,x1,y1,x2,y2,x3,y3)
    if(z.size()!=12) throw std::invalid_argument("Wrong size of z for three body");

    pp::vector x = pp::vector{z[6],z[8],z[10]};
    pp::vector y = pp::vector{z[7],z[9],z[11]};

    pp::vector ddx = pp::vector(3);
    pp::vector ddy = pp::vector(3);

    for (int i=0; i<3;i++){
        for (int j=0; j<3;j++){
            if (j!=i){
                double r_x= x[j]-x[i];
                double r_y= y[j]-y[i];
                double r=std::sqrt(r_x*r_x+r_y*r_y);
                double r_cube=std::pow(r,3);

                ddx[i]+=(r_x)/r_cube;
                ddy[i]+=(r_y)/r_cube;
            }
        }
    }

    pp::vector z_new = pp::vector{ddx[0],ddy[0],ddx[1],ddy[1],ddx[2],ddy[2],
                                    z[0],z[1],z[2],z[3],z[4],z[5]};

    return z_new; 
};



int main(){
    double a=-5;
    double b=5;
    pp::vector yinit = pp::vector{2,-2};
    double hinit=0.001;
    double acc=0.01;
    double eps=0.01;
    
    // NOTE: The ODE driver outputs a matrix with columns x,y0,y1
    
    pp::matrix result = pp::ode::driver(u,a,b,yinit,hinit,acc,eps);
    result.print();
    std::cout << "\n";

    a=0;
    b=10;
    yinit = pp::vector{3.141-0.1,0.0};


    pp::matrix result_pendulum = pp::ode::driver(pendulum,a,b,yinit,hinit,acc,eps);

    result_pendulum.print();
    std::cout << "\n";

    // TASK B
    a=0.0;
    b=40*3.14;
    yinit = pp::vector{1,0};
    hinit = 0.01;
    acc = 0.00001;
    eps = 0.000001;
    epsilon=0;


    pp::matrix result_orbit_1 = pp::ode::driver(orbit,a,b,yinit,hinit,acc,eps);
    result_orbit_1.print();
    std::cout<< "\n";

    hinit = 0.01;
    acc = 0.01;
    eps = 0.01;
    epsilon=0;

    yinit = pp::vector{1,-0.7};
    pp::matrix result_orbit_2 = pp::ode::driver(orbit,a,b,yinit,hinit,acc,eps);
    result_orbit_2.print();
    std::cout<< "\n";

    yinit = pp::vector{1,-0.7};
    epsilon=0.04;
    pp::matrix result_orbit_3 = pp::ode::driver(orbit,a,b,yinit,hinit,acc,eps);
    result_orbit_3.print();
    std::cout<< "\n";
    std::cout<< "\n";
    
    
    //Task C
    double x1=0.97000436;
    double x2=-x1;
    double x3=0;

    double y1=-0.24308753;
    double y2=-y1;
    double y3=0;

    double dx3=-0.93249737;
    double dx1=-0.5*dx3;
    double dx2=-0.5*dx3;

    double dy3=-0.8647314;
    double dy1=-0.5*dy3;
    double dy2=-0.5*dy3;

    double T=6.32591398;
    
    a=0;
    b=T;
    hinit = 0.0001*T;
    acc = 0.000001;
    eps = 0.000001;

    yinit = pp::vector{dx1,dy1,dx2,dy2,dx3,dy3,x1,y1,x2,y2,x3,y3};

    pp::matrix result_3body = pp::ode::driver(body_3,a,b,yinit,hinit,acc,eps);
    std::cout << "t              dx1,          dy1,    dx2,      dy2,         dx3,        dy3,         x1,       y1,     x2,       y2,        x3,        y3        ";
    result_3body.print();
    std::cout<< "\n";


    return 0;
}