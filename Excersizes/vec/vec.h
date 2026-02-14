#pragma once
#include <iostream>
#include <string>
#include"../eps/sfuns.h"
#include<complex>
#include <type_traits>
namespace vecmath{
template<typename T>    
struct vec {
    T x=0, y=0, z=0;

    // Rule of 0, no constructors declared.

    // arithmetic
    vec&  operator+=(const vec& other){
        x+=other.x;
        y+=other.y;
        z+=other.z;
        return *this;
    }
    
    vec& operator-=(const vec& other){
        x-=other.x;
        y-=other.y;
        z-=other.z;
        return *this;
    }
    vec& operator*=(T scalar){
        x*=scalar;
        y*=scalar;
        z*=scalar;
        return *this;
    }
    vec& operator/=(T scalar){
        x/=scalar;
        y/=scalar;
        z/=scalar;
        return *this;
    }
    
    void print(const std::string& s) const {
    std::cout << s << x << " " << y << " " << z << std::endl;
    }

    // utility
    void set(T a, T b, T c) { x = a; y = b; z = c; };

    T norm() const {
    // Noget bøvl med int?
    return std::sqrt(std::abs(x)*std::abs(x)
                    +std::abs(y)*std::abs(y)+std::abs(z)*std::abs(z));
}

    vec unit() const {
    return *this/vec::norm();
}


    // stream output
    friend std::ostream& operator<<(std::ostream& os, const vec<T>& v) {
            os << "{" << v.x << "," << v.y << "," << v.z << "}";
            return os;
        }

    // "non-member" operators i guess they are now
    
    friend vec operator-(const vec& v1){
        T x=-v1.x;
        T y=-v1.y;
        T z=-v1.z;
        return vec(x,y,z); 
    }  // Flip direction
    
    friend vec operator-(const vec& v1, const vec& v2){
        T x = v1.x - v2.x;
        T y = v1.y - v2.y;
        T z = v1.z - v2.z;
        return vec(x,y,z);
    }; // Substract
 
    friend vec operator+(const vec& v1, const vec& v2){
        T x = v1.x + v2.x;
        T y = v1.y + v2.y;
        T z = v1.z + v2.z;
        return vec(x,y,z);
    }; // add

    friend vec operator*(const vec& v1, T scalar){
        T x = v1.x*scalar;
        T y = v1.y*scalar;
        T z = v1.z*scalar;
        return vec(x,y,z);
    };  // multiply

  
    friend vec operator*(T scalar, const vec& v1){
        T x = v1.x*scalar;
        T y = v1.y*scalar;
        T z = v1.z*scalar;
        return vec(x,y,z);
    }; // Specify  commutativity


    friend vec operator/(const vec& v1, T scalar){
        T x = v1.x/scalar;
        T y = v1.y/scalar;
        T z = v1.z/scalar;
        return vec(x,y,z);
    };  // Divide by constant    
};




template<typename T> 
T dot(const vec<T>& a, const vec<T>& b) {
    if constexpr (requires { typename T::value_type; }) { // if T requires "value_type" at runtime: (builtins do not require valuetype)
        // For complex types, return the complex dot product
        return a.x * std::conj(b.x) + a.y * std::conj(b.y) + a.z * std::conj(b.z);
    } else {
        // For float/int, use standard math
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
}


template<typename T> 
vec<T> vecproduct(vec<T> a,vec<T> b){
    //Complex vecproductS
    T x = a.y*b.z - a.z*b.y;
    T y = a.z*b.x - a.x*b.z;
    T z = a.x*b.y - a.y*b.x;
  
    return vec{x,y,z};
}



template<typename T> 
 bool approx(const vec<T>& a, const vec<T>& b){
	if (!sfuns::approx(a.x,b.x)||
    (!sfuns::approx(a.y,b.y))||
	(!sfuns::approx(a.z,b.z)))
    return false;
    else return true;
	}

 }