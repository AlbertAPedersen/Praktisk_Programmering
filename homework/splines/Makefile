CXX=g++ -std=c++23  #Compiler and standard
CXXFLAGS = -Wall -Wextra  -O1 #-Werror #Flags for debugging
LDLIBS += -lstdc++ -lm #Links libraries that are already linked

packages = ../packages/matrix_QR.h spline.h

all : out.txt qspline.svg cspline.svg
	cat out.txt

qspline.svg :  qspline.gp out.txt
	gnuplot qspline.gp > qspline.svg

cspline.svg :  cspline.gp out.txt
	gnuplot cspline.gp > cspline.svg

out.txt : main
	./main > out.txt

main : main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

main.o : main.cc $(packages) Makefile
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

clean : 
	$(RM) main *.o out.txt *.svg