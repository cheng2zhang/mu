#ifndef RPMF_H__
#define RPMF_H__



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
  fprintf(fp, "# %d %g %d %d %g %g %g\n", p->n, p->dx, dim, n, tp, rho, p->lnf);
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



#endif

