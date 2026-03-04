#pragma once
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include<functional>
#include<ranges>
#include<cstdlib>


namespace pp{
    struct vector {
        //Constructors
        std::vector<double> data;
        vector() = default; //Default constructor
        vector(int n) : data(n) {}
        vector(std::initializer_list<double> list) : data(list) {}
        vector(const vector&) = default; // Copy
        vector(vector&&) noexcept = default; //move

        vector& operator=(const vector&) = default;     // Copy assignment
        vector& operator=(vector&&) noexcept = default; //Move assignment
    

        inline int size() const {return data.size();} //inline function to gain vector size
        void resize(int n) {data.resize(n);} // change size using std::vector function

        
        inline double& operator()(int i) {return data[i];} // Changed as older compilers cant pass [i,j]
        inline double& operator[](int i) {return data[i];} // Added for consistency, does the same
        inline const double& operator()(int i) const {return data[i];} // Changed as older compilers cant pass [i,j]
        inline const double& operator[](int i) const {return data[i];} // Added for consistency, does the 
        
        //Member functions
        vector& operator+=(const vector& other){
            for(int i=0;i<size();i++)(*this)[i]+=other[i]; //Simple vector addition. This[i] returns its own i'th value while other[i] is the adduct.
            return (*this);
            }
        
        vector& operator-=(const vector& other){
            for(int i=0;i<size();i++)(*this)[i]-=other[i]; //Simple vector addition. This[i] returns its own i'th value while other[i] is the adduct.
            return (*this);
        }
        
        vector& operator*=(const double c){
            for(int i=0;i<size();i++)(*this)[i]*=c;
            return (*this);
        }

        vector& operator/=(const double c){
            for(int i=0;i<size();i++)(*this)[i]/=c;
            return (*this);
        }
        
        //struct functions
        double norm() const{
            double squares=0; 
            for(int i=0;i<size();i++){
                squares+= (*this)[i]*(*this)[i];
            }
            return std::sqrt(squares);
        }

        void print(std::string s="") const { //Debug print
        std::cout<<s<<" ";
        for(auto &x : data) std::cout<<x<<" ";
        std::cout<<"\n";
        }   

        vector map(std::function<double(double)> f) const{ 
        //Maps a function onto each scalar in the vector to make a new vector
        //(squaring done by vector squared = v.map([] double x {return x*x;});)
            vector New(size());
            for(int i=0;i<size();i++)New.data[i]=f(data[i]);
            return New;

        }
    };
    //non member operations/functions    
        vector operator+(vector a, const vector& b)	{ a+=b ; return a; }
        vector operator-(vector a)					{ a*=-1; return a; }
        vector operator-(vector a, const vector& b)	{ a-=b ; return a; }
        vector operator*(vector a, const double c)	{ a*=c ; return a; }
        vector operator*(const double c, vector a)	{ a*=c ; return a; }
        vector operator/(vector a, const double c)	{ a/=c ; return a; }

        
        double dot(const vector& a, const vector& b){
            if(a.size() !=b.size()) throw std::runtime_error("Size=("+std::to_string(a.size())+")!=size"+std::to_string(b.size()));
            double sum=0;
            for (int i=0;i<a.size();i++){
                    sum+=a[i]*b[i];
                }
            return sum;
        }

        vector randomvec(int size){
            vector a(size);
            for (int i=0;i<size;i++){
                a[i]=(std::rand()%10);
            }
            return a;
        }


    struct matrix {
        //Constructors
        std::vector<pp::vector> cols;
        matrix()=default;
        matrix(int n,int m) : cols(m, pp::vector(n)) {} //make a matrix of m std::vectors each containing a pp::vector that is n long.
        matrix(const matrix& other)=default;  //copy make
        matrix(matrix&& other)=default;        //move make
        matrix& operator=(const matrix& other)=default; //copy overwrite
        matrix& operator=(matrix&& other)=default; //move overwrite

        int size1() const {return cols.empty() ? 0 : cols[0].size(); } // ? is ternary operator (condition ? value_if_true : value_if_false) If not empty, count first column.
        int size2() const {return cols.size();}     //simply count columns

        double& operator()(int i, int j){return cols[j][i];} //works for older c++
        double& operator[](int i, int j){return cols[j][i];} // works only in new, but is nicely readable
        const double& operator()(int i, int j)const{return cols[j][i];}
        const double& operator[](int i, int j)const{return cols[j][i];}

        
        vector& operator[](int i){return cols[i];}
        const vector& operator[](int i) const {return cols[i];}

        vector& operator()(int i){return cols[i];}
        const vector& operator()(int i) const {return cols[i];}


        void setid(){   //makes identity matrix
            if(size1()!=size2())throw std::runtime_error("non-square matrix\n");
            for(int i=0;i<size1();i++){
                (*this)[i,i]=1;
                for(int j=i+1;j<size1();j++)(*this)[i,j]=(*this)[j,i]=0;
            }
        }

        matrix transpose() const{
            matrix R(size2(),size1());
            for(int i=0;i<size1();i++)
            for(int j=0;j<size2();j++)
                R[j,i]=(*this)[i,j];
            return R;
        }

        double get (int i, int j) {return cols[j][i];}
        void set(int i, int j, double value){cols[j][i] = value;}

        vector get_col(int j) {return (*this)[j];}

        void set_col(int j,const vector& cj) {cols[j]=cj;}

