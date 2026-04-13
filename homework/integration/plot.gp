set terminal svg background "white" size 800,600
set multiplot layout 2,1

set xlabel "Accuracy"; set ylabel "Abs difference"
set title "erf(1)"
set logscale y
set logscale x
set yrange [1e-17 : 0.001]
set xrange [1e-16 : 2]
set grid
plot "out.txt" index 1 using 1:2 with lines title "Y"

#unset multiplot







