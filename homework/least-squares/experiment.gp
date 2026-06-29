set terminal svg background "white" size 800,600
set multiplot layout 1,2

#LOGSPACE
set xlabel "Time [days]"; set ylabel "Log(activity) [a.u.]"
set title "Log space"
plot\
"log" index 1 using 1:2 with lines title "Best",\
"log" index 1 using 1:3 with lines title "Upper",\
"log"  index 1 using 1:4 with lines title "Lower"

#Linearspace
set xlabel "Time [days]"; set ylabel "activity [a.u.]"
set title "Linear space"
plot "log"  index 2 using 1:2:3 with errorbars title "Raw",\
"log"  index 3 using 1:2 with lines title "Best",\
"log"  index 3 using 1:3 with lines title "Upper",\
"log"  index 3 using 1:4 with lines title "Lower"

unset multiplot
