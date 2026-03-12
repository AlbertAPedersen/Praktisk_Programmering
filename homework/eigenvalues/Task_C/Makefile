CXX=g++ -std=c++23  #Compiler and standard something?
CXXFLAGS = -Wall -Wextra  -O1 #-Werror #Flags for debugging
LDLIBS += -lstdc++ -lm #Links libraries that are already linked

packages = ../../packages/matrix_QR.h ../jacobi.h
Ns := $(shell seq 100 100 800)
LOGS := $(Ns:%=log.%)


all : outtimes.txt parallel.svg

parallel.svg: outtimes.txt parallel.gp
#Silent fitting
	@gnuplot parallel.gp > parallel.svg
	

benchmark:
	@$(MAKE) clean
	@echo "Benchmark results:\n" -o benchmark_results.txt 
	@/usr/bin/time -o benchmark_results.txt -f"Single thread elapsed:%e  User:%U" $(MAKE) -j1 
	@$(MAKE) clean
	@/usr/bin/time -a -o benchmark_results.txt -f"8 threads elapsed:%e  User:%U" $(MAKE) -j8
	@cat benchmark_results.txt


outtimes.txt: $(LOGS) 
#Many targets for parallel
	@cat $(LOGS) | sort -n >$@
	@rm  $(LOGS)


log.%:main
#time - format "N, elapsed, user" -output to log, running file $ with input N ($*) 
	@/usr/bin/time -f "$* %e %U" -o $@ ./$< $*

main : main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

main.o : main.cc $(packages) Makefile
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

clean : 
	$(RM) main *.o outtimes.txt *.svg log* *.log