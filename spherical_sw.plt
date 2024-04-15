set terminal png
set output "spherical_square_well.png"

set title "Integration Routines for Spherically Symmetric Born Approx"
set xlabel "log 10 Number of Steps N"
set ylabel "log 10 Relative Error"

f(x) = a + b*x
g(x) = c + d*x

fit f(x) "spherical_sw_output.dat" using 1:4 via a,b
fit g(x) "spherical_sw_output.dat" using 1:5 via c,d

plot "spherical_sw_output.dat" using 1:4 with lines title "Monte Carlo Integration", \
     "spherical_sw_output.dat" using 1:5 with lines title "Milne's Rule", \
        f(x) title sprintf("Monte Carlo Fit: y = %.2f + %.2f*x", a, b), \
        g(x) title sprintf("Milne's Rule Fit: y = %.2f + %.2f*x", c, d)