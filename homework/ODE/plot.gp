set terminal svg background "white" size 800,600
set multiplot layout 2,3

set xlabel "X"; set ylabel "Y"
set title "function u''=-u"
set grid
plot "out.txt" index 0 using 1:2 with lines title "Y",\
"out.txt" index 0 using 1:3 with line title "dy/dx"

set xlabel "X"; set ylabel "Y"
set title "Oscillator with friction"
set grid
plot "out.txt" index 1 using 1:2 with lines title "Y",\
"out.txt" index 1 using 1:3 with lines title "dy/dx"


set xlabel "X"; set ylabel "Y"
set title "Orbit 1"
set grid
set xrange [-2:2]
set yrange [-2:2]
plot "out.txt" index 2 using (1/$2)*cos($1):(1/$2)*sin($1) with points notitle 

set xlabel "X"; set ylabel "Y"
set title "Orbit 2"
set xrange [-5:5]
set yrange [-5:5]
set grid
plot "out.txt" index 3 using (1/$2)*cos($1):(1/$2)*sin($1) with lines notitle 

set xlabel "X"; set ylabel "Y"
set title "Orbit 2"
set grid
plot "out.txt" index 4 using (1/$2)*cos($1):(1/$2)*sin($1) with lines notitle 

set xlabel "X"; set ylabel "Y"
set title "3-body 8"
set grid
set xrange [-2:2]
set yrange [-2:2]
plot "out.txt" using 8:9 with lines lw 5  title "Body 1", \
     "out.txt" using 10:11 with lines lw 3  title "Body 2", \
     "out.txt" using 12:13 with lines lw 1 title "Body 3"

#unset multiplot







