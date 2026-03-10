CXX=g++ -std=c++23  #Compiler and standard something?
CXXFLAGS = -Wall -Wextra  -O3 #-Werror #Flags for debugging
LDLIBS += -lstdc++ -lm #Links libraries that are already linked


all : out.txt times.txt plot.svg
	cat out.txt
	cat times.txt

plot.svg : times.txt Makefile
	echo '\
	set terminal svg background "white" size 800,600;\
	set output "$@";\
	set xlabel "Matrix Size (N)";\
	set ylabel "Time (seconds)";\
	set title "QR Decomposition of NxN";\
	a=5e-10; b=3; \
	f(x) = a * x**b;\
	fit f(x) "times.txt" using 1:2 via a,b;\
	set label sprintf("Power Fit: t ≈ %.2e * N^{%.2f}", a, b) at graph 0.05, 0.9;\
	plot "times.txt" using 1:2 with points title "Measured Data", \
	     f(x) with lines title "O(N^b) Fit";' | gnuplot



out.txt : main
	./main > $@

times.txt : main
	> $@
	for N in $$(seq 100 100 2200); do \
		time --format "$$N %e" --output $@ --append \
		./$< -size $$N 1>out ;\
	done 


main : main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

main.o : main.cc matrix_QR.h Makefile
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

clean : 
	$(RM) main *.o out.txt plot.svg times.txt