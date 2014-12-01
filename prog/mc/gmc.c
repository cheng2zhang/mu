#define ZCOM_PICK
#define ZCOM_LJ
#define ZCOM_LOG
#define ZCOM_ARGOPT
#include "zcom.h"



int d = 3;
int n = 108;
real tp = 1;
real rho = (real) 0.7;
real amp = (real) 0.3;
int dolj = 1;
double nequil = 1000000;
double nsteps = 1000000;
int nstrdf = 1000;
double nstsave = 1e7;
double uref = 0, Pref = 0, Fref = 0, muref = 0, mu0ref = 0;
int eostype = 0;
int verbose = 0;

char fnrdf[80];



/* solve the rho that correspond to mu */
static real solverho(double tp, double muexref, double rho0)
{
  double rho1, rho2, mu0, mu1, mu2, fac = 0.9;

  /* get the initial bracket */
  for ( rho1 = rho0; ; rho1 *= fac ) {
    lj_eos3dx(rho1, tp, NULL, NULL, &mu1, eostype);
    if ( mu1 < muexref ) break;
  }
  for ( rho2 = rho0; ; rho2 /= fac ) {
    lj_eos3dx(rho2, tp, NULL, NULL, &mu2, eostype);
    if ( mu2 > muexref ) break;
  }
  for ( ; fabs(rho1 - rho2) > 1e-14; ) {
    rho0 = (rho1 + rho2) / 2;
    lj_eos3dx(rho0, tp, NULL, NULL, &mu0, eostype);
    if ( mu0 > muexref ) {
      rho2 = rho0;
      mu2 = mu0;
    } else {
      rho1 = rho0;
      mu1 = mu0;
    }
    //printf("rho1 %g (%g) rho2 %g (%g)\n", rho1, mu1, rho2, mu2);
  }
  fprintf(stderr, "adjust rho %g for muex %g\n", rho1, muexref);
  //getchar();
  return (real) rho1;
}



static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);
  ao->desc = "Monte Carlo";
  argopt_add(ao, "--rho", "%r", &rho, "maximal density rho (estimated or target value)");
  argopt_add(ao, "-T", "%r", &tp, "temperature");
  argopt_add(ao, "-n", "%d", &n, "number of particles");
  argopt_add(ao, "-A", "%r", &amp, "amplitude of Monte Carlo moves");
  argopt_add(ao, "-0", "%lf", &nequil, "number of steps for equilibration");
  argopt_add(ao, "-1", "%lf", &nsteps, "number of steps for actual runs");
  argopt_add(ao, "--mu", "%lf", &muref, "specify the reference excess mu value");
  argopt_add(ao, "--mu0", "%lf", &mu0ref, "specify the reference excess mu value");
  argopt_add(ao, "--nstrdf", "%d", &nstrdf, "number of steps of doing RDF");
  argopt_add(ao, "--nstsave", "%lf", &nstsave, "number of steps to save data");
  //argopt_add(ao, "-G", "%b", &gaussf, "do the Gaussian fluid");
  //argopt_add(ao, "--invexp", "%d", &invexp, "exponent e of the r^{-e} fluid");
  //argopt_add(ao, "--lj", "%b", &dolj, "do the Lennard-Jones fluid");
  argopt_add(ao, "--eos", "%d", &eostype, "standard equation of state, 0: JZG 1993, 1: KN 1994, MBWR, 2: KN 1994, PVE-hBH");
  argopt_add(ao, "-v", "%b", &verbose, "be verbose");
  argopt_addhelp(ao, "-h");
  argopt_addhelp(ao, "--help");
  argopt_parse(ao, argc, argv);

  if ( dolj ) {
    double muref1;
    uref = lj_eos3dx(rho, tp, &Pref, &Fref, &muref1, eostype);
    if ( argopt_isset(ao, muref) ) { /* modify mu */
      if ( argopt_isset(ao, rho) ) {
        fprintf(stderr, "target rho %g, eos mu %g, parameter mu %g\n",
            rho, muref1, muref);
      } else { /* adjust rho such that muref1 == muref */
        rho = solverho(tp, muref, rho);
        mu0ref = muref/tp + log(rho);
      }
    } else if ( !argopt_isset(ao, mu0ref) ) { /* use the mu from the equation of state */
      muref = muref1;
      mu0ref = muref/tp + log(rho);
    }
  }

  printf("T %g, rho %g, mu0ref %g, nsteps %g\n", (double) tp, (double) rho, mu0ref, nsteps);
  if ( verbose ) argopt_dump(ao);
  argopt_close(ao);
}



