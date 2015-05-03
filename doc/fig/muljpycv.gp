#!/usr/bin/env gnuplot

set encoding cp1250 # make the minus sign longer
set terminal push
set terminal postscript eps enhanced size 5, 3.5 font "Times, 24"
set output "muljpycv.eps"



rhomax = 1.0 + 1e-5


set xtics 0.2 font "Times,20" offset 0, 0.5
set mxtics 2
set ytics 2.0 font "Times,20" offset 0.5, 0
set mytics 2

set lmargin 5.5
set rmargin 1
set tmargin 0.7
set bmargin 2.3

color1  = "#224488"
color2  = color1
color3  = "#aa0000"
color4  = color3
color5  = "#008000"
color6  = color5
color7  = color1
color8  = color3
color9  = color5
color10 = "#404040"

set style line 1  lw 2.0 lt 1 lc rgb color1  pt 4   ps 1.8
set style line 2  lw 2.0 lt 1 lc rgb color2  pt 12  ps 2.5
set style line 3  lw 2.0 lt 1 lc rgb color3  pt 8   ps 2.0
set style line 4  lw 2.0 lt 1 lc rgb color4  pt 10  ps 2.0
set style line 5  lw 2.0 lt 1 lc rgb color5  pt 6   ps 2.0
set style line 6  lw 2.0 lt 1 lc rgb color6  pt 14  ps 2.0
set style line 7  lw 3.0 lt 4 lc rgb color7  pt 2   ps 2.0
set style line 8  lw 3.0 lt 2 lc rgb color8  pt 3   ps 2.0
set style line 9  lw 3.0 lt 5 lc rgb color9  pt 1   ps 2.0
set style line 10 lw 4.0 lt 1 lc rgb color10 pt 1   ps 2.0

set xlabel "Density, {/Symbol-Oblique r}" offset 0, 0.9
set ylabel "Excess chemical potential, {/Symbol-Oblique b m}^{ex}" offset 2.0, 0
set key left Left reverse spacing 1.5 font "Times, 24"

plot [0:rhomax][:7] \
  "../../data/lj/muljT1.5pycv.dat" u 1:3 w l ls 7 t "{/Symbol-Oblique b m}@_{/Times-Italic c}^{ex}, Reference", \
  "" u 1:4 every 5 w p ls 1 t "{/Symbol-Oblique b m}@_{/Times-Italic c}^{ex}, {/Symbol D} = {/Times-Italic h B}", \
  "" u 1:6 every 5 w p ls 2 t "{/Symbol-Oblique b m}@_{/Times-Italic c}^{ex}, {/Symbol D} = {/Times-Italic -B}", \
  "" u 1:9 w l ls 8 t "{/Symbol-Oblique b m}@_{/Times-Italic v}^{ex}, Reference", \
  "" u 1:10 every 5 w p ls 3 t "{/Symbol-Oblique b m}@_{/Times-Italic v}^{ex}, {/Symbol D} = {/Times-Italic h B}", \
  "" u 1:12 every 5 w p ls 4 t "{/Symbol-Oblique b m}@_{/Times-Italic v}^{ex}, {/Symbol D} = {/Times-Italic -B}", \
  "" u 1:17 w l ls 10 t "{/Symbol-Oblique b m}^{ex}, EOS", \
  0 w l lt 4 lc rgb "#c0c0c0" notitle



unset output
set terminal pop
reset
