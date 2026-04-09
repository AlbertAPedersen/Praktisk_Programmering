CXX=g++ -std=c++23  #Compiler and standard
CXXFLAGS = -Wall -Wextra  -O1 #-Werror #Flags for debugging
LDLIBS += -lstdc++ -lm #Links libraries that are already linked

packages = ../packages/matrix_QR.h ode.h

all : out.txt plot.svg
	cat out.txt 

plot.svg : out.txt plot.gp
	gnuplot plot.gp > plot.svg	

out.txt : main
	./main > out.txt

main : main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

main.o : main.cc $(packages) Makefile
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

clean : 
	$(RM) main *.o out.txt *.svg