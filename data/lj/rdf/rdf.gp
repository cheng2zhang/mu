#!/usr/bin/env gnuplot

set encoding cp1250 # make the minus sign longer
set terminal push
set terminal postscript eps enhanced size 5, 4 font "Times, 28"
set output "rdf.eps"


color1 = "#000000"
color2 = "#224488"
color3 = "#803000"
color4 = "#aa0000"
color5 = "#008000"
color6 = "#800080"
color7 = "#808080"
color8 = "#606060"
color9 = "#202020"

set style line 1 lw 1.0 lt 1 lc rgb color1 pt 5   ps 1.0
set style line 2 lw 1.0 lt 2 lc rgb color2 pt 6   ps 1.5
set style line 3 lw 1.0 lt 3 lc rgb color3 pt 8   ps 1.5
set style line 4 lw 1.0 lt 4 lc rgb color4 pt 10  ps 1.0
set style line 5 lw 1.0 lt 5 lc rgb color5 pt 12  ps 1.0
set style line 6 lw 1.0 lt 6 lc rgb color6 pt 14  ps 1.0
set style line 7 lw 1.0 lt 1 lc rgb color7 pt 2   ps 1.0
set style line 8 lw 1.0 lt 2 lc rgb color8 pt 3   ps 1.0
set style line 9 lw 1.0 lt 3 lc rgb color9 pt 1   ps 1.0

set style line 100 lw 12.0 lt 1 lc rgb "#cccccc"


#tagdx1 = 0.015
#tagdy1 = 0.030
#set label 1000 "(a)" at screen tagdx1,  1.0 - tagdy1
#set label 1001 "(b)" at screen tagdx1,  htl - tagdy1

set multiplot


set size 1.0, 1.0
set origin 0.0, 0.0

set xtics 1.0
set mxtics 5
set xlabel "{/Times-Italic r}" offset 0.5, 0.5

set ytics 0.1
set mytics 5
set ylabel "{/Times-Italic g}({/Times-Italic r})" offset 1.5, 0
set key right top Left reverse spacing 1.25 font "Times, 28"


plot [0.9:4][0.98:1.16] \
   1 w l ls 100 lw 0.5 notitle, \
  "grdfT10rho0.1n256.dat"  u 1:3                w l   ls 1 t "Grand-canonical", \
  "rdfT10rho0.1n256a.dat"  u 1:3  every 5       w l   ls 2 t "Canonical, unscaled", \
  "rdfT10rho0.1n256.dat"   u 1:3  every 5       w l   ls 3 t "Canonical, scaled"



unset multiplot
unset output
set terminal pop
reset

