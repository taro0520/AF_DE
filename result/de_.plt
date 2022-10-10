set grid
set term png
set output 'de.png'
set xlabel 'Generation'
set ylabel 'Fitness'
set title 'DE'
set xrange [0:3000]
set xtics 0,500,3000
set yrange [1:25]
set ytics nomirror
plot 'data_de.txt' using 1:2 smooth bezier with lines linestyle 1 title 'de'
# 1000P 30D 3000G