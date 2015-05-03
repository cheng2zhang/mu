#!/usr/bin/env gnuplot

set encoding cp1250 # make the minus sign longer
set terminal push
set terminal postscript eps enhanced size 5, 3.5 font "Times, 24"
set output "gamhs.eps"


rhomin = 0.01
rhomax = 1.0 + 1e-5
rhobsmax = 0.7

set xtics 0.2 font "Times,20" offset 0, 0.5
set mxtics 2
set ytics 0.2 font "Times,20" offset 0.5, 0
set mytics 2

#set lmargin 5.5
#set rmargin 1
#set tmargin 0.7
#set bmargin 2.3

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
set style line 2  lw 2.0 lt 2 lc rgb color2  pt 12  ps 2.5
set style line 3  lw 2.0 lt 1 lc rgb color3  pt 8   ps 2.0
set style line 4  lw 2.0 lt 2 lc rgb color4  pt 10  ps 2.0
set style line 5  lw 2.0 lt 1 lc rgb color5  pt 6   ps 2.0
set style line 6  lw 2.0 lt 2 lc rgb color6  pt 14  ps 2.0
set style line 7  lw 3.0 lt 4 lc rgb color7  pt 2   ps 2.0
set style line 8  lw 3.0 lt 2 lc rgb color8  pt 3   ps 2.0
set style line 9  lw 3.0 lt 5 lc rgb color9  pt 1   ps 2.0
set style line 10 lw 4.0 lt 1 lc rgb color10 pt 1   ps 2.0


set xlabel "Density, {/Symbol-Oblique r}" offset 0, 0.9
set ylabel "{/Symbol-Oblique g}^{id}" offset 2.0, 0
set key left bottom Left reverse spacing 1.5 font "Times, 24"

plot [0:rhomax][0:0.8] \
  "../../data/hs/muhspycv.dat" u 1:($1>rhomin ? $15 : 1/0) w l ls 1 t "PY, {/Symbol D} = {/Times-Italic h B}", \
  "../../data/hs/muhshccv.dat" u 1:($1>rhomin? $15 : 1/0) w l ls 3 t "HC, {/Symbol D} = {/Times-Italic h B}", \
  "../../data/hs/muhsbscv.dat" u 1:($1>rhomin && $1<rhobsmax? $15 : 1/0) w l ls 5 t "BS8, {/Symbol D} = {/Times-Italic h B}", \
  "../../data/hs/muhspycv.dat" u 1:($1>rhomin ? $16 : 1/0) w l ls 2 t "PY, {/Symbol D} = {/Times-Italic -B}", \
  "../../data/hs/muhshccv.dat" u 1:($1>rhomin ? $16 : 1/0) w l ls 4 t "HC, {/Symbol D} = {/Times-Italic -B}", \
  "../../data/hs/muhsbscv.dat" u 1:($1>rhomin && $1<rhobsmax ? $16 : 1/0) w l ls 6 t "BS8, {/Symbol D} = {/Times-Italic -B}", \
  -1 notitle



unset output
set terminal pop
reset
