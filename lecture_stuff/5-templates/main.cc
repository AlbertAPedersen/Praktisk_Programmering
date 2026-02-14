#include<iostream>
#include<functional>

struct func {
    double operator()(double x){return x*x*x;}
};

double square(double x){return x*x;} // square is pointer
double eval(std::function<double(double)> f, double x=2){
    return f(x);
}


template<typename T> // template for function echo using datatype T.
void echo(const T& arg){
    std::cout << "echo: arg= "<<arg<< "\n";
}

template<typename T>
struct list {
    T* data;
    int size;
    T& operator[](int i){return data[i];}
    list(int n){size=n;data = new T[n];}
    ~list(){size=0;delete[] data;}

    };

template<typename T> //template for future structures that can use print
struct bar {
    T datum;
    void print(){std::cout << "bar: datum= "<< datum << "\n";}
};

int main(){
    echo(1);
    echo(1.235);
    echo("hello");

    bar<int> intbar{1}; // puts int in place of T
    bar<double> doublebar{1.234}; // puts double in place of T etc..
    bar<std::string> stringbar{"hello"};
    intbar.print();
    doublebar.print();
    stringbar.print();
    int n=5;
    list<double> doublelist(n);
    doublelist[0]=1.234;

    std::cout << "square(2)= " << square(2) << "\n";
    std::function<double(double)> f = square; // f is not pointer, but typesafe
    std::cout << "f(2)= " << f(2) << "\n";
    std::cout << "eval(2)= " << eval(f,2) << "\n";
    std::cout << "eval(2)= " << eval(square,2) << "\n";
    func cube;
    std::function<double(double)> g=cube;

     std::cout << "g(2)= " << eval(g,2) << "\n";
    std::cout << "cube(2)= " << cube(2) << "\n";

    double a=1;
    auto h = [a](double x)->double {return x*x*x*x;}; //lambda function /python
    auto q = [&a](double x)->double {return x*x*x*x;}; //lambda function /python
    std::cout << "h(2)=" << h(2) << "\n";
    return 0;
}