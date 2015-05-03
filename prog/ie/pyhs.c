#include <stdio.h>
#include "pyhs.h"



int main(void)
{
  xdouble rhodel = 0.1, rhomax = 1.0;
  xdouble rho;
  xdouble bmuc, bmuv, bmux, bPc, bPv, bPx;

  for ( rho = rhodel; rho < rhomax + 1e-7; rho += rhodel ) {
    bPc = hs3d_getbPc(rho);
    bPv = hs3d_getbPv(rho);
    bPx = hs3d_getbPx(rho);
    bmuc = hs3d_getbmuc(rho);
    bmuv = hs3d_getbmuv(rho);
    bmux = hs3d_getbmux(rho);
    printf("%g %g %g %g %g %g %g\n", (double) rho,
        (double) bPc, (double) bPv, (double) bPx,
        (double) bmuc, (double) bmuv, (double) bmux);
  }
  return 0;
}
