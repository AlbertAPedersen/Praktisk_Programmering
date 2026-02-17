CXXFLAGS += -Wall -std=c++23
LDLIBS += -lstdc++ -lm

fig2.png: erf.data Makefile
	echo '\
	set terminal png ;\
	set output "$@" ;\
	plot "$<" index 1 using 1:3 with lines ;\
	' | tee log.fig2.gpi | gnuplot # tee creates log for debugging

fig1.svg: fig1.gpi erf.data
	gnuplot $<

erf.data: main Makefile
	./$< -xmin 0 -xmax 2 -dx 0.5 > $@ 2>log.erf;\
	echo "\n\n">> $@ 2>log.erf;\
	./$< -xmin 0 -xmax 2 -dx 0.225 >> $@ 2>log.erf