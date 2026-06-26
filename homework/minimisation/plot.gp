set terminal svg background "white" size 800,600
set output "plot.svg"

set xlabel "r"
set grid
analytical(x) = x * exp(-x)

set title " "
plot "out.txt" index 1 using 1:2 with lines title "data",\
     "out.txt" index 2 using 1:2 with lines lw 5 title "fit (forward params)",\
     "out.txt" index 3 using 1:2 with lines lw 2 linecolor rgb "orange" title "fit (central params)"




