set terminal svg background "white" size 800,600
set output "plot.svg"
set multiplot layout 2,2

set xlabel "r"
set grid
analytical(x) = x * exp(-x)

set title " "
plot "out.txt" index 4 using 1:2 with lines lw 3 linecolor rgb "red"  title "f",\
     analytical(x) with lines title "Analytical f" linecolor rgb "black"

plot "out.txt" index 1 using 1:2 with lines title "rmax convergence"

set logscale x
set format x "10^{%L}"
plot "out.txt" index 2 using 1:2 with lines title "rmin convergence"

plot "out.txt" index 3 using 1:2 with lines title "eps,acc convergence"



