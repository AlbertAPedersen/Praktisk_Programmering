#include<iomanip>
#include<iostream>
#include<thread>
#include"main.h"
#include<vector>


int main(int argc, char** argv) {
    long nthreads = 1, nterms = (int)1e8; /* default values */
        for(int i=0;i<argc;i++) {
            std::string arg = argv[i];
            if(arg=="-nthreads" && i+1<argc) nthreads=std::stoi(argv[i+1]);
            if(arg=="-nterms" && i+1<argc) nterms=static_cast<int>(std::stod(argv[i+1]));
        }

    //data objects for each thread
    std::vector<harm::data> params(nthreads);
    for(int i=0;i<nthreads;i++) {
        params[i].a = 1 + nterms/nthreads*i;
        params[i].b = 1 + nterms/nthreads*(i+1);
    }
    params[params.size()-1].b=nterms+1; /* the enpoint might need adjustment */    


    //prepare threads
    std::vector<std::thread> threads;
    threads.reserve(nthreads); // reserve empty slots for our threads

    for(int i=0;i<nthreads;i++) {
        threads.emplace_back(harm::harm,std::ref(params[i]));
   }

   //join threads (wait for operations to be done)
   for(auto &thread : threads) thread.join();
   //total sum
   double total=0; for(const auto &p : params){total+=p.sum;}
    return 0;
}
