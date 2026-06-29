set terminal svg background "white" size 800,600
set multiplot layout 2,2

set xlabel "X"; set ylabel "Y"
set grid
set title "Oscillator no friction"
y(x)=sin(x)
yprime(x)=cos(x)

set key bottom right
set key font ",10"
set yrange [-1.1:1.1]
set title "Harmonic oscillator"

plot "out.txt" index 0 using 1:3 with lines lw 4 linecolor rgb "black" title "Y_{analytic}",\
"out.txt" index 0 using 1:2 with lines lw 1.5 dt 1 linecolor rgb "red" title "twostep",\
"out.txt" index 1 using 1:2 with lines lw 1.5 dt 1 linecolor rgb "cyan" title "Corrected twostep",\
"out.txt" index 2 using 1:2 with lines lw 1.5 dt 1 linecolor rgb "magenta" title "onestep"

unset yrange
set title "Absolute error(y_{Analytic} - y_{solved}) "
plot "out.txt" index 0 using 1:6 with lines linecolor rgb "red" title "twostep",\
"out.txt" index 1 using 1:6 with lines linecolor rgb "cyan" title "Twostep with correction",\
"out.txt" index 2 using 1:6 with lines linecolor rgb "magenta" title "onestep",\



set logscale y
set yrange [10e-13:5]
set title "Accumulated Residual (R)"

plot "out.txt" index 0 using 1:4 with lines linecolor rgb "red" title "twostep",\
"out.txt" index 1 using 1:4 with lines linecolor rgb "cyan" title "twostep with correction",\
"out.txt" index 2 using 1:4 with lines linecolor rgb "magenta" title  "onestep"


set yrange [10e-16:10e-3]
set logscale y
set title "Accumulated weighted residual (R/N_{points})"

plot "out.txt" index 0 using 1:5 with  lines linecolor rgb "red" title "twostep",\
"out.txt" index 1 using 1:5 with lines linecolor rgb "cyan" title "Twostep with correction",\
"out.txt" index 2 using 1:5 with lines linecolor rgb "magenta" title "onestep"







#unset multiplot