        matrix& operator+=(const matrix& B){
            for(int i=0;i<size2();i++)(*this)[i]+=B[i];
            return *this;
            }
        matrix& operator-=(const matrix& B){
            for(int i=0;i<size2();i++)(*this)[i]-=B[i];
            return *this;
            }
        matrix& operator*=(const double c){
            for(int i=0;i<size2();i++)(*this)[i]*=c;
            return *this;
            }
        matrix& operator/=(const double c){
            for(int i=0;i<size2();i++)(*this)[i]/=c;
            return *this;
            }
        matrix& operator*=(const matrix& B){ 
            //Uses a "Rank-1 update rather than sclar product method"
            //For matrix of size m x n, multiply by n x p, resulting in m x p
            int n = (*this).size2(); //Columns of A
            int n2 = B.size1(); //nrows of B
            if (n!=n2) throw std::invalid_argument("size mismatch");

            //new matrix dimensions
            int m = (*this).size1(); //nrows of A
            int p = B.size2(); //ncols of B
            matrix New(m,p); //empty matrix of size m,p

            for (int k = 0; k < n ; k++){		//for columns in A, take column k
            const vector& Acol = (*this)[k]; 
                for (int j = 0 ; j < p ; j++){	//For columns in b, take scalar B[k,j]
                    double Bkj=B(k,j);
                
                    for (int i = 0 ; i < m; i++){  //for rows in A / New, calculate scalar value 
                        New(i,j)+=Acol(i)*Bkj; // add Aik*Bkj
                    }
                }
            }
            *this = std::move(New); 		
            return *this;
        }

        matrix  operator^(int ex){
            matrix New((*this).size1(),(*this).size2());
            New.setid();
            matrix base = (*this);
            for (int i=0;i<ex;i++){
                New*=base;
            }
            return New;
        }

        void print(std::string s="") const{
            printf("%s\n",s.c_str());
            for(int i=0;i<size1();i++){
                for(int j=0;j<size2();j++)printf("%10.5g ",(*this)[i,j]);
                printf("\n");
            }
        }
    };
    // non-member func
        matrix randommatrix(int n, int m){
            matrix A(n,m);
            for(int i=0; i<m; i++){
                A.set_col(i, randomvec(n));
            }
            return A;
        }

        bool approx(double x, double y, double acc=1e-6, double eps=1e-6){
            if(std::abs(x-y) < acc) return true;
            if(std::abs(x-y) < eps*std::max(std::abs(x),std::abs(y))) return true;
            return false;
        }

        bool approx(const vector& a, const vector& b, double acc=1e-6, double eps=1e-6){
            if(a.size() != b.size()) return false;
            for(int i=0;i<a.size();i++)
                if(!approx(a[i],b[i],acc,eps)) return false;
            return true;
        }

        bool approx(const matrix& a, const matrix& b, double acc=1e-6, double eps=1e-6){
            if(a.size1() != b.size1()) return false;
            if(a.size2() != b.size2()) return false;
            for(int i=0;i<a.size2();i++)
                if(!approx(a[i],b[i],acc,eps)) return false;
            return true;
        }
    //Non-member matrix
        matrix operator+(matrix& A, const matrix& B){
        for(int i=0;i<A.size2();i++)A[i]+=B[i];
        return A;
        };

        matrix operator-(matrix& A, const matrix& B){
            for(int i=0;i<A.size2();i++)A[i]-=B[i];
            return A;
        };

        matrix operator*(const matrix& A, const matrix& B){
            matrix New = A;
            return New*=B;
        };
        
        matrix operator*(matrix A, const double c){
            for(auto &col : A.cols) col*=c;
            return A;
        };
        matrix operator*(const double c, matrix A){
            for(auto &col : A.cols) col*=c;
            return A;
        };
        matrix operator/(matrix A, const double c){
            for(auto &col : A.cols) col/=c;
            return A;
        };
        vector operator*(const matrix& A, const vector& v){
            vector r(A.size1());
            for(int j=0;j<A.size2();j++){
                double vj=v[j];
                for(int i=0;i<A.size1();i++) r[i]+=A(i,j)*vj;
                }
            return r;
        };
    

    
    struct QR{
         //Constructors
         matrix Q, R;
         int m,n;
        QR(const matrix& A) : Q(A), R(A.size2(),A.size2()) {
            n=A.size2(); //A columns
            m=A.size1(); //A rows
        
            //orthogonalize with GS algorithm
            for(int i=0;i<n;i++){
                R(i,i)=Q[i].norm(); //diagonal constains norms of of each column in Q
                Q(i)/=R[i,i];

                for (int j=i+1;j<n;j++){ 
                    R(i,j)=dot(Q[i],Q[j]);
                    Q[j]-=Q[i]*R[i,j];
                }
            }
        }   
            double det(){
                double prod=1;
                for (int i=0;i<n;i++){
                    prod*=R(i,i);
                }
                return prod;
            }

            vector solve(const vector& b){ 
                //for equation QRx=B find x by using QtQRx  = Rx  =  QtB. Backsubstitution as upper=right
                if (b.size()!=m) throw std::runtime_error("Size =("+ std::to_string(b.size())+")!=size m"+std::to_string(m));
                
                // y=Q^t*B
                    vector y=Q.transpose()*b;
                    vector x(b.size());
                    for (int i=n-1;i>=0;i--){
                        double sum=0;
                        
                        for (int k=i+1;k<n;k++){
                            sum+=R(i,k)*x(k);
                        }
                        x[i]=(y[i]-sum)/R(i,i);
                    }
                return x;
                }
            
            matrix inverse(){
                if (m!=n) throw std::runtime_error("Not square:"+std::to_string(n)+"+"+std::to_string(m));
                if (det()==0) throw std::runtime_error("Determinant is 0, no inverse");

                //Ax=I

                matrix Ain(n,n);
                matrix I(n,n);
                I.setid();
                for(int i=0; i<I.size2();i++){
                    Ain[i]=solve(I[i]); //solves Axi=1, to get column i of X
                }
                return Ain;
            }
                
            
        }; 
            

    }
    



