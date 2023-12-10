set terminal png size 1200,600  # Set the size of the output PNG (width, height)
set output "sir_model_graph.png"
set output "sir_model_graph.png"
set title "SIR Model Dynamics"
set xlabel "Time"
set ylabel "Population Size"
set key outside
set xtics 1,1   # Set tic marks at intervals of 1
set xtic ("2014" 0, "2015" 1, "2016" 2, "2017" 3, "2018" 4, "2019" 5, "2020" 6, "2021" 7, "2022" 8, "2023" 9, "2024" 10)  # Map tic marks to corresponding years
set xrange [0:10]  # Adjust according to your simulation time
plot "population.dat" using 1:2 with lines title "Susceptible", \
     "population.dat" using 1:3 with lines title "Infected", \
     "population.dat" using 1:4 with lines title "Recovered", \
     "population.dat" using 1:5 with lines title "Dead to HIV", \
     "population.dat" using 1:6 with lines title "Dead with HIV"
set output
