set terminal svg background "white" size 800,600
set output "plot.svg"
set multiplot layout 2,2

set xlabel "1/sqrt(N)"; set ylabel "Error"
set grid

#FIT AND R2 ADDED BY AI
set fit quiet
stats "log" index 0 using 4 name "Y" nooutput
f(x) = m*x + b
fit f(x) "log" index 0 using 1:4 via m, b 
SSE = FIT_WSSR
SST = (Y_stddev**2) * Y_records
R2 = 1.0 - (SSE/SST)

set label 1 sprintf("R^2 = %.4f", R2) at graph 0.05, 0.9 front

set title "Task 1 plot, error estimate is linear, an actual error fits quite poorly"
plot "log" index 0 using 1:3 with lines title "Estimated error",\
     "log" index 0 using 1:4 with points pt 7 ps 0.5 title "Actual error",\
     f(x) with lines lc rgb "red" lw 2 title sprintf("Linear Fit (slope = %.4f)", m)

unset label 1

set title "Task 2 singular plot"
plot "log" index 1 using 1:3 with lines title "Halton error",\
     "log" index 1 using 1:5 with lines title "lcg error",\



set title "Task 2 non-singular plot (x*x+y*z)"
plot "log" index 2 using 1:2 with lines title "Halton error",\
     "log" index 2 using 1:3 with lines title "lcg error",\
     "log" index 2 using 1:4 with lines title "c++ standard error"