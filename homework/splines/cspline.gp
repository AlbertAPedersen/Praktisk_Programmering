set terminal svg background "white" size 800,600
set multiplot layout 1,2

set xlabel "X"; set ylabel "Y"
set title "Task C - Interpolant, derivative and integral"
set grid
plot "out.txt" index 2 using 1:5 with points title "Table values",\
"out.txt" index 6 using 1:2 with lines title "Interpolated value",\
"out.txt" index 6 using 1:3 with lines title "Interpolated derivative",\
"out.txt" index 6 using 1:4 with lines title "Interpolated Integral"


set xlabel "X"; set ylabel "Y"
set title "Task C - Gnuplot spline comparison"
set grid
plot "out.txt" index 2 using 1:5 with points title "Table values",\
"out.txt" index 6 using 1:2 with lines title "Interpolated value",\
"out.txt" index 2 using 1:5 smooth csplines title "gnuplot spline" with lines

unset multiplot







