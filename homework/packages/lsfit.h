#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>

namespace pp{
    struct lsfit{
        vector R; // R
        matrix A; //design
        vector weights;
        QR decomp; // QR decomposition to finr R
        vector coefficients; //coefficients
        
        lsfit(const std::vector<std::function<double(double)>> fs,const vector x,const vector y, const vector delta=vector()) : A(), decomp(), coefficients() {
            if (x.size()!=y.size()) throw std::runtime_error("lsfit not possible due to size difference");
            if (delta.size()!=0){
                if (delta.size()!=x.size()) throw std::runtime_error("Incorrect number of deltavalues");
            }
            //Solving Ax=b
            int m = x.size();
            int n = fs.size();
            
            vector b = vector(m); 

            A=matrix(m,n);
            for(int i=0;i<m;i++){
                double y_uncertainty = (delta.size() == m) ? delta[i] : 1.0; //ternary:: if size=m return delta[i], else 1.0
                b(i)=y[i]/y_uncertainty;
                for(int j=0; j<n;j++){
                    A[i,j]=(fs[j](x[i])) / y_uncertainty; //Weighted matrix entries
                }
            }
            decomp = QR(A);
            //Solve Rc=Qty. Returns C.
            coefficients = decomp.solve(b);
            //coefficients.resize(m);
        }

        matrix covariance(){
            matrix R_in = decomp.R_in();
            matrix SIGMA = R_in*((R_in).transpose());
            return SIGMA;
        }
    }; // struct lsfit



}//namespace
