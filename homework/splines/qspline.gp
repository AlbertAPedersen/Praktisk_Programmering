set terminal svg background "white" size 800,600
set multiplot layout 2,2


set xlabel "X"; set ylabel "Y"
set title "Task A plot"
set grid
plot "out.txt" index 0 using 1:2 with points title "Table value",\
"out.txt" index 1 using 1:2 with lines title "Interpolated Value",\
"out.txt" index 1 using 1:3 with lines title "Interpolated integral"

set xlabel "X"; set ylabel "Y"
set title "Task B plot 1"
set grid
plot "out.txt" index 2 using 1:2 with points title "Table value",\
"out.txt" index 3 using 1:2 with lines title "Interpolated value",\
"out.txt" index 3 using 1:3 with lines title "Interpolated derivative",\
"out.txt" index 3 using 1:4 with lines title "Interpolated Integral"

set xlabel "X"; set ylabel "Y"
set title "Task B plot 2"
set grid
plot "out.txt" index 2 using 1:3 with points title "Table value",\
"out.txt" index 4 using 1:2 with lines title "Interpolated value",\
"out.txt" index 4 using 1:3 with lines title "Interpolated derivative",\
"out.txt" index 4 using 1:4 with lines title "Interpolated Integral"

set xlabel "X"; set ylabel "Y"
set title "Task B plot 3"
set grid
plot "out.txt" index 2 using 1:4 with points title "Table value",\
"out.txt" index 5 using 1:2 with lines title "Interpolated value",\
"out.txt" index 5 using 1:3 with lines title "Interpolated derivative",\
"out.txt" index 5 using 1:4 with lines title "Interpolated Integral"



