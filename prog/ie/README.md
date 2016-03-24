File description
================

File          | Description
--------------|--------------------------------------------
gr.c          | simple exercise of computing the radial distribution function, g(r)
murhoscan.c   | integrating over the density
muxiscan.c    | integrating over the charging parameter
muxiscan.py   | calls muxiscan.exe over a density range
mulamscan.c   | integrate over the global charging parameter
mulamscan.py  | calls mulamscan.exe over a density range
pyhs.c        | print the exact pressure and chemical of the hard-sphere fluid (driver)
--------------|--------------------------------------------
util.h        | utility functions
cfs.h         | correlation functions
model.h       | parameters and its IO
picard.h      | Picard solver
mdiis.h       | MDIIS solver
solver.h      | wrapper of picard.h and mdiis.h
ref.h         | reading and using reference values (Pmuhsvs12.dat)
brseries.h    | reading and using the exact bridge function components (crtrD3M8192ms.dat)
sc.h          | self-consistently determine the parameter in the integral equation
--------------|--------------------------------------------
pyhs.h        | exact presure and chemical potential of the hard-sphere fluid
ljeos.h       | Lennard-Jones equation of state
--------------|--------------------------------------------
xdouble.h     | define the `xdouble` type
ftx.h         | Fourier transform
fft.h         | fast Fourier transform, for odd dimensions
slowdht.h     | discrete Hankel transform, for even dimensions


Compilation
===========

Under Linux, all files can be compiled by simply enter
```
make
```


gr
==

To make it, type
```
make gr
```
This will produce `gr_fftw` for odd dimensions and `gr_gsl` for even dimensions.

The following example does a density scan from 1.4 to 1.6
for four dimensions.
```
./gr_gsl -v -D 4 --rhomin=1.4 --rhomax=1.6
```


murhoscan
==========

Compute the chemical potential by a scan over the density.

The executable is `murhoscan.exe`,
which can be obtained by
```
cl murhoscan.c
```

Example 1: PY
```
murhoscan -r 1.0 -O muhspycv.dat
```

Example 2: HNC
```
murhoscan -r 1.0 -O muhshnccv.dat -C HNC
```


muxiscan
========

Compute the chemical potential by a scan over the charging paramter.



### muxiscan.exe

The executable muxiscan.exe does only one density.
It can be compiled as
```
cl muxiscan.c
```

The charging parameter can f, r, or t,
as specified by the flag `-X f`, `-X r`, or `-X t`.

Note: the t-route is much faster than the rest,
because no integral equation is solved for xi != 1.



### muxiscan.py

To scan over a density range, use muxiscan.py.
Under windows, use it as `python muxiscan.py XXX`.
If run directly as `muxiscan.py XXX`,
the arguments `XXX` will not be passed to the script.

Note: muxiscan.exe must be created before using muxiscan.py.



Example 1: PY, f-route
```
python muxiscan.py --save=muhspyxif.dat
```

Example 2: HNC, r-route
```
python muxiscan.py -X r -C HNC --save=muhshncxir.dat
```

Example 3: PY, t-route
```
python muxiscan.py -X t -C PY --save=muhspyxit.dat
```



mulamscan
========

Compute the chemical potential by a scan over the global paramter.



### mulamscan.exe

The executable mulamscan.exe does only one density.
It can be compiled as
```
cl mulamscan.c
```

The charging parameter can f, r, c, h, or t
as specified by the flag `-L f`, `-L r`, `-L c`. `-L h`, or `-L t`.



### mulamscan.py

To scan over a density range, use mulamscan.py.
Under windows, use it as `python mulamscan.py XXX`.
If run directly as `mulamscan.py XXX`,
the arguments `XXX` will not be passed to the script.

Note: mulamscan.exe must be created before using mulamscan.py.




Example 1: PY, c-route
```
python muxiscan.py -X c -C PY --save=muhspylamc.dat
```
