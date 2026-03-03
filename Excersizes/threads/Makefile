CXX=g++ -std=c++23  #Compiler and standard something?
CXXFLAGS = -Wall -Wextra #-Werror -O  #Flags for debugging
LDLIBS += -lstdc++ -lm #Links libraries that are already linked
TIME = time --format "$$nthreads %e %U" --append --output $@
N = 1e9

all : out.times threads.svg
	cat out.times

threads.svg: out.times Makefile
	echo '\
	set terminal svg background "white";\
	set terminal svg ;\
	set title "CPU times 12 logical processors";\
	set output "$@" ;\
	plot "$<" index 0 using 1:2 with linespoints title "Elapsed time",\
	 	 "$<" index 0 using 1:3 with linespoints title "Total CPU work";\
	' | tee log.erf.gpi | gnuplot # tee creates log for debugging

out.times : main Makefile
	>$@
	>log.main
	for nthreads in 1 2 3 4 5 6 7 8 9 10 11 12 13 14; do \
		$(TIME) ./main -nthreads $$nthreads -nterms $(N) >>log.main ;\
	done

main : main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

main.o : main.cc main.h
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

clean : 
	$(RM) main *.o out.times 