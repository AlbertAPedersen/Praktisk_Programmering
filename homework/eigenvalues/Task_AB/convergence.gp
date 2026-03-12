set terminal svg background "white" size 800,600
set multiplot layout 1,2 title "Hydrogen ground state"

set xlabel "rmax"; set ylabel "E0 [hartree]"
set title "Convergence plot with dr=0.05"
plot "out.txt" index 2 using 1:3 with lines title "dr=0.05"

set title "Convergence plot with rmax=5"
set xlabel "dr"; set ylabel "E0 [hartree]"
plot "out.txt" index 1 using 2:3 with lines title "rmax=7"

unset multiplot