/* biased Monte Carlo to compute the potential of mean force */
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
real mcamp = (real) 0.3;
int dolj = 1;
double nequil = 100000;
double nsteps = 1000000;
//int nstrdf = 1000;
double nstsave = 1e7;
double uref, Pref, Fref, muref;
int verbose = 0;

//char *fnrdf = "rdf1.dat";

double xdel = 0.01;
char fnpmf[80] = "pmf.dat";

#include "rpmf.h"



static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);

  ao->desc = "Monte Carlo to compute the potential of mean force";
  argopt_add(ao, "--rho", "%r", &rho, "maximal density rho");
  argopt_add(ao, "-T", "%r", &tp, "temperature");
  argopt_add(ao, "-n", "%d", &n, "number of particles");
  argopt_add(ao, "-A", "%r", &mcamp, "amplitude of Monte Carlo moves");
  argopt_add(ao, "-0", "%lf", &nequil, "number of steps for equilibration");
  argopt_add(ao, "-1", "%lf", &nsteps, "number of steps for actual runs");
  argopt_add(ao, "--mu", "%lf", &muref, "specify the reference mu value");
  argopt_add(ao, "--nstsave", "%lf", &nstsave, "number of steps to save data");
  //argopt_add(ao, "-G", "%b", &gaussf, "do the Gaussian fluid");
  //argopt_add(ao, "--invexp", "%d", &invexp, "exponent e of the r^{-e} fluid");
  //argopt_add(ao, "--lj", "%b", &dolj, "do the Lennard-Jones fluid");
  argopt_add(ao, "--dx", "%lf", &xdel, "delta x");
  argopt_add(ao, "-v", "%b", &verbose, "be verbose");
  argopt_addhelp(ao, "-h");
  argopt_addhelp(ao, "--help");
  argopt_parse(ao, argc, argv);
  if ( dolj ) {
    double muref1;
    uref = lj_eos3d(rho, tp, &Pref, &Fref, &muref1);
    if ( !argopt_isset(ao, muref) ) muref = muref1;
  }
  printf("T %g, rho %g, mu %g, nsteps %g\n", (double) tp, (double) rho, muref, nsteps);
  if ( verbose ) argopt_dump(ao);
  argopt_close(ao);
}



static int domc(void)
{
  double t, acc = 0, isrun = 0, rf;
  lj_t *lj;
  //ljrdf_t *ljrdf;
  av_t avU[1] = {0}, avp[1] = {0}, avxp[1] = {0};
  real u, p, xpnbu, dr01, dx01[3], del, nr;
  real *x0, *x1, xi[3];
  rpmf_t *rpmf;
  logfile_t *logfile;
  char fnlog[80];

  sprintf(fnlog, "ljmcT%grho%g.log", tp, rho);
  logfile = log_open(fnlog);
  logfile->flags = LOG_WRITESCREEN | LOG_FLUSHAFTER | LOG_APPEND;

  lj = lj_open(n, 3, rho, 1e8);
  lj->dof = n * 3;
  x0 = lj->x;
  x1 = lj->x + 3;
  //ljrdf = ljrdf_open(lj, 0.01, 0);

  rpmf = rpmf_open(lj->l/2 - xdel, xdel);
  sprintf(fnpmf, "pmfT%grho%gn%d.dat", tp, rho, n);

  printf("rho %g, T %g, n %d, l/2 %g, u %g, P %g (bP %g), f %g, mu %g (bmu %g)\n",
      rho, tp, n, lj->l/2, uref, Pref, Pref/tp, Fref, muref, muref/tp);

  lj->epot = lj_energylj3dx(lj, (rv3_t *) lj->x, &lj->vir, &lj->epot0, &lj->epots);

  for ( t = 1; t <= nequil + nsteps; t += 1 ) {
    /* move a particle that is not special */
    acc += lj_metrolj3dx(lj, mcamp, 1/tp);

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

      /* compute the mean force between 1 and 2 */
      dr01 = lj_pbcdist2_3d(dx01, x0, x1, lj->l);
      dr01 = (real) sqrt(dr01);
      rf = lj_getrf(lj);
      rpmf_add(rpmf, dr01, rf);
      del = mcamp * (2*rnd0() - 1);
      nr = dr01 + del;
      if (fabs(rf) > 1e5) {
        printf("t %g, dr %g, mf %g ndr %g, del %g xmax->%g\n", t, dr01, rf, nr, del, rpmf->xmax);
        exit(1);
      }
      if ( nr >= 0 && nr < rpmf->xmax ) {
        real du, du1, dvir;
        int i;

        i = ( rnd0() < 0.5 );
        if ( i ) {
          rv3_sadd(xi, x1, dx01, -del/lj->l/dr01);
        } else {
          rv3_sadd(xi, x0, dx01,  del/lj->l/dr01);
        }
        du = lj_depotlj3dx(lj, i, xi, &dvir);
        du1 = du + rpmf_getdlnz(rpmf, nr, dr01) * tp;
        if ( metroacc1(du1, 1/tp) ) {
          lj_commitlj3d(lj, i, xi, du, dvir);
          //printf("r %g --> %g, %g, du %g\n", dr01, nr, sqrt(lj_pbcdist2_3d(dx01, x0, x1, lj->l)), du);
        }
      }
      if (fmod(t, 100) < .5) {
        if ( rpmf_wlupdate(rpmf) || fmod(t, 1e8) < .5 ) {
          u = av_getave(avU)/lj->n;
          p = av_getave(avp);
          rpmf_save(rpmf, fnpmf);
          log_printf(logfile, "t %g, lnf %g saved to %s, acc %g%%, bmu %g, bP %g, u %g\n",
              t, rpmf->lnf, fnpmf, 100.*acc/t, -log(av_getave(avxp)), p/tp, u);
        }
      }
    }
    //if (fmod(t, nstrdf) < .5) ljrdf_add(ljrdf, 0);
  }
  rpmf_save(rpmf, fnpmf);
  rpmf_close(rpmf);
  u = av_getave(avU)/lj->n;
  p = av_getave(avp);
  xpnbu = log(av_getave(avxp));
  printf("T %g, rho %g, erg %g, p %g (bP %g), mu %g (bmu %g), acc %.2f%%\n",
      tp, rho, u, p, p/tp, -tp*xpnbu, -xpnbu, 100.*acc/nsteps);
  //ljrdf_save(ljrdf, fnrdf, HIST_ADDAHALF | HIST_KEEPHIST | HIST_NOZEROES);
  //ljrdf_close(ljrdf);
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



