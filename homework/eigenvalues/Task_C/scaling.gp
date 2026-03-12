set terminal svg background "white" size 800,600
set xlabel "Size [n]"; set ylabel "Time [s]"
set title "Scaling of Jabobi algorithm"
a=5e-10; b=3; \
f(x) = a * x**b;\
fit f(x) "outtimes.txt" using 1:3 via a,b;\
set label sprintf("Power Fit (elapsed): t ≈ %.2e * N^{%.2f}", a, b) at graph 0.05, 0.9;\
plot "outtimes.txt" using 1:2 with points title "Elapsed",\
    "outtimes.txt" using 1:3 with points title "User time",\
    f(x) with lines title "O(N^b) Fit"
