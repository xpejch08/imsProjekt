set terminal png
set output "sir_model_graph.png"
set title "SIR Model Dynamics"
set xlabel "Time"
set ylabel "Population Size"
set key outside
set xrange [0:100]  # Adjust according to your simulation time
plot "population.dat" using 1:2 with lines title "Susceptible", \
     "population.dat" using 1:3 with lines title "Infected", \
     "population.dat" using 1:4 with lines title "Recovered"
set output
