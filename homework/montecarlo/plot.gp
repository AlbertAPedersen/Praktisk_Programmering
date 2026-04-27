set terminal svg background "white" size 800,600
set output "plot.svg"

set xlabel "1/sqrt(N)"; set ylabel "Error"
set grid

//FIT AND R2 ADDED BY AI
stats "out.txt" index 0 using 4 name "Y" nooutput

f(x) = m*x + b
fit f(x) "out.txt" index 0 using 1:4 via m, b

# FIT_WSSR is the Sum of Squared Residuals from the fit
# (Y_stddev**2 * Y_records) is the Total Sum of Squares
SSE = FIT_WSSR
SST = (Y_stddev**2) * Y_records
R2 = 1.0 - (SSE/SST)

set label 1 sprintf("R^2 = %.4f", R2) at graph 0.05, 0.9 front

plot "out.txt" index 0 using 1:3 with lines title "Estimated error",\
     "out.txt" index 0 using 1:4 with points pt 7 ps 0.5 title "Actual error",\
     f(x) with lines lc rgb "red" lw 2 title sprintf("Linear Fit (slope = %.4f)", m)


