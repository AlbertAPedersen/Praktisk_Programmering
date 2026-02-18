CXXFLAGS += -Wall -std=c++23
LDLIBS += -lstdc++ -lm


all: erf.svg sgamma.svg cgamma.svg

erf.svg: all.data Makefile
	echo '\
	set terminal svg ;\
	set output "$@" ;\
	plot "$<" index 0 using 1:2 with lines,\
	 	 "$<" index 1 using 1:2 with points;\
	' | tee log.erf.gpi | gnuplot # tee creates log for debugging

cgamma.svg: all.data Makefile
	echo 'set terminal svg background "white"; \
	set output "$@"; \
	set key off; \
	set ticslevel 0; \
	set view 70, 345; \
	set zrange [0:6] ;\
	set pm3d; \
	set palette viridis;\
	set colorbox;\
	splot "$<" index 2 using 1:2:3 with pm3d\
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
	./main -xmin -4.5 -xmax 4.5 -dx 0.04, -imin -2.5 -imax 2.5 -di 0.04 | while read x erf sgamma; do\
		echo "$$x $$erf" $$sgamma>> $@ ; \
	done 2>> log.erf


clean:
	rm -f main *.o *.data log.erf erf.svg log.*

	
