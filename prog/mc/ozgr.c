/* Computing c(r), t(r) from g(r) computed from the OZ relation
 * adapted from ievir.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ZCOM_PICK
#define ZCOM_LJ
#define ZCOM_ARGOPT
#include "zcom.h"
#include "fftx.h"



int dim = D;
xdouble T = 2;
xdouble beta = .5f;
xdouble rho = (xdouble) 0.7;
double rmax = 20.48;
xdouble Rmax = 0;
xdouble sdr = 0.1;
int numpt = 8192;
int ffttype = 1;
int verbose = 0;
char *fncrtr = "crtr.dat";
char *fngr = "rdf.dat";
char *fnpmf = "pmf.dat";

int smoothpot = 0; /* smooth potential */
int gaussf = 0; /* Gaussian model */
int invexp = 0; /* inverse potential */
int dolj = 1; /* Lennard-Jones potential by default */
char systitle[32];




static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);

  ao->desc = "computing the virial coefficients from the PY/HNC closure for hard-sphere fluids";
  argopt_add(ao, "-D", "%d", &dim, "dimension integer");
  argopt_add(ao, "-T", "%" XDBLSCNF "f", &T, "temperature");
  argopt_add(ao, "-r", "%lf", &rmax, "rmax (flexible)");
  argopt_add(ao, "-R", "%" XDBLSCNF "f", &Rmax, "rmax (exact)");
  argopt_add(ao, "--sdr", "%" XDBLSCNF "f", &sdr, "region for scaling g(r)");
  argopt_add(ao, "-M", "%d", &numpt, "number of points along r");
  argopt_add(ao, "-t", "%d", &ffttype, "FFT type, 0: integral grid points, 1: half-integer grid points");
  argopt_add(ao, "--gr", NULL, &fngr, "input file of the RDF g(r)");
  argopt_add(ao, "--pmf", NULL, &fnpmf, "input file of the excess p.m.f. w(r)");
  argopt_add(ao, "--crtr", NULL, &fncrtr, "file name of c(r) and t(r)");
#ifdef DHT
  argopt_add(ao, "--disk", "%d", &dhtdisk, "use disk for discrete Hankel transform (DHT)");
  argopt_add(ao, "--tmpdir", "%s", &slowdht_tmpdir, "directory for temporary files");
  argopt_add(ao, "--dhtblock", "%u", &slowdht_block, "block size for DHT input/output");
  argopt_add(ao, "--dhtquiet", "%b", &slowdht_quiet, "suppress DHT output");
#endif
  argopt_add(ao, "-G", "%b", &gaussf, "Gaussian model instead of hard spheres");
  argopt_add(ao, "-I", "%d", &invexp, "exponent of the inverse potential r^(-n)");
  argopt_add(ao, "-v", "%b", &verbose, "be verbose");
  argopt_addhelp(ao, "--help");
  argopt_parse(ao, argc, argv);

  if ( dim < 1 ) argopt_help(ao);
  if ( dim % 2 == 0 ) {
#ifndef DHT
    fprintf(stderr, "cannot do even dimensions %d, define DHT\n", dim);
    exit(1);
#endif
    if ( !argopt_isset(ao, numpt) ) /* adjust the default number of points */
      numpt = 1024;
  }

  /* models */
  if ( gaussf || invexp > 0 ) smoothpot = 1;

  { /* write the name of the system */
    char syst[16] = "";
    if ( gaussf ) strcpy(syst, "GF");
    else if ( invexp ) sprintf(syst, "INV%d", invexp);
    sprintf(systitle, "%s%s", (dim % 2 ? "" : "h"), syst);
  }

  printf("D %d, rmax %f, Rmax %f, npt %d, %s\n",
      dim, (double) rmax, (double) Rmax, numpt, systitle);

  if ( verbose ) argopt_dump(ao);
  argopt_close(ao);
}



#include "loadgr.h"



