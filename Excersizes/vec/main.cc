//NOTE: this .cc file is almost pure AI, to do comprehensive tests of functions. I would rather spend the time writing the code than testing it manually. Also, my tests may have errors as well.

#include<cmath>
#include<numbers> // c++20
#include <random>
#include <cassert>
#include"vec.h"
#include"../eps/sfuns.h"
#include<limits>
#include<complex>
#include <iomanip> // For setprecision
#include <type_traits>

using complex = std::complex<double>;
constexpr complex I = complex(0,1);
    template <typename T>
void run_tests(std::string name, T x1, T y1, T z1, T x2, T y2, T z2) {
    std::cout << "\n================ " << name << " TEST ================\n";
    
    // 1. Construction
    vecmath::vec<T> v1{x1, y1, z1};
    vecmath::vec<T> v2{x2, y2, z2};

    // Print with high precision to see float vs double differences
    std::cout << std::setprecision(10);
    
    // 2. Output & Basic Ops
    std::cout << "v1: " << v1 << "\n";
    std::cout << "v2: " << v2 << "\n";

    // 3. Addition / Subtraction
    auto v_sum = v1 + v2;
    std::cout << "Sum (v1+v2): " << v_sum << "\n";
    
    auto v_diff = v1 - v2;
    std::cout << "Diff (v1-v2): " << v_diff << "\n";

    // 4. Dot Product
    // If you implemented the conjugate fix, Complex Dot should include conj()
    auto d = vecmath::dot(v1, v2);
    std::cout << "Dot Product: " << d << "\n";

    // 5. Cross Product (Vector Product)
    auto cp = vecmath::vecproduct(v1, v2);
    std::cout << "Cross Product: " << cp << "\n";

    // 6. Norm
    // This checks if your library correctly handles return types (int -> double, complex -> real)
    auto n1 = v1.norm(); 
    std::cout << "Norm(v1): " << n1 << "\n";

    // 7. Scalar Math
    // We use a small scalar. For complex, we just use a real scalar (2) to keep it simple.
    // Note: casting 2 to T ensures it works even if T is complex.
    // However, usually scalar mult is vec<T> * T (scalar).
    // Let's assume scalar is just 'double' or 'int' usually. 
    // For this generic test, we'll multiply by 2.
    auto v_mult = v1 * 2; 
    std::cout << "Scalar Mult (v1 * 2): " << v_mult << "\n";
    
    // Check for division (Integers will truncate!)
    auto v_div = v1 / 2;
    std::cout << "Scalar Div (v1 / 2): " << v_div << "\n";
}

int main() {
    using namespace std::complex_literals; // Allows 1i, 2i syntax

    // --- 1. Integers ---
    // Expect truncation in division!
    // Dot: 1*4 + 2*5 + 3*6 = 32
    run_tests<int>("INTEGER", 
        1, 2, 3, 
        4, 5, 6
    );

    // --- 2. Float (Low Precision) ---
    // Norm should differ slightly from double after ~7 digits
    run_tests<float>("FLOAT", 
        1.0f, 2.0f, 3.0f, 
        4.0f, 5.0f, 6.0f
    );

    // --- 3. Double (Standard Precision) ---
    run_tests<double>("DOUBLE", 
        1.0, 2.0, 3.0, 
        4.5, 5.5, 6.5 // Using .5 to test non-integers
    );

    // --- 4. Long Double (High Precision) ---
    // Use 'L' suffix. Useful for scientific simulations.
    run_tests<long double>("LONG DOUBLE", 
        1.123456789123L, 2.0L, 3.0L, 
        4.0L, 5.0L, 6.0L
    );

    // --- 5. Complex <Double> ---
    // The Ultimate Test.
    // v1 = {1+1i, 2+0i, 3-2i}
    // v2 = {0+2i, 1+1i, 2+2i}
    // If your dot product uses conjugate, result will differ from simple multiplication.
    using Comp = std::complex<double>;
    run_tests<Comp>("COMPLEX", 
        Comp{1, 1}, Comp{2, 0}, Comp{3, -2}, 
        Comp{0, 2}, Comp{1, 1}, Comp{2, 2}
    );

    return 0;
}

    
    /* OLD
    vecmath::vec v1{1,2,3};
    vecmath::vec v2{1,2,4};
    
    v1.print("Vector:");
    std::cout << v1.norm()<< "\n";

    std::cout <<"Dot: " << vecmath::dot(v1,v2)<<"\n";

    vecmath::vec v3=vecmath::vecproduct(v1,v2);

    v3.print("Vecproduct");

    std::cout << vecmath::approx(v1,v2);

    v3+=v1;
    v3.print("Post addition");
    v3-=v1;
    v3.print("Post subtraction");

    v3*=2;
    v3.print("Post mult");

    v3/=2;
    v3.print("Post div");

    vecmath::vec v4 = v3 - v2;
    v4.print("Post div");

    vecmath::vec v6 = v4.unit();
    
    v6.print("s");


    return 0;
}
}
 OLD CODE*/