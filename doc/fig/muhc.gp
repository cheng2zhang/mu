#!/usr/bin/env gnuplot

set encoding cp1250 # make the minus sign longer
set terminal push
set terminal postscript eps enhanced size 5, 8 font "Times, 28"
set output "muhc.eps"


set xtics 0.2 font "Times,20" offset 0, 0.5
set mxtics 2
set ytics 1.0 font "Times,20" offset 0.5, 0
set mytics 5

set lmargin 4.5
set rmargin 1
set tmargin 2.0
set bmargin 2.3

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

htl = 0.5
hth = 1 - htl

#tagdx1 = 0.015
#tagdy1 = 0.030
#set label 1000 "(a)" at screen tagdx1,  1.0 - tagdy1
#set label 1001 "(b)" at screen tagdx1,  htl - tagdy1

set multiplot
set size 1.0, hth
set origin 0.0, htl
set title "(a) HC closure, {/Symbol \266}_{/Symbol-Oblique r} {/Times-Italic P}-consistent" offset 0, -0.5

set xlabel "Density, {/Symbol-Oblique r}" offset 0, 1.0
set ylabel "Excess chemical potential, {/Symbol-Oblique b m}^{ex}" offset 2.0, 0
set key left Left reverse spacing 1.3 font "Times, 28"

plot [:0.7][:] \
  "../../data/D3P.dat"              u 1:4   w l   ls 7 t "Ref., Mayer sampling", \
  "../../data/iemuhshcscp.dat"      u 1:2   w p   ls 1 t "Eq. (7), {/Symbol-Oblique g} = 0", \
  "../../data/iemuhshcscp.dat"      u 1:3   w p   ls 2 t "Eq. (7), {/Symbol-Oblique g} = 2/3", \
  "../../data/iemuhshcscp.dat"      u 1:4   w p   ls 3 t "Eqs. (7) and (8)", \
  "../../data/iemuhshcscp.dat"      u 1:13  w p   ls 4 t "Eqs. (7) and (19)", \
  "../../data/iemuhshcscp.dat"      u 1:15  w p   ls 5 t "Eq. (21)", \
  "../../data/iemuhshcscp.dat"      u 1:11  w p   ls 6 t "Eq. (22)", \



set size 1.0, htl
set origin 0.0, 0.0
set title "(b) HC closure, {/Symbol \266}@^2_{/Symbol-Oblique r x} {/Symbol-Oblique m}-consistent" offset 0, -0.5

plot [:0.7][:] \
  "../../data/D3P.dat"              u 1:4   w l   ls 7 t "Ref., Mayer sampling", \
  "../../data/iemuhshcscmu.dat"     u 1:2   w p   ls 1 t "Eq. (7), {/Symbol-Oblique g} = 0", \
  "../../data/iemuhshcscmu.dat"     u 1:3   w p   ls 2 t "Eq. (7), {/Symbol-Oblique g} = 2/3", \
  "../../data/iemuhshcscmu.dat"     u 1:4   w p   ls 3 t "Eqs. (7) and (8)", \
  "../../data/iemuhshcscmu.dat"     u 1:13  w p   ls 4 t "Eqs. (7) and (19)", \
  "../../data/iemuhshcscmu.dat"     u 1:15  w p   ls 5 t "Eq. (21)", \
  "../../data/iemuhshcscmu.dat"     u 1:11  w p   ls 6 t "Eq. (22)", \



unset multiplot
unset output
set terminal pop
reset
