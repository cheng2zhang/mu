Hard-sphere
=============



Pmuhsvs12.dat
--------------

Exact pressure/chemical potential from the 12-term virial series: 
Replacing D3P.dat



crtrD3M8192ms.dat
-----------------

Correlation functions from Mayer sampling.
Up to order n = 3 to 8.
The format is
```
r   c(r)  t(r)  n-2   B(r)  w(r)
```

This file can be read by brseries.h.



Results from integral equations
-------------------------------

### Compressibility and virial routes

murhoscan.c --> muhsXXXcv.dat



### Chemical-potential routes

muxiscan.py --> muhsXXXxif.dat, muhsXXXxir.dat, muhsXXXxit.dat

