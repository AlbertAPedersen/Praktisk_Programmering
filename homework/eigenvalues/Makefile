CXX=g++ -std=c++23  #Compiler and standard something?
CXXFLAGS = -Wall -Wextra  -O3 #-Werror #Flags for debugging
LDLIBS += -lstdc++ -lm #Links libraries that are already linked

packages = ../packages/matrix_QR.h jacobi.h
all : out.txt convergence_rmax.svg
	cat out.txt

convergence_rmax.svg : out.txt Makefile
#a=5e-10; b=3; 
	echo '\
	set terminal svg background "white" size 800,600;\
	set multiplot layout 1,2;\
	set output "$@";\
	set xlabel "rmax";\
	set ylabel "E0";\
	set title "Convergence plot with dr=0.2";\
	plot "out.txt" index 2 using 1:3 with points title "dr=0.2",\
	"out.txt" index 1 using 1:2 with points title "rmax=5"' | gnuplot



out.txt : main
	./main -rmax $$(seq -s ' ' 1 0.5 10) -dr $$(seq -s ' ' 0.05 0.05 0.5)  > $@

main : main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

main.o : main.cc $(packages) Makefile
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

clean : 
	$(RM) main *.o out.txt plot.svg times.txt