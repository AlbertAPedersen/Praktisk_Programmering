CXX=g++ -std=c++23  #Compiler and standard something?
CXXFLAGS = -Wall -Wextra  -O1 #-Werror #Flags for debugging
LDLIBS += -lstdc++ -lm #Links libraries that are already linked

packages = ../../packages/matrix_QR.h ../jacobi.h
all : out.txt convergence.svg wavefunctions.svg
	cat out.txt
wavefunctions.svg : out.txt wavefunctions.gp
	gnuplot wavefunctions.gp > wavefunctions.svg	

convergence.svg : out.txt convergence.gp
	gnuplot convergence.gp > convergence.svg

out.txt : main
#Change convergence values later
	./main -rmax $$(seq -s ' ' 3 0.5 10) -dr $$(seq -s ' ' 0.01 0.01 0.3)  > $@

main : main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

main.o : main.cc $(packages) Makefile
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

clean : 
	$(RM) main *.o out.txt *.svg