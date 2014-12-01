#!/usr/bin/env gnuplot

set encoding cp1250 # make the minus sign longer
set terminal push
set terminal postscript eps enhanced size 5, 3.8 font "Times, 28"
set output "mugamma.eps"


set xtics 0.2 font "Times,20" offset 0, 0.5
set mxtics 2
set ytics 0.1 font "Times,20" offset 0.5, 0
set mytics 5

set lmargin 5.5
set rmargin 1
set tmargin 1
set bmargin 3

color1 = "#000000"
color2 = "#224488"
color3 = "#aa0000"
color4 = "#228822"
color9 = "#808080"

set style line 1 lw 4.0 lt 1 lc rgb color1 pt 4 ps 2.5
set style line 2 lw 4.0 lt 1 lc rgb color1 pt 5 ps 2.5
set style line 3 lw 4.0 lt 2 lc rgb color2 pt 6 ps 2.5
set style line 4 lw 4.0 lt 2 lc rgb color2 pt 7 ps 2.5
set style line 5 lw 4.0 lt 3 lc rgb color3 pt 8 ps 2.5
set style line 6 lw 4.0 lt 3 lc rgb color3 pt 9 ps 2.5
set style line 7 lw 4.0 lt 4 lc rgb color4 pt 2 ps 2.0
set style line 8 lw 12.0 lt 4 lc rgb color4 pt 1 ps 2.5
set style line 9 lw 4.0 lt 1 lc rgb color9 pt 3 ps 2.0

#htl = 0.53
#hth = 1 - htl
#
#tagdx1 = 0.015
#tagdy1 = 0.030
#set label 1000 "(a)" at screen tagdx1,  1.0 - tagdy1
#set label 1001 "(b)" at screen tagdx1,  htl - tagdy1

#set multiplot
#set size 1.0, hth
#set origin 0.0, htl

set xlabel "Density, {/Symbol-Oblique r}" offset 0, 0.5
set ylabel "{/Symbol-Oblique g}, from Eq. (5)" offset 2.5, 0
set key at graph 0.9, 0.5 right Left reverse spacing 1.0 font "Times, 20"

plot [:0.7][0.45:0.7] \
  "../../data/iemuhspy.dat"       u 1:5 w p ls 1 t "PY", \
  "../../data/iemuhssqrscp.dat"   u 1:5 w p ls 3 t "Quadratic, {/Symbol \266}_{/Symbol-Oblique r} {/Times-Italic P} consistent", \
  "../../data/iemuhssqrscmu.dat"  u 1:5 w p ls 4 t "Quadratic, {/Symbol \266}@^2_{/Symbol-Oblique r, x} {/Symbol-Oblique m} consistent", \
  "../../data/iemuhshcscp.dat"    u 1:5 w p ls 5 t "HC, {/Symbol \266}_{/Symbol-Oblique r} {/Times-Italic P} consistent", \
  "../../data/iemuhshcscmu.dat"   u 1:5 w p ls 6 t "HC, {/Symbol \266}@^2_{/Symbol-Oblique r, x} {/Symbol-Oblique m} consistent", \
  "../../data/iemuhsirscp.dat"    u 1:5 w p ls 7 t "Rowlinson, {/Symbol \266}_{/Symbol-Oblique r} {/Times-Italic P} consistent", \
  "../../data/iemuhsirscmu.dat"   u 1:5 w p ls 8 t "Rowlinson, {/Symbol \266}@^2_{/Symbol-Oblique r, x} {/Symbol-Oblique m} consistent", \



#unset multiplot
unset output
set terminal pop
reset
