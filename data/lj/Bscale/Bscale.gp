#!/usr/bin/env gnuplot

set encoding cp1250 # make the minus sign longer
set terminal push
set terminal postscript eps enhanced size 5, 7 font "Times, 28"
set output "Bscale.eps"


color1 = "#000000"
color2 = "#224488"
color3 = "#803000"
color4 = "#aa0000"
color5 = "#008000"
color6 = "#800080"
color7 = "#808080"
color8 = "#606060"
color9 = "#202020"

set style line 1  lw 1.0 lt 1 lc rgb color1 pt 5   ps 2.0
set style line 2  lw 1.0 lt 2 lc rgb color2 pt 7   ps 2.0
set style line 3  lw 1.0 lt 3 lc rgb color3 pt 8   ps 2.0
set style line 4  lw 1.0 lt 4 lc rgb color4 pt 10  ps 2.0
set style line 5  lw 1.0 lt 5 lc rgb color5 pt 12  ps 2.0
set style line 6  lw 1.0 lt 6 lc rgb color6 pt 14  ps 2.0
set style line 7  lw 1.0 lt 1 lc rgb color7 pt 2   ps 2.0
set style line 8  lw 1.0 lt 2 lc rgb color8 pt 3   ps 2.0
set style line 9  lw 1.0 lt 3 lc rgb color9 pt 1   ps 2.0

set style line 11 lw 1.0 lt 1 lc rgb color1 pt 4   ps 2.0
set style line 12 lw 1.0 lt 2 lc rgb color2 pt 6   ps 2.0

set style line 100 lw 5.0 lt 3 lc rgb "#777777"

htl = 0.50
hth = 1 - htl

tagdx1 = 0.015
tagdy1 = 0.030
set label 1000 "(a)" at screen tagdx1,  1.0 - tagdy1
set label 1001 "(b)" at screen tagdx1,  htl - tagdy1

set multiplot


set lmargin 5.5
set rmargin 1
set tmargin 0.5
set bmargin .0



set size 1.0, hth
set origin 0.0, htl

set xtics 0.2
set mxtics 2
unset xlabel
set ylabel "Ideal {/Symbol-Oblique g}" offset 1.5, 0
set key right bottom Left reverse spacing 1.25 font "Times, 28"


set format x ""
set ytics 1.0 offset 0.5, 0
set mytics 2

plot [0:1.6][:] \
  "Bscale.dat"  u 1:(($5 == 1)?$2:1/0)               w lp ls 1 lw 3 t "{/Times-Italic T} = 1, {/Symbol-Oblique r} = 0.7", \
  ""            u 1:(($5 == 2)?$2:1/0)               w lp ls 2 lw 3 t "{/Times-Italic T} = 10, {/Symbol-Oblique r} = 0.3", \
  0 w l ls 100 lw 0.5 notitle



set size 1.0, htl
set origin 0.0, 0.0

set bmargin 4
set format x "%g"
set xlabel "Scaling of the bridge function {/Times-Italic B}({/Times-Italic r}), {/Times-Italic s}"

set ytics 2
set mytics 2
set key right bottom Left reverse spacing 1.25 font "Times, 28"

set ylabel "{/Symbol-Oblique b m}^{ex}" offset 2.0, 0

plot [0:1.6][:-1] \
  -3.485 w l ls 100 t "Reference", \
  "Bscale.dat"  u 1:(($5 == 1)?$3:1/0) w lp ls 1  lw 3 t "{/Times-Italic T} = 1,  {/Symbol-Oblique r} = 0.7, {/Symbol-Oblique g} = 0", \
  ""            u 1:(($5 == 1)?$4:1/0) w lp ls 11 lw 3 t "{/Times-Italic T} = 1,  {/Symbol-Oblique r} = 0.7, {/Symbol-Oblique g} = 2/3", \
  0 w l ls 100 lw 0.5 notitle




unset multiplot
unset output
set terminal pop
reset
