set terminal png
set output "population_graph.png"
set title "Dynamika Populace"
set xlabel "Čas"
set ylabel "Velikost Populace"
set xrange [0:365]
plot "population.dat" using 1:2 with lines title "Populace"
set output
