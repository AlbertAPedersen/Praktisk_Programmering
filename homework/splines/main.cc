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
int binsearch(const vector& x, double z)
	{/* locates the interval for z by bisection */ 
	assert( z>=x[0] && z<=x[x.size()-1] );//is z even in the range?
	int i=0, j=x.size()-1;
	while(j-i>1){
		int mid=(i+j)/2;
		if(z>x[mid]) i=mid; else j=mid;
		}
	return i;
	}

double linterp(vector x, vector y, double z){
	int i=binsearch(x,z);
  	double dx=x[i+1]-x[i];
  	assert(dx>0);
  	double dy=y[i+1]-y[i];
  	return y[i]+dy/dx*(z-x[i]);
  	}
double linterpInteg(vector x, vector y, double z){ //double[] is an array of doubles/ vector used
	double y_end=linterp(x, y, z);
    double a = (y_end-y[0])/(z-x[0]);
    double b = y[0];
    double y_integral = 1/2*a*z*z +b*z; // y=ax + b -> ax^2/2 +bx
    return y_integral;
}

int main(){
vector x_table = vector(19);
vector y_table = vector(19);

for (int i=0; i<19;i++){;
    double i_double=i*1.0;
    double x=i/2.0;

    double y = std::cos(x);

        std::cout << x << " " << y << "\n";
    
    x_table[i]=x;
        std::cerr << "asd";
    y_table[i]=y;
            std::cerr << "asd";
}

for (int i=0; i<19;i++){
    double z=x_table[i];
    double y_interp = std::cos(x);
    double integral =
        std::cout << x << " " << y << "\n";
    
    x_table[i]=x;
        std::cerr << "asd";
    y_table[i]=y;
            std::cerr << "asd";
}


x_table.print();
    
return 0;
}