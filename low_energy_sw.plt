set terminal png
set output "low_energy_sw.png"

set title "Integration Routines for Low Energy Born Approx"
set xlabel "log 10 Number of Steps N"
set ylabel "log 10 Relative Error"

f(x) = a + b*x

fit [2:8] f(x) "low_energy_sw_output.dat" using 1:3 via a,b

plot "low_energy_sw_output.dat" using 1:3 with lines title "Monte Carlo Integration", \
        f(x) title sprintf("Monte Carlo Fit: y = %.2f + %.2f*x", a, b)