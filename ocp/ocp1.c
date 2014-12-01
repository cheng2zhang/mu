#include <stdio.h>
#include <ctype.h>
#include <math.h>



#include "xdouble.h"

#ifdef NOFFTW
#define XDOUBLE xdouble
#include "fft.h"
typedef void *FFTWPFX(plan);
#else
#include <fftw3.h>
#endif



xdouble beta = 1.0;
int numpt = 8192;
xdouble rmax = 32;
xdouble rho = 0.3;
xdouble a = 1.0;
xdouble damp = 1;
xdouble tol = 1e-7;
int itmax = 100;



#ifndef xnew
#define xnew(x, n) { \
  if ((x = calloc((size_t)(n), sizeof(*(x)))) == NULL) { \
    fprintf(stderr, "no memory for %s x %d\n", #x, (int) (n)); \
    exit(1); } }
#endif



/* compute
 *    out(k) = 2*fac/k Int {from 0 to infinity} in(r) r sin(k r) dr */
static void sphr(int npt, xdouble *in, xdouble *out, xdouble fac,
    FFTWPFX(plan) p, xdouble *arr, xdouble *ri, xdouble *ki)
{
  int i;

  for ( i = 0; i < npt; i++ ) /* form in(x) * x */
    arr[i] = in[i] * ri[i];
#ifdef NOFFTW
  sint11(arr, npt);
#else
  FFTWPFX(execute)(p);
#endif
  for ( i = 0; i < npt; i++ ) /* form out(k) / k */
    out[i] = arr[i] * fac / ki[i];
}



/* solve the integral equation */
static void iter(int npt, xdouble rho, xdouble *ri, xdouble *ki,
    xdouble *dcr, xdouble *dtr, xdouble *dck, xdouble *dtk,
    xdouble *bphi, xdouble *t0r, xdouble *t0k,
    xdouble facr2k, xdouble fack2r,
    FFTWPFX(plan) plan, xdouble *arr, int itmax)
{
  int i, it;
  xdouble x, err, errmax, yr, ck;

  for ( it = 0; it < itmax; it++ ) {
    sphr(npt, dcr, dck, facr2k, plan, arr, ri, ki); /* dc(r) --> dc(k) */
    for ( i = 0; i < npt; i++ ) {
      ck = dck[i] - t0k[i];
      dtk[i] = rho * ck * ck / (1 - rho * ck) - t0k[i];
    }
    sphr(npt, dtk, dtr, fack2r, plan, arr, ki, ri); /* dt(k) --> dt(r) */
    for ( errmax = 0, i = 0; i < npt; i++ ) {
      x = EXP(-bphi[i] + t0r[i] + dtr[i]) - (1 + dtr[i]);
      if ((err = FABS(dcr[i] - x)) > errmax) errmax = err;
      dcr[i] += damp * (x - dcr[i]);
    }
    if ( errmax < tol ) break;
  }
  //printf("iter %d errmax %g\n", it, (double) errmax);
}



static int integ(int npt, xdouble rmax, xdouble rho)
{
  xdouble dr, dk, facr2k, fack2r, surfr, surfk;
  xdouble *bphi, *cr, *tr, *ck, *tk, *c0r, *t0r, *c0k, *t0k;
  xdouble *arr, *ri, *ki, *ri2, *ki2;
  int i;
  FFTWPFX(plan) plan = NULL;
  FILE *fp;

  xnew(arr, npt);
  xnew(ri, npt);
  xnew(ki, npt);
  xnew(ri2, npt);
  xnew(ki2, npt);
  plan = FFTWPFX(plan_r2r_1d)(npt, arr, arr, FFTW_RODFT11, FFTW_ESTIMATE);

  dr = rmax / npt;
  dk = PI / (dr * npt);

  facr2k = PI*2 * dr;
  fack2r = pow_si(PI*2, -2) * dk;
  for ( i = 0; i < npt; i++ ) {
    ri[i] = dr * (i * 2 + 1) / 2;
    ki[i] = dk * (i * 2 + 1) / 2;
  }

  surfr = PI*4;
  surfk = surfr * pow_si(PI*2, -3);
  for ( i = 0; i < npt; i++ ) {
    ri2[i] = surfr * ri[i] * ri[i] * dr;
    ki2[i] = surfk * ki[i] * ki[i] * dk;
  }

  xnew(bphi, npt);
  xnew(cr, npt);
  xnew(tr, npt);
  xnew(ck, npt);
  xnew(tk, npt);
  xnew(t0r, npt);
  xnew(t0k, npt);

  for ( i = 0; i < npt; i++ ) {
    xdouble x;
    bphi[i] = beta / ri[i];
    t0r[i] = bphi[i] * ERF(ri[i]/SQRT(2)/a);
  }
  sphr(npt, t0r, t0k, facr2k, plan, arr, ri, ki); /* t0(r) --> t0(k) */

  /* initialize c(r) for iteration */
  for ( i = 0; i < npt; i++ )
    cr[i] = -bphi[i] + t0r[i];

  iter(npt, rho, ri, ki, cr, tr, ck, tk, bphi, t0r, t0k,
      facr2k, fack2r, plan, arr, itmax);

  free(bphi);
  free(cr);
  free(tr);
  free(ck);
  free(tk);
  free(t0r);
  free(t0k);

  free(arr);
  free(ri);
  free(ki);
  free(ri2);

  return 0;
}



int main(void)
{
  integ(numpt, rmax, rho);
#ifndef NOFFTW
  FFTWPFX(cleanup)();
#endif
  return 0;
}

