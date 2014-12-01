#define ZCOM_PICK
#define ZCOM_LJ
#define ZCOM_LOG
#define ZCOM_ARGOPT
#include "zcom.h"



int d = 3;
int n = 108;
real tp = 10;
real rho = (real) 0.7;
real amp = (real) 0.3;
int dolj = 1;
double nequil = 100000;
double nsteps = 1000000;
//int nstrdf = 1000;
double nstsave = 1e7;
double uref, Pref, Fref, muref;
int verbose = 0;

//char *fnrdf = "rdf1.dat";

double dx = 0.01;
char fnpmf[80] = "pmf.dat";



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
  argopt_add(ao, "--nstsave", "%lf", &nstsave, "number of steps to save data");
  //argopt_add(ao, "-G", "%b", &gaussf, "do the Gaussian fluid");
  //argopt_add(ao, "--invexp", "%d", &invexp, "exponent e of the r^{-e} fluid");
  //argopt_add(ao, "--lj", "%b", &dolj, "do the Lennard-Jones fluid");
  argopt_add(ao, "--dx", "%lf", &dx, "delta x");
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



static real lj_widom(lj_t *lj, real beta)
{
  real du, bu;

  du = lj_duinsert(lj, NULL);
  bu = beta * du;
  return (bu > 700) ? 0 : exp(-bu);
}



/* randomly displace particle i with random amplitude */
INLINE int lj_randmv3dx(lj_t *lj, real *xi, real amp)
{
  int i, d;

  /* skip particles 1 and 2 */
  i = (int)(rnd0() * (lj->n - 2)) + 2;
  amp /= lj->l;
  rv3_copy(xi, lj->x + i*3);
  for (d = 0; d < 3; d++) /* displacement */
    xi[d] += (real)(amp * (2.*rnd0() - 1.));
  return i;
}



/* Metropolis moves */
INLINE int lj_metrolj3dx(lj_t *lj, real amp, real bet)
{
  int i;
  real xi[3], du = 0.f, dvir = 0.f;

  i = lj_randmv3dx(lj, xi, amp);
  du = lj_depotlj3d(lj, i, xi, &dvir);
  if (metroacc1(du, bet)) {
    lj_commitlj3d(lj, i, xi, du, dvir);
    return 1;
  }
  return 0;
}



/* compute energy data for a 3D Lennard-Jones pair */
INLINE int lj_pairlj3dx(real *xi, real *xj, real *dx,
    real l, real rc2, real *dr2, real *u, real *vir)
{
  real invr2, invr6;
  *dr2 = lj_pbcdist2_3d(dx, xi, xj, l);
  if (*dr2 < rc2) {
    invr2 = 1.0f / *dr2;
    invr6 = invr2 * invr2 * invr2;
    *vir = invr6 * (48.f * invr6 - 24.f); /* f.r */
    *u  = 4.f * invr6 * (invr6 - 1.f);
    return 1;
  } else return 0;
}



/* compute the excess mean force between 0 and 1 */
INLINE real getrf(lj_t *lj)
{
  int j, n = lj->n;
  real dr2, u, vir, dr01, dr01sqr, rf;
  real *x0 = lj->x, *x1 = lj->x + 3;
  rv3_t dx, dx01;

  dr01sqr = lj_pbcdist2_3d(dx01, x0, x1, lj->l);
  dr01 = (real) sqrt(dr01sqr);
  for ( j = 2; j < n; j++ ) {
    lj_pairlj3dx(x0, lj->x + j*3, dx, lj->l, lj->rc2, &dr2, &u, &vir);
    rf -= vir * rv3_dot(dx01, dx) / dr2 / dr01;
    lj_pairlj3dx(x1, lj->x + j*3, dx, lj->l, lj->rc2, &dr2, &u, &vir);
    rf += vir * rv3_dot(dx01, dx) / dr2 / dr01;
  }
  return rf / 2;
}



/* 3D compute force and virial, return energy */
INLINE real lj_energylj3dx(lj_t *lj, rv3_t *x, real *virial, real *ep0, real *eps)
{
  real dx[3], dr2, dr6, ep, vir, l = lj->l, rc2 = lj->rc2;
  int i, j, prcnt = 0, n = lj->n;

  if (virial) *virial = 0.f;
  /* skip the pair (0, 1) */
  for (ep = vir = 0, i = 0; i < n - 1; i++) {
    for (j = (i == 0) ? 2 : i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 > rc2) continue;
      dr2 = 1.f / dr2;
      dr6 = dr2 * dr2 * dr2;
      vir += dr6 * (48.f * dr6 - 24.f); /* f.r */
      ep += 4 * dr6 * (dr6 - 1);
      prcnt++;
    }
  }
  if (ep0) *ep0 = ep;
  if (eps) *eps = ep - prcnt * lj->epot_shift; /* shifted energy */
  if (virial) *virial = vir;
  return ep + lj->epot_tail; /* unshifted energy */
}


/* return the energy change from displacing x[i] to xi */
INLINE real lj_depotlj3dx(lj_t *lj, int i, real *xi, real *vir)
{
  int j, n = lj->n;
  real l = lj->l, rc2 = lj->rc2, u = 0.f, du = 0.f, dvir = 0.f;
  rv3_t *x = (rv3_t *) lj->x;

  *vir = 0.0f;
  for (j = 2; j < n; j++) { /* pair */
    if (j == i) continue;
    if (lj_pairlj3d(x[i], x[j], l, rc2, &du, &dvir)) {
      u -= du;
      *vir -= dvir;
    }
    if (lj_pairlj3d(xi, x[j], l, rc2, &du, &dvir)) {
      u += du;
      *vir += dvir;
    }
  }
  return u;
}



typedef struct {
  int n;
  double dx, xmax, lnf, t;
  double *sc;
  double *smf;
  double *pmf;
  double *lnz;
  double *hist;
} rpmf_t;



__inline static rpmf_t *rpmf_open(real xmax, real dx)
{
  rpmf_t *p;
  int i;

  xnew(p, 1);
  p->n = (int) (xmax / dx);
  p->t = 0;
  p->dx = dx;
  p->xmax = p->dx * p->n;
  p->lnf = 0.1;
  xnew(p->sc, p->n);
  xnew(p->smf, p->n);
  xnew(p->pmf, p->n + 1);
  xnew(p->lnz, p->n);
  xnew(p->hist, p->n);
  for ( i = 0; i < p->n; i++ ) {
    p->sc[i] = p->smf[i] = p->pmf[i] = 0;
    p->lnz[i] = p->hist[i] = 0;
  }
  p->pmf[p->n] = 0;
  return p;
}



__inline static int rpmf_add(rpmf_t *p, double r, double f)
{
  int i = (int) ( r / p->dx );

  if ( i < 0 || i >= p->n ) return -1;
  //printf("i %d/%d\n", i, p->n);
  p->sc[i] += 1;
  p->smf[i] += f;
  p->lnz[i] += p->lnf;
  p->hist[i] += 1;
  p->t += 1;
  return 0;
}



__inline static int rpmf_save(rpmf_t *p, const char *fn)
{
  FILE *fp;
  int i;
  real mf;

  p->pmf[p->n] = 0;
  for ( i = p->n - 1; i >= 0; i-- ) {
    mf = p->sc[i] > 0 ? p->smf[i] / p->sc[i] : 0;
    p->pmf[i] = p->pmf[i+1] + mf * p->dx;
  }

  xfopen(fp, fn, "w", return 0);
  fprintf(fp, "# %d %g %d %d %g %g %g\n", p->n, p->dx, d, n, tp, rho, p->lnf);
  for ( i = 0; i < p->n; i++ ) {
    mf = p->sc[i] > 0 ? p->smf[i] / p->sc[i] : 0;
    fprintf(fp, "%g %g %g %g %g %g\n", (i + .5) * p->dx,
        (p->pmf[i] + p->pmf[i+1])/2, mf, p->sc[i], /* 4 items */
        p->lnz[i], p->hist[i]);
  }
  fclose(fp);

  return 0;
}



__inline static double rpmf_getlnz(rpmf_t *p, double r)
{
  int i = (int)(r/p->dx);
  if ( i <= 0 ) return p->lnz[i];
  if ( i >= p->n - 1 ) return p->lnz[p->n - 1];
  return p->lnz[i];
}



__inline static double rpmf_getdlnz(rpmf_t *p, double r1, double r2)
{
  double v1 = rpmf_getlnz(p, r1);
  double v2 = rpmf_getlnz(p, r2);
  return v1 - v2;
}



__inline static int rpmf_wlupdate(rpmf_t *p)
{
  double hmin = 1e20, hmax = 0, flatness;
  int i, reduce = 0;

  for ( i = 0; i < p->n; i++ )
    p->lnz[i] -= p->lnz[p->n - 1];

  if ( p->lnf <= 0 ) return 0;

  for ( i = 0; i < p->n; i++ ) {
    if (p->hist[i] > hmax) hmax = p->hist[i];
    else if (p->hist[i] < hmin) hmin = p->hist[i];
  }
  flatness = (hmax - hmin) / (hmax + hmin);

  if ( p->lnf > 1e-4 ) {
    /* use Wang-Landau for a sufficiently large lnf */
    if ( flatness < 0.2 ) {
      for ( i = 0; i < p->n; i++ )
        p->hist[i] = 0;
      //fprintf(stderr, "t %g, change lnf from %g to %g\n",
      //    p->t, p->lnf, p->lnf*.5);
      p->lnf *= 0.5;
      reduce = 1;
    }
  } else {
    p->lnf = 0;
    printf("switched off updating, p->t %g\n", p->t);
    //p->lnf = p->n / p->t;
  }
  return reduce;
}



__inline static void rpmf_close(rpmf_t *p)
{
  free(p->sc);
  free(p->smf);
  free(p->pmf);
  free(p->lnz);
  free(p->hist);
  free(p);
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

  lj = lj_open(n, d, rho, 1e8);
  lj->dof = n * d;
  x0 = lj->x;
  x1 = lj->x + 3;
  //ljrdf = ljrdf_open(lj, 0.01, 0);

  rpmf = rpmf_open(lj->l/2 - dx, dx);
  sprintf(fnpmf, "pmfT%grho%gn%d.dat", tp, rho, n);

  printf("rho %g, T %g, n %d, l/2 %g, u %g, P %g (bP %g), f %g, mu %g (bmu %g)\n",
      rho, tp, n, lj->l/2, uref, Pref, Pref/tp, Fref, muref, muref/tp);

  lj->epot = lj_energylj3dx(lj, (rv3_t *) lj->x, &lj->vir, &lj->epot0, &lj->epots);

  for ( t = 1; t <= nequil + nsteps; t += 1 ) {
    /* move a particle that is not special */
    acc += lj_metrolj3dx(lj, amp, 1/tp);

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
      rf = getrf(lj);
      rpmf_add(rpmf, dr01, rf);
      del = amp * (2*rnd0() - 1);
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



