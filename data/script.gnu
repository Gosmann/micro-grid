set term X11       

set datafile separator ","

#plot "m1_cost_best.csv" using 0:1

set term png
set output "xyz.png"

plot "m1_cost_best.csv" using 0:3 

#plot "m1_cost_best.txt" using 1:2 title "data1" 

#plot "force.dat" using 1:2 title "data1", "force.dat" using 1:3 title "data2"



