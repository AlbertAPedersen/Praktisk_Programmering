CXXFLAGS += -Wall -std=c++23
LDLIBS += -lstdc++ -lm


all: erf.svg sgamma.svg

erf.svg: all.data Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	plot "$<" index 0 using 1:2 with lines,\
	 	 "$<" index 1 using 1:2 with points;\
	' | tee log.erf.gpi | gnuplot # tee creates log for debugging
	
sgamma.svg: all.data Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	plot "$<" index 0 using 1:3 with lines,\
	 	 "$<" index 1 using 1:3 with points;\
	' | tee log.erf.gpi | gnuplot # tee creates log for debugging

all.data: main Makefile
#clear file
	>$@
#	using parameters xmin=0, xmax=2 dx=0.1 in main read outputs x, erf, gamma and echo into erf.data
# 	and put stderr into log.erf
	./main -xmin 0 -xmax 2 -dx 0.1 | while read x erf sgamma; do\
		echo "$$x $$erf" $$sgamma>> $@ ; \
	done 2>> log.erf


clean:
	rm -f main *.o *.data log.erf erf.svg log.*

	

