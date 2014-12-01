#!/usr/bin/env gnuplot

set encoding cp1250 # make the minus sign longer
set terminal push
set terminal postscript eps enhanced size 5, 3.5 font "Times, 28"
set output "attard1997.eps"


set xtics 0.05 font "Times,20" offset 0, 0.5
set mxtics 5
set ytics 1.0 font "Times,20" offset 0.5, 0
set mytics 5

set lmargin 5.
set rmargin 1
set tmargin 0.5
set bmargin 2.5

color1 = "#000000"
color2 = "#224488"
color3 = "#aa0000"
color4 = "#803000"
color5 = "#800080"
color6 = "#008000"
color7 = "#808080"
color8 = "#606060"
color9 = "#202020"

set style line 1 lw 3.0 lt 1 lc rgb color1 pt 4   ps 2.0
set style line 2 lw 3.0 lt 1 lc rgb color2 pt 6   ps 2.0
set style line 3 lw 3.0 lt 1 lc rgb color3 pt 8   ps 2.0
set style line 4 lw 3.0 lt 1 lc rgb color4 pt 10  ps 2.0
set style line 5 lw 3.0 lt 1 lc rgb color5 pt 12  ps 2.0
set style line 6 lw 3.0 lt 1 lc rgb color6 pt 14  ps 2.0
set style line 7 lw 3.0 lt 1 lc rgb color7 pt 2   ps 2.0
set style line 8 lw 3.0 lt 2 lc rgb color8 pt 3   ps 2.0
set style line 9 lw 3.0 lt 3 lc rgb color9 pt 1   ps 2.0

set xlabel "Density, {/Symbol-Oblique r}" offset 0, 1.0
#set ylabel "(Excess) chemical potential" offset 2.0, 0
set key left Left reverse spacing 1.5

plot [0.67:0.97][:] \
  "attard1997.dat" u 2:1 w lp ls 1 t "{/Symbol-Oblique m}, Attard 1997", \
  "attard1997.dat" u 2:3 w lp ls 2 t "{/Symbol-Oblique m}^{ex}, EOS", \
  "attard1997.dat" u 2:($3+log($2)) w lp ls 3 t "{/Symbol-Oblique m}^{ex} + log({/Symbol-Oblique r}), EOS", \




unset output
set terminal pop
reset
