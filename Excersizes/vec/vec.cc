#include<cmath>
#include<numbers> // c++20
#include"vec.h"
#include"../eps/sfuns.h"
#include<limits>
/*

OBSOLETE CODE - Changing everything in both .cc and .h is too
                tedius

namespace vecmath{
    
 // arithmetic
    vec<T>&  vec::operator+=(const vec<T>& other){
        x+=other.x;
        y+=other.y;
        z+=other.z;
        return *this;
    }
    
    vec<T>& vec::operator-=(const vec<T>& other){
        x-=other.x;
        y-=other.y;
        z-=other.z;
        return *this;
    }
    vec<T>& vec::operator*=(T scalar){
        x*=scalar;
        y*=scalar;
        z*=scalar;
        return *this;
    }
    vec<T>& vec::operator/=(T scalar){
        x/=scalar;
        y/=scalar;
        z/=scalar;
        return *this;
    }

vec<T> operator-(const vec<T>& v1){
    T x=-v1.x;
    T y=-v1.y;
    T z=-v1.z;
    return vec(x,y,z); 
}  // Flip direction

vec<T> operator-(const vec<T>& v1, const vec<T>& v2){
    T x = v1.x - v2.x;
    T y = v1.y - v2.y;
    T z = v1.z - v2.z;
    return vec(x,y,z);
}; // Substract
vec<T> operator+(const vec<T>& v1, const vec<T>& v2){
    T x = v1.x + v2.x;
    T y = v1.y + v2.y;
    T z = v1.z + v2.z;
    return vec(x,y,z);
}; // add

vec<T> operator*(const vec<T>& v1, T scalar){
    T x = v1.x*scalar;
    T y = v1.y*scalar;
    T z = v1.z*scalar;
    return vec(x,y,z);
};  // multiply
vec<T> operator*(T scalar, const vec<T>& v1){
    T x = v1.x*scalar;
    T y = v1.y*scalar;
    T z = v1.z*scalar;
    return vec(x,y,z);
}; // Specify  commutativity
vec<T> operator/(const vec<T>& v1, T scalar){
    T x = v1.x/scalar;
    T y = v1.y/scalar;
    T z = v1.z/scalar;
    return vec(x,y,z);
};  // Divide by constant

void vec::print(const std::string& s) const {
std::cout << s << x << " " << y << " " << z << std::endl;
}

template<typename T> 
T vec::norm() const {
    // Noget bøvl med int?
    return std::sqrt(std::pow(x,2)+std::pow(y,2)+std::pow(z,2));
}

template<typename T> 
vec<T> vec::unit() const {
    return *this/vecmath::vec::norm();
}

template<typename T> 
T dot(vecmath::vec<T> a, vec<T> b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T> 
vec<T> vecproduct(vec<T> a,vec<T> b){
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

template<typename T>  
bool approx(const T a, const T b){
    return sfuns::approx(a,b);
};


}

*/