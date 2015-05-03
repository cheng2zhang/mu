#!/usr/bin/env gnuplot

set encoding cp1250 # make the minus sign longer
set terminal push
set terminal postscript eps enhanced size 5, 7 font "Times, 24"
set output "muhspylam.eps"
set multiplot


rhomax = 1.0 + 1e-5


set xtics 0.2 font "Times,20" offset 0, 0.5
set mxtics 2
set ytics 5.0 font "Times,20" offset 0.5, 0
set mytics 5

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

color11 = "#800080"
color12 = color11
color13 = "#804000"
color14 = color13
color17 = color11
color18 = color13
color20 = "#c0c000"

set style line 1  lw 2.0 lt 1 lc rgb color1  pt 4   ps 1.8
set style line 2  lw 2.0 lt 1 lc rgb color2  pt 12  ps 2.5
set style line 3  lw 2.0 lt 1 lc rgb color3  pt 8   ps 2.0
set style line 4  lw 2.0 lt 1 lc rgb color4  pt 10  ps 2.0
set style line 5  lw 2.0 lt 1 lc rgb color5  pt 6   ps 2.0
set style line 6  lw 2.0 lt 1 lc rgb color6  pt 14  ps 2.0
set style line 7  lw 4.0 lt 4 lc rgb color7  pt 2   ps 2.0
set style line 8  lw 3.0 lt 2 lc rgb color8  pt 3   ps 2.0
set style line 9  lw 3.0 lt 5 lc rgb color9  pt 1   ps 2.0
set style line 10 lw 4.0 lt 1 lc rgb color10 pt 1   ps 2.0

set style line 11 lw 2.0 lt 1 lc rgb color11 pt 12  ps 2.5
set style line 12 lw 2.0 lt 1 lc rgb color12 pt 4   ps 1.8
set style line 13 lw 2.0 lt 1 lc rgb color13 pt 10  ps 2.0
set style line 14 lw 2.0 lt 1 lc rgb color14 pt 8   ps 2.0
#set style line 15 lw 2.0 lt 1 lc rgb color15 pt 14  ps 2.0
#set style line 16 lw 2.0 lt 1 lc rgb color16 pt 6   ps 2.0
set style line 17 lw 3.0 lt 3 lc rgb color17 pt 2   ps 2.0
set style line 18 lw 3.0 lt 6 lc rgb color18 pt 3   ps 2.0
#set style line 19 lw 3.0 lt 7 lc rgb color19 pt 1   ps 2.0
set style line 20 lw 2.0 lt 8 lc rgb color20 pt 1   ps 2.0


htt = 0.48
htb = 1 - htt

ldx = 0.02
ldy = 0.02

set label "(a)" at screen ldx, 1-ldy
set label "(b)" at screen ldx, htb-ldy


set size 1, htt
set origin 0, htb

set ylabel "Excess chemical potential, {/Symbol-Oblique b m}^{ex}" offset 2.0, 0
set key left Left reverse spacing 1.5 font "Times, 24"

plot [0:rhomax][0:20] \
  2*x*pi/6*(5-2*x*pi/6)/(1-x*pi/6)**2 + 2*log(1-x*pi/6) w l ls 20 t "{/Symbol-Oblique b m}@_{/Times-Italic v}^{ex}, Exact", \
  "../../data/hs/muhspylamr.dat" u 1:3 w l ls 7 t "{/Symbol-Oblique b m}@^{ex}_{{/Symbol-Oblique l}{/Times-Italic r}} , Reference", \
  ""              u 1:5 every 5::4 w p ls 1 t "{/Symbol-Oblique b m}@^{ex}_{{/Symbol-Oblique l}{/Times-Italic r}} , {/Symbol D} = {/Times-Italic h B}", \
  "../../data/hs/muhspylamf.dat" u 1:3 w l ls 8 t "{/Symbol-Oblique b m}@^{ex}_{{/Symbol-Oblique l}{/Times-Italic f}} , Reference", \
  ""              u 1:5 every 5::4 w p ls 3 t "{/Symbol-Oblique b m}@^{ex}_{{/Symbol-Oblique l}{/Times-Italic f}} , {/Symbol D} = {/Times-Italic h B}", \
  "../../data/hs/Pmuhsvs12.dat" u 1:4 w l ls 10 t "{/Symbol-Oblique b m}^{ex}, VS12", \
  -1 notitle



set size 1, htb
set origin 0, 0

set xlabel "Density, {/Symbol-Oblique r}" offset 0, 0.9

plot [0:rhomax][0:21] \
  "../../data/hs/muhspylamc.dat" u 1:3 w l ls 7 t "{/Symbol-Oblique b m}@^{ex}_{{/Symbol-Oblique l}{/Times-Italic c}} , Reference", \
  ""              u 1:5 every 5::4 w p ls 1 t "{/Symbol-Oblique b m}@^{ex}_{{/Symbol-Oblique l}{/Times-Italic c}} , {/Symbol D} = {/Times-Italic h B}", \
  "../../data/hs/muhspylamh.dat" u 1:3 w l ls 8 t "{/Symbol-Oblique b m}@^{ex}_{{/Symbol-Oblique l}{/Times-Italic h}} , Reference", \
  ""              u 1:5 every 5::4 w p ls 3 t "{/Symbol-Oblique b m}@^{ex}_{{/Symbol-Oblique l}{/Times-Italic h}} , {/Symbol D} = {/Times-Italic h B}", \
  "../../data/hs/muhspylamt.dat" u 1:3 w l ls 9 t "{/Symbol-Oblique b m}@^{ex}_{{/Symbol-Oblique l}{/Times-Italic t}} , Reference", \
  ""              u 1:5 every 5::4 w p ls 5 t "{/Symbol-Oblique b m}@^{ex}_{{/Symbol-Oblique l}{/Times-Italic t}} , {/Symbol D} = {/Times-Italic h B}", \
  "../../data/hs/Pmuhsvs12.dat" u 1:4 w l ls 10 t "{/Symbol-Oblique b m}^{ex}, VS12", \
  -1 notitle

unset multiplot
unset output
set terminal pop
reset