static real lj_widom(lj_t *lj, real beta)
{
  real du, bu;

  du = lj_duinsert(lj, NULL);
  bu = beta * du;
  return (bu > 700) ? 0 : exp(-bu);
}



static int lj_insert(lj_t *lj, real beta, real bmu0, int nmax)
{
  int j, n = lj->n;
  real du = 0, dvir = 0, u, vir, fac, xi[3];

  if (lj->n >= nmax) return 0;

  for (j = 0; j < 3; j++) xi[j] = (real) rnd0();
  for (u = vir = 0, j = 0; j < n; j++) { /* pair energy */
    if (lj_pair(lj, xi, lj->x + 3*j, &du, &dvir)) {
      u += du;
      vir += dvir;
    }
  }
  du  = lj_gettail(lj, (n+1)/lj->vol, n+1, NULL);
  du -= lj_gettail(lj, n/lj->vol, n, NULL);

  /* we do not consider utail in the acceptance ratio */
  fac = lj->vol*exp(bmu0 - beta*(u+du))/(n+1);
  if ( fac > 1 || rnd0() < fac ) { /* accept */
    rv3_copy(lj->x + n*3, xi);
    lj->epot0 += u;
    lj->vir += vir;
    lj->n = n + 1;
    lj_setrho(lj, lj->n/lj->vol);
    lj->epot = lj->epot0 + lj->epot_tail;
    //real ep1, ep0, vir1;
    //ep1 = lj_energylj3d(lj, (rv3_t *) lj->x, &vir1, &ep0, NULL);
    //printf("insert: epot0 %g(%g), epot %g(%g), vir %g(%g)\n", lj->epot0, ep0, lj->epot, ep1, lj->vir, vir1); getchar();
    lj->dof = lj->n * lj->d;
    return 1;
  }
  return 0;
}



static int lj_delete(lj_t *lj, real beta, real bmu0)
{
  int i, j, n = lj->n;
  real du = 0, dvir = 0, u, vir, fac, *xi;

  if (n <= 0) return 0;

  i = (int) (rnd0() * n);
  xi = lj->x + 3*i;
  for (u = vir = 0, j = 0; j < n; j++) { /* pair energy */
    if ( j == i ) continue;
    if (lj_pair(lj, xi, lj->x + 3*j, &du, &dvir)) {
      u += du;
      vir += dvir;
    }
  }
  du  = lj_gettail(lj, n/lj->vol, n, NULL);
  du -= lj_gettail(lj, (n-1)/lj->vol, n-1, NULL);

  fac = n*exp(beta*(u+du) - bmu0)/lj->vol;
  if ( fac > 1 || rnd0() < fac ) { /* accept */
    rv3_copy(xi, lj->x + (n-1)*3);
    lj->epot0 -= u;
    lj->vir -= vir;
    lj->n = n - 1;
    lj_setrho(lj, lj->n/lj->vol);
    lj->epot = lj->epot0 + lj->epot_tail;
    lj->dof = lj->n * lj->d;
    //real ep1, ep0, vir1;
    //ep1 = lj_energylj3d(lj, (rv3_t *) lj->x, &vir1, &ep0, NULL);
    //printf("delete: epot0 %g(%g), epot %g(%g), vir %g(%g)\n", lj->epot0, ep0, lj->epot, ep1, lj->vir, vir1); getchar();
    return 1;
  }
  return 0;
}



av_t avU[1] = {0}, avp[1] = {0}, avxp[1] = {0}, avn[1]= {0};



static void save(logfile_t *logfile, ljrdf_t *ljrdf, double acc, double t)
{
  real u, p, xpnbu;
  double nav, nvar, mu0;

  nav = av_getave(avn);
  nvar = av_getvar(avn);
  u = av_getave(avU);
  p = av_getave(avp);
  xpnbu = log(av_getave(avxp));
  ljrdf_save(ljrdf, fnrdf, HIST_ADDAHALF | HIST_KEEPHIST | HIST_NOZEROES);
  mu0 = tp*(-xpnbu + log(rho));
  log_printf(logfile, "t %g: saved to %s, acc %g%%, "
      "mu %g (muex %g), bmu %g (bmuex %g), P %g, bP %g, u %g, N %g, var %g, rho %g, %d frames\n",
      t, fnrdf, 100.*acc/t,
      mu0, -tp*xpnbu, mu0/tp, -xpnbu, p, p/tp, u/nav,
      nav, nvar, nav/ljrdf->lj->vol, ljrdf->nfr);
}



static int domc(void)
{
  double t, acc = 0, isrun = 0;
  lj_t *lj;
  ljrdf_t *ljrdf;
  real xpnbu, bmu0;
  int nmax;
  logfile_t *logfile;
  char fnlog[80];

  bmu0 = mu0ref/tp;
  sprintf(fnlog, "ljgmcT%gmu%g.log", tp, mu0ref);
  logfile = log_open(fnlog);
  logfile->flags = LOG_WRITESCREEN | LOG_FLUSHAFTER | LOG_APPEND;

  nmax = (int) (n * 1.5 + 100);
  lj = lj_open(nmax, d, rho*nmax/n, 1e8);
  lj->n = n;
  lj_setrho(lj, lj->n/lj->vol);
  lj->dof = lj->n * d;
  lj_energy(lj);

  ljrdf = ljrdf_open(lj, 0.01, 0);
  sprintf(fnrdf, "grdfT%gmu%gn%d.dat", tp, mu0ref, n);
  ljrdf_load(ljrdf, fnrdf, HIST_VERBOSE);

  /* avoid tail correction for simplicity */
  lj->epot_tail = 0;
  lj->epot = lj->epot0;

  printf("rho %g, T %g, n %d, l/2 %g, u %g, P %g (bP %g), F %g, mu %g (bmuex %g, bmu0 %g)\n",
    rho, tp, n, lj->l/2, uref, Pref, Pref/tp, Fref, muref, muref/tp, bmu0);

  for ( t = 1; t <= nequil + nsteps; t += 1 ) {
    acc += lj_metro3d(lj, amp, 1/tp);

    if (fmod(t, 5) < .5) {
      /* try to add or remove a particle */
      if ( rnd0() < 0.5 ) {
        lj_insert(lj, 1/tp, bmu0, nmax);
      } else {
        lj_delete(lj, 1/tp, bmu0);
      }
    }

    if (t > nequil) {
      if ( !isrun ) {
        fprintf(stderr, "t %g, equilibrated, n %d, acc %g%%\n",
            t, lj->n, 100.*acc/t);
        isrun = 1;
      }
    }
    if ( !isrun ) continue;

    av_add(avU, lj->epot);
    av_add(avp, lj_calcp(lj, tp));
    av_add(avn, lj->n);
    if (fmod(t, 5) < .5) {
      xpnbu = lj_widom(lj, 1/tp);
      av_add(avxp, xpnbu);
    }
    if (fmod(t, nstrdf) < .5) {
      ljrdf_add(ljrdf, 0);
      if (fmod(t, nstsave) < 0.5)
        save(logfile, ljrdf, acc, t);
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



