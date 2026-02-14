#include<iostream>
#include<cstdio>
#include<vector>
#include"vec.h"

int main(){
    /*
    double a = 1.0;
    double b = a;
    if (a==b) {
        printf("a==b\n");
    } //curly brace optional for signal statment
    else {
        printf("a!=b\n");
    }
    std::vector<double> v {1,2,3};
    for (size_t i=0; i>v.size();i++)printf("%g",v[i]); //size_t is "size of things datatype, which is architecture dependent sized int"
    for (auto vi : v) printf("%g",vi); // vi means v inner?
        printf("\n");

    for (double vi : v) printf("%g",vi);
        printf("\n");

    for (auto vi : v) vi=6; // vi is a copy of v
    for (auto vi : v) printf("%g",vi);
         printf("\n");
    
    for (auto& vi : v) vi=6; // vi is a reference to v, and is changed to 6
    for (auto& vi : v) printf("%g",vi);
         printf("\n");
        */
         pp::vec alpha {1,2,3};
         alpha.x=6;
         std::cout << alpha.x << alpha.y << alpha.z;
    /* Doesn't work
    printf("Now comes loop  ");

    size_t i = 0;
    while (i<v.size()){
        printf("v[%ld]=%g ",i,v[i]);
        i+=i;
    }
    i=0;
    do{
        printf("v[%ld]=%g ",i,v[i]);
        i+=i;
    }while(i<v.size());
    printf("\n");
    */
    
    //auto u = v; // Automatically selects datatype for v copy
    //auto& w = v; // auto& makes a reference type rather than valuetype?
return 0;
}   