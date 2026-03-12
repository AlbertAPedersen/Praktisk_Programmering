set terminal svg background "white" size 800,600
set xlabel ""; set ylabel ""
set title "Wavefunctions"
plot "out.txt" index 3 using 1:2 with lines title "First state",\
    "out.txt" index 4 using 1:2 with lines title "Second state",\
    "out.txt" index 5 using 1:2 with lines title "Third state"