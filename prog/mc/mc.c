#define ZCOM_PICK
#define ZCOM_LJ
#define ZCOM_LOG
#define ZCOM_ARGOPT
#include "zcom.h"
#include "ljx.h"



int dim = 3;
int n = 108;
real tp = 10;
real rho = (real) 0.7;
real amp = (real) 0.3;
int dolj = 1;
double nequil = 1000000;
double nsteps = 1000000;
int nstrdf = 1000;
double nstsave = 1e7;
double uref, Pref, Fref, muref;
int verbose = 0;

char fnrdf[80];



static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);
  ao->desc = "Monte Carlo";
  argopt_add(ao, "--rho", "%r", &rho, "maximal density rho");
  argopt_add(ao, "-T", "%r", &tp, "temperature");
  argopt_add(ao, "-n", "%d", &n, "number of particles");
  argopt_add(ao, "-A", "%r", &amp, "amplitude of Monte Carlo moves");
  argopt_add(ao, "-0", "%lf", &nequil, "number of steps for equilibration");
  argopt_add(ao, "-1", "%lf", &nsteps, "number of steps for actual runs");
  argopt_add(ao, "--mu", "%lf", &muref, "specify the reference mu value");
  argopt_add(ao, "--nstrdf", "%d", &nstrdf, "number of steps of doing RDF");
  argopt_add(ao, "--nstsave", "%lf", &nstsave, "number of steps to save data");
  //argopt_add(ao, "-G", "%b", &gaussf, "do the Gaussian fluid");
  //argopt_add(ao, "--invexp", "%d", &invexp, "exponent e of the r^{-e} fluid");
  //argopt_add(ao, "--lj", "%b", &dolj, "do the Lennard-Jones fluid");
  argopt_add(ao, "-v", "%b", &verbose, "be verbose");
  argopt_addhelp(ao, "-h");
  argopt_addhelp(ao, "--help");
  argopt_parse(ao, argc, argv);
  if ( dolj ) {
    double muref1;
    uref = lj_eos3d(rho, tp, &Pref, &Fref, &muref1);
    if ( !argopt_isset(ao, muref) ) muref = muref1;
  }
  printf("T %g, rho %g, muref %g, nsteps %g\n", (double) tp, (double) rho, muref, nsteps);
  if ( verbose ) argopt_dump(ao);
  argopt_close(ao);
}



av_t avU[1] = {0}, avp[1] = {0}, avxp[1] = {0}, avvir2[1] = {0};



/* compute Sum_{ij} < phi''(rij) rij^2 > / lj->n */
static double getvir2(ljrdf_t *ljrdf)
{
  double vir2 = 0, x, xav, npr, Gr, invr6;
  int i;
  lj_t *lj = ljrdf->lj;

  npr = lj->n * lj->n * .5;
  for ( i = 0; i < ljrdf->rdf->n; i++ ) {
    x = ljrdf->rdf->xmin + i * ljrdf->rdf->dx;
    xav = x + .5 * ljrdf->rdf->dx;
    Gr = ljrdf->rdf->arr[i] * lj->vol / (npr * ljrdf->nfr);
    invr6 = 1/(xav*xav*xav*xav*xav*xav);
    vir2 += 0.5 * rho * invr6 * (624 * invr6 - 168) * Gr;
  }
  return vir2;
}



static void save(logfile_t *logfile, ljrdf_t *ljrdf, double acc, double t)
{
  lj_t *lj = ljrdf->lj;
  real u, p, rho1, bpx, xpnbu, varbpx, invc, bvir2;

  u = av_getave(avU)/lj->n;
  p = av_getave(avp);
  rho1 = lj->n / lj->vol;
  bpx = p/tp - rho1;
  varbpx = av_getvar(avp)/(tp*tp);
  //real vir2a = av_getave(avvir2)/lj->n;
  bvir2 = (real) getvir2(ljrdf) / tp;
  /* d(beta * P) / d rho */
  invc = 1 - varbpx * lj->vol / rho1 + bpx/rho1 * (1 - 1./lj->d)
       + bvir2 / (lj->d*lj->d);
  xpnbu = log(av_getave(avxp));
  ljrdf->cfac = 1 + 1./invc/(lj->n - 1);
  ljrdf_save(ljrdf, fnrdf, HIST_ADDAHALF | HIST_KEEPHIST | HIST_NOZEROES);
  log_printf(logfile, "t %g: saved to %s, acc %g%%, "
      "mu %g, bmu %g, P %g, bP %g, u %g, invc %g, bvir2 %g, %d frames\n",
      t, fnrdf, 100.*acc/t, -tp*xpnbu, -xpnbu,
      p, p/tp, u, invc, bvir2, ljrdf->nfr);
}



static int domc(void)
{
  double t, acc = 0, isrun = 0;
  lj_t *lj;
  ljrdf_t *ljrdf;
  real xpnbu;
  logfile_t *logfile;
  char fnlog[80];

  sprintf(fnlog, "ljmcT%grho%g.log", tp, rho);
  logfile = log_open(fnlog);
  logfile->flags = LOG_WRITESCREEN | LOG_FLUSHAFTER | LOG_APPEND;

  lj = lj_open(n, dim, rho, 1e8);
  lj->dof = n * dim;

  ljrdf = ljrdf_open(lj, 0.01, 0);
  sprintf(fnrdf, "rdfT%grho%gn%d.dat", tp, rho, n);
  ljrdf_load(ljrdf, fnrdf, HIST_VERBOSE);

  printf("rho %g, T %g, n %d, l/2 %g, u %g, P %g (bP %g), f %g, mu %g (bmu %g)\n",
    rho, tp, n, lj->l/2, uref, Pref, Pref/tp, Fref, muref, muref/tp);

  for ( t = 1; t <= nequil + nsteps; t += 1 ) {
    acc += lj_metro3d(lj, amp, 1/tp);

    if (t > nequil) {
      if ( !isrun ) {
        fprintf(stderr, "t %g, equilibrated, acc %g%%\n",
            t, 100.*acc/t);
        isrun = 1;
      }
    }
    if ( !isrun ) continue;

    av_add(avU, lj->epot);
    av_add(avp, lj_calcp(lj, tp));
    if (fmod(t, 5) < .5) {
      xpnbu = lj_widom(lj, 1/tp);
      av_add(avxp, xpnbu);
    }
    if (fmod(t, nstrdf) < .5) {
      ljrdf_add(ljrdf, 0);
      if (fmod(t, nstsave) < 0.5) {
        save(logfile, ljrdf, acc, t);
      }
    }
  }
  save(logfile, ljrdf, acc, t);
  ljrdf_close(ljrdf);
  lj_close(lj);
  log_close(logfile);
  return 0;
}



int main(int argc, char **argv)
{
  doargs(argc, argv);
  domc();
  return 0;
}



