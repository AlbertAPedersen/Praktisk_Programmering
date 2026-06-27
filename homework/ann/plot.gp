set terminal svg background "white" size 800,600
set output "plot.svg"
set xlabel "r"
set grid
set key font ",7"
set key spacing 0.6

set multiplot layout 2,2

set key top left
set title "Wavelet evaluated (Same function as training data)"
plot "out.txt" index 0 using 1:2 with lines lw 5 linecolor rgb "black" title "training data",\
     "out.txt" index 0 using 1:3 with lines lw 2 linecolor rgb "red" title "Wavelet evaluated with 1 neuron",\

set title "Interesting function evaluated with different amount of neurons"
plot "out.txt" index 1 using 1:2 with lines lw 5 linecolor rgb "black" title "data",\
     "out.txt" index 1 using 1:3 with lines lw 2 title "1 neurons",\
     "out.txt" index 2 using 1:3 with lines lw 2 title "3 neurons",\
     "out.txt" index 3 using 1:3 with lines lw 2 linecolor rgb "purple"  title "5 neurons",\
     "out.txt" index 4 using 1:3 with lines lw 2 linecolor rgb "red" title "7 neurons",\
     
set key bottom left
set title "derivatives and antiderivatives of wavelet found with ANN (test)"
plot "out.txt" index 5 using 1:2 with lines lw 2 title "ANN Function",\
     "out.txt" index 5 using 1:3 with lines lw 2 title "ANNderivative",\
     "out.txt" index 5 using 1:4 with lines lw 2 title "ANN 2nd derivative",\
     "out.txt" index 5 using 1:5 with lines lw 2 title "ANN antiderivative",\
     "out.txt" index 6 using 1:2 with lines lw 2 dt 2 title "Analytic Function",\
     "out.txt" index 6 using 1:3 with lines lw 2 dt 2 title "Analytic derivative",\
     "out.txt" index 6 using 1:4 with lines lw 2 dt 2 title "Analytic 2nd derivative",\
     "out.txt" index 6 using 1:5 with lines lw 2 dt 2 title "Analytic antiderivative",\

set title "derivatives and antiderivatives of Interesting function found"
plot "out.txt" index 7 using 1:2 with lines lw 2 title "ANN Function",\
     "out.txt" index 7 using 1:3 with lines lw 2 title "ANN derivative",\
     "out.txt" index 7 using 1:4 with lines lw 2 title "ANN 2nd derivative",\
     "out.txt" index 7 using 1:5 with lines lw 2 title "ANN antiderivative",\


