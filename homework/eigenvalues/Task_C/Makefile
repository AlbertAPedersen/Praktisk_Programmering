CXX=g++ -std=c++23  #Compiler and standard something?
CXXFLAGS = -Wall -Wextra  -O1 #-Werror #Flags for debugging
LDLIBS += -lstdc++ -lm #Links libraries that are already linked

packages = ../../packages/matrix_QR.h ../jacobi.h
Ns := $(shell seq 100 100 800)
LOGS := $(Ns:%=log.%)
all : outtimes.txt parallel.svg
	cat outtimes.txt

parallel.svg : outtimes.txt parallel.gp
	gnuplot parallel.gp	>$@

outtimes.txt: $(LOGS) 
#Many targets for parallel
	cat $(LOGS) | sort -n >$@

log.%:main
#time - format "N, elapsed, user" -output to log, running file $ with input N ($*) 
	time -f "$* %e %U" -o $@ ./$< $*

main : main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

main.o : main.cc $(packages) Makefile
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

clean : 
	$(RM) main *.o out.txt *.svg log*