set term X11       

plot "force.dat" with impulses

set term png
set output "xyz.png"

plot "force.dat" using 1:2 title "data1", "force.dat" using 1:3 title "data2"