static int intgeq(int npt, xdouble rmax, xdouble Rmax, int ffttype)
{
  xdouble *bphi, *bphi1, *fr, *rdfr = NULL;
  xdouble *cr, *tr, *hr, *Br, *wr, *ck, *tk, *hk, x, r;
  xdouble bmu0, bmu1, bmu2, sc, sth;
  double Pref, Fref, muref;
  int i;
  sphr_t *sphr;
  FILE *fp;

  (void) Rmax;
  sphr = sphr_open(dim, npt, rmax, Rmax, ffttype);
  printf("D %d, dr %f, dm %d, rmax %f, ffttype %d\n",
      dim, (double) sphr->rmax/npt, sphr->dm, (double) sphr->rmax,
      ffttype);

  MAKE1DARR(bphi, npt);
  MAKE1DARR(bphi1, npt);
  MAKE1DARR(fr, npt);
  MAKE1DARR(rdfr, npt);
  MAKE1DARR(cr, npt);
  MAKE1DARR(hr, npt);
  MAKE1DARR(tr, npt);
  MAKE1DARR(Br, npt);
  MAKE1DARR(wr, npt);
  MAKE1DARR(hk, npt);
  MAKE1DARR(ck, npt);
  MAKE1DARR(tk, npt);

  /* this function, if successful, updates rho and T */
  loadwr(fnpmf, npt, wr, sphr->ri);

  /* compute f(r) */
  x = POW(2, 1./6);
  mkfr(npt, beta, bphi, fr, rdfr, sphr->ri, sphr->dm, gaussf, invexp, dolj);
  for ( i = 0; i < npt; i++ ) {
    bphi1[i] = ( sphr->ri[i] < x ) ? -beta : bphi[i];
  }

  loadgr(fngr, npt, hr, sphr->ri, sdr);
  for ( i = 0; i < npt; i++ )
    hr[i] -= 1;
  sphr_r2k(sphr, hr, hk);

  ///* remove high frequency modes */
  //kcutoff = 2*PI/0.01;
  //for ( i = 0; i < npt; i++ )
  //  if (sphr->ki[i] > kcutoff)
  //    hk[i] = 0;
  //sphr_k2r(sphr, hk, hr);

  /* apply the OZ relation */
  for ( i = 0; i < npt; i++ )
    ck[i] = hk[i]/(1 + rho * hk[i]);
  sphr_k2r(sphr, ck, cr);
  for ( i = 0; i < npt; i++ ) {
    tr[i] = hr[i] - cr[i];
    tk[i] = hk[i] - ck[i];
  }

  /* estimate B(r) */
  for ( i = 0; i < npt; i++ ) {
    x = 1 + hr[i];
    if ( FABS(x) > 0.3 ) {
      Br[i] = LOG(x) + bphi[i] - tr[i];
    } else {
      Br[i] = 0;
    }
  }

  /* compute the reference value */
  lj_eos3d(rho, T, &Pref, &Fref, &muref);

  /* evaluate the chemical potential */
  bmu0 = bmu1 = bmu2 = 0;
  sc = sth = 0;
  for ( i = 0; i < npt; i++ ) {
    xdouble Bri = wr[i] - tr[i], hri = cr[i] + tr[i];
    r = sphr->ri[i];
    xdouble rDm1 = 4 * PI * r * r * sphr->dr;
    //if (r > 1.7) Bri = 0;
    sc += cr[i] * rDm1;
    sth += tr[i] * hri * rDm1;
    bmu0 += rDm1 * rho * (-cr[i] + 0.5 * hri * tr[i]);
    bmu1 += rDm1 * rho * Bri;
    bmu2 += rDm1 * rho * 2./3 * Bri * hri;
  }
  printf("mu0 %g, %g, %g, muref %g\n",
      (double) bmu0, (double) (bmu0 + bmu1), (double) (bmu0 + bmu1 + bmu2),
      (double) (muref/T));
  printf("-rho c %g, rho (th/2 - c) %g\n",
      (double) (-rho*sc), (double) (rho*(sth/2 - sc)));

  xfopen(fp, fncrtr, "w", return -1);
  for ( i = 0; i < npt; i++ ) {
    fprintf(fp, "%g %g %g %g %g %g %g %g %g\n",
        sphr->ri[i], cr[i], tr[i], wr[i], Br[i], bphi[i], bphi1[i], /* 7 items */
        ck[i], tk[i]);
  }
  fclose(fp);

  sphr_close(sphr);
  FREE1DARR(bphi, npt);
  FREE1DARR(bphi1,npt);
  FREE1DARR(fr,   npt);
  FREE1DARR(rdfr, npt);
  FREE1DARR(cr,   npt);
  FREE1DARR(tr,   npt);
  FREE1DARR(hr,   npt);
  FREE1DARR(Br,   npt);
  FREE1DARR(wr,   npt);
  FREE1DARR(ck,   npt);
  FREE1DARR(tk,   npt);
  FREE1DARR(hk,   npt);
  return 0;
}



int main(int argc, char **argv)
{
  doargs(argc, argv);
  intgeq(numpt, rmax, Rmax, ffttype);
  return 0;
}
