#include<iostream>
#include<vector>
#include<string>
#include"../packages/matrix_QR.h"
//#include<tuple>
//#include"lsfit.h"
#include"spline.h"
#include<assert.h>
#include<cmath>

using vector=pp::vector;
int binsearch(const vector& x, double z){/* locates the interval for z by bisection */ 
	assert( z>=x[0] && z<=x[x.size()-1] );//is z even in the range?
	int i=0, j=x.size()-1;
	while(j-i>1){
		int mid=(i+j)/2;
		if(z>x[mid]) i=mid; else j=mid;
		}
	return i; //i is always lower than j.
	}

double linterp(vector x, vector y, double z){

	int i=binsearch(x,z);
  	double dx=x[i+1]-x[i];
  	assert(dx>0);
  	double dy=y[i+1]-y[i];
  	return y[i]+dy/dx*(z-x[i]);
  	}

double linterpInteg(vector x, vector y, double z){ //double[] is an array of doubles/ vector used
    int i=binsearch(x,z);
    double y_integral=0;

    for (int j=0; j<i ;j++){
        //Integral from 0 to i
            double y_start = y[j];
            double y_end = y[j+1];
            double x_start = x[j];
            double x_end = x[j+1];

            double a = (y_end-y_start)/(x_end-x_start);
            double b = y_start - a*x_start;
            y_integral+= (0.5*a*x_end*x_end + b*x_end - (0.5*a*x_start*x_start +b*x_start)); // y=ax + b -> ax^2/2 +bx
    }
        //integral from j to end
        double y_start = y[i];
        double y_end=linterp(x,y,z);
        double x_start = x[i];
        double x_end = z;
        double a = (y_end-y_start)/(x_end-x_start);
        double b = y_start - a*x_start;
        y_integral+= (0.5*a*x_end*x_end +b*x_end - (0.5*a*x_start*x_start +b*x_start)); // y=ax + b -> ax^2/2 +bx
    return y_integral;
}

int main(){
//TASK A
int N_points = 100;
vector x_table = vector(19);
vector y_table = vector(19);
vector interpolation_range_taskA = vector(N_points);
for (int i=0; i<19;i++){;
    double x=i/2.0;
    double y = std::cos(x);
    x_table[i]=x;
    y_table[i]=y;
    std::cout << x << " " << y << "\n";
}

std::cout << "\n\n"; // GNU BLOCK 0^

for (int i=0; i<interpolation_range_taskA.size()-1;i++){
    double end = x_table[x_table.size()-1]-1e-7;
    double dx = end/N_points;
    interpolation_range_taskA[i]=i*dx+1e-8;

    double z=interpolation_range_taskA[i];
    double y_interp = linterp(x_table,y_table,z);
    double integral = linterpInteg(x_table,y_table,z);

    std::cout << z << " " << y_interp << " " << integral << " " << "\n";
}

std::cout << "\n\n"; // GNU BLOCK 1^


//TASK B
vector x_table1 = vector{0,1,2,3,4,5,6,7,8};

vector y_table1 = vector{1,1,1,1,1,1,1,1,1};
vector y_table2 = x_table1;
vector y_table3 = vector{0,1,4,9,16,25,36,49,64};
vector y_table4 = vector(x_table1.size()); 

for (int i = 0; i < x_table1.size(); i++) {
    double x_val = x_table1[i];
    y_table4[i] = std::pow(x_val,3);
    //TABLE VALUES
    std::cout << x_table1[i] << " " << y_table1[i] <<" "<< y_table2[i] << " " << y_table3[i] << " " << y_table4[i]<< "\n"; 

}

std::cout << "\n\n"; // GNU BLOCK 2^

pp::qspline qspline1 = pp::qspline(x_table1,y_table1);
pp::qspline qspline2 = pp::qspline(x_table1,y_table2);
pp::qspline qspline3 = pp::qspline(x_table1,y_table3);
pp::cspline cspline = pp::cspline(x_table1,y_table4);

vector interpolation_range(N_points);

for (int i=0; i<N_points;i++){
    double end = x_table1[x_table1.size()-1]-1e-7;
    double dx = end/N_points;
    interpolation_range[i]=i*dx+1e-8;

}

for (int i=0; i<N_points; i++){
    double z=interpolation_range[i];
    if (z>8.0) break;
    std::cout << z << " " << qspline1.eval(z) << " " <<qspline1.deriv(z) << " " << qspline1.integ(z) << "\n";

}


std::cout << "\n\n"; //GNU block 3^
for (int i=0; i<N_points; i++){
    double z=interpolation_range[i];
    std::cout << z << " " << qspline2.eval(z) << " " <<qspline2.deriv(z) << " " << qspline2.integ(z) << "\n";


}

std::cout << "\n\n"; //GNU block 4^
for (int i=0; i<N_points; i++){
    double z=interpolation_range[i];
    std::cout << z << " " << qspline3.eval(z) << " " <<qspline3.deriv(z) << " " << qspline3.integ(z) << "\n";

}


std::cout << "\n\n"; //GNU block 5^

for (int i=0; i<N_points; i++){
    double z=interpolation_range[i];
    std::cout << z << " " << cspline.eval(z) << " " <<cspline.deriv(z) << " " << cspline.integ(z) << "\n";

}




    
return 0;
}