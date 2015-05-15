#ifndef CFS_H__
#define CFS_H__



/* correlation functions */



#include "fftx.h"
#include "model.h"
#include "brseries.h"



typedef struct {
  int bm;
  sphr_t *sphr; /* handler for spherical Fourier transform */

  xdouble *bphi;
  xdouble *fr;
  xdouble *rdfr;
  xdouble *fk;

  xdouble *cr;
  xdouble *tr;
  xdouble *ck;
  xdouble *tk;
  xdouble *Br;

  /* derivatives w.r.t. rho */
  xdouble *dcr;
  xdouble *dtr;
  xdouble *dck;
  xdouble *dtk;
  xdouble *dBr;

  /* derivatives w.r.t. xi,
     the one-particle charging parameter  */
  xdouble *Dfr;
  xdouble *Dfk;
  xdouble *Dcr;
  xdouble *Dtr;
  xdouble *Dck;
  xdouble *Dtk;
  xdouble *DBr;

  /* derivative w.r.t. lam,
     the many-particle charging parameter */
  xdouble *Lfr;
  xdouble *Lfk;
  xdouble *Lcr;
  xdouble *Ltr;
  xdouble *Lck;
  xdouble *Ltk;
  xdouble *LBr;

  xdouble *ffr;

  xdouble *res; /* residue in the iteration */

  brseries_t *bs; /* series of bridge function components */
  int hasBr;
  int hasdBr;
} cfs_t;



__inline static cfs_t *cfs_open(sphr_t *sphr)
{
  cfs_t *c;
  int npt, i;

  xnew(c, 1);

  npt = sphr->npt;
  c->sphr = sphr;

  /* compute bm */
  for ( i = 0; i < npt; i++ ) {
    if ( sphr->ri[i] > 1 ) {
      c->bm = i;
      break;
    }
  }

  xnew(c->bphi,   npt);
  xnew(c->fr,     npt);
  xnew(c->rdfr,   npt);
  xnew(c->fk,     npt);

  xnew(c->cr,     npt);
  xnew(c->tr,     npt);
  xnew(c->ck,     npt);
  xnew(c->tk,     npt);
  xnew(c->Br,     npt);

  xnew(c->dcr,    npt);
  xnew(c->dtr,    npt);
  xnew(c->dck,    npt);
  xnew(c->dtk,    npt);
  xnew(c->dBr,    npt);

  xnew(c->Dfr,    npt);
  xnew(c->Dfk,    npt);
  xnew(c->Dcr,    npt);
  xnew(c->Dtr,    npt);
  xnew(c->Dck,    npt);
  xnew(c->Dtk,    npt);
  xnew(c->DBr,    npt);

  xnew(c->Lfr,    npt);
  xnew(c->Lfk,    npt);
  xnew(c->Lcr,    npt);
  xnew(c->Ltr,    npt);
  xnew(c->Lck,    npt);
  xnew(c->Ltk,    npt);
  xnew(c->LBr,    npt);

  xnew(c->ffr,    npt);

  xnew(c->res,    npt);

  c->bs = NULL;
  c->hasBr = 0;
  c->hasdBr = 0;
  return c;
}



__inline static void cfs_close(cfs_t *c)
{
  free(c->bphi);
  free(c->fr);
  free(c->rdfr);
  free(c->fk);

  free(c->cr);
  free(c->tr);
  free(c->ck);
  free(c->tk);
  free(c->Br);

  free(c->dcr);
  free(c->dtr);
  free(c->dck);
  free(c->dtk);
  free(c->dBr);

  free(c->Dfr);
  free(c->Dfk);
  free(c->Dcr);
  free(c->Dtr);
  free(c->Dck);
  free(c->Dtk);
  free(c->DBr);

  free(c->Lfr);
  free(c->Lfk);
  free(c->Lcr);
  free(c->Ltr);
  free(c->Lck);
  free(c->Ltk);
  free(c->LBr);

  free(c->ffr);

  free(c->res);

  if ( c->bs != NULL ) {
    brseries_close( c->bs );
  }

  free(c);
}



/* compute f(r)
 * f(r, xi, lam) = lam f(r/xi);
 * fills c->bphi, c->fr, and c->rdfr */
__inline static void cfs_mkfr(cfs_t *c,
    const model_t *m, xdouble xi, xdouble lam)
{
  sphr_t *sphr = c->sphr;
  int i, npt = m->npt;
  xdouble x, u, usr, rdu;
  xdouble dr = sphr->dr;

  /* set the hard-core boundary */
  c->bm = (int) (xi / dr + 0.5);

  /* compute f(r) */
  for ( i = 0; i < npt; i++ ) { /* compute f(r) = exp(-beta u(r)) - 1 */
    xdouble r = sphr->ri[i];

    if ( m->pottype == POTTYPE_GAUSS ) { /* f(r) = exp(-r^2) */
      xdouble r2, xp;

      r2 = pow_si(r, 2);
      xp = EXP(-r2);
      c->bphi[i] = -lam * LOG(1 - xp);
      c->fr[i] = POW(1 - xp, lam) - 1;
      c->rdfr[i] = lam * POW(1 - xp, lam - 1) * (2 * r2) * xp;

    } else if ( m->pottype == POTTYPE_WCA
             || m->pottype == POTTYPE_LJ ) {
      xdouble invr, invr2, invr6;

      r /= xi;
      invr = 1 / r;
      invr2 = invr * invr;
      invr6 = invr2 * invr2 * invr2;
      u = 4 * invr6 * (invr6 - 1);
      rdu = invr6 * (invr6 * 48 - 24);

      if ( invr6 * 2 > 1 ) {
        usr = u + 1;
      } else {
        usr = 0;
      }

      if ( m->pottype == POTTYPE_WCA ) {
        u = usr;
      }

      u *= m->beta;
      if ( u > m->crmax ) {
        u = m->crmax;
      } else if ( u < -m->crmax ) {
        u = -m->crmax;
      }

      c->bphi[i] = u;
      x = EXP( -c->bphi[i] * lam );
      c->fr[i] = x - 1;
      c->rdfr[i] = m->beta * lam * rdu * x;
    } else if ( m->pottype == POTTYPE_HS ) { /* hard-sphere */
      c->bphi[i] = 0;
      c->fr[i] = (i < c->bm) ? -1 : 0;
      /* for the hard-sphere fluid,
         r f'(r) is a delta function peaked at the contact radius.
         Thus, we average the values at the two consecutive
         grid points that bracket the contact radius */
      if ( i == c->bm || i == c->bm - 1 ) {
        c->rdfr[i] = xi / dr / 2;
      } else {
        c->rdfr[i] = 0;
      }
    } else {
      fprintf(stderr, "unknown potential type %d\n", m->pottype);
      exit(1);
    }

#ifdef RCUTOFF
    if ( r > RCUTOFF ) {
      c->fr[i] = 0;
      c->rdfr[i] = 0;
      c->bphi[i] = 0;
    }
#endif
  }
}



/* initialize the correlation functions */
__inline static void cfs_init(cfs_t *c, const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;

  /* initialize c->bphi, c->fr, c->rdfr, and c->bm */
  cfs_mkfr(c, m, 1, 1);

  for ( i = 0; i < npt; i++ ) {
    c->dcr[i] = c->cr[i] = c->fr[i];
    c->tr[i] = 0;
  }

  /* compute the convolution f * f */
  sphr_r2k(c->sphr, c->fr, c->fk); /* f(r) --> f(k) */

  for ( i = 0; i < npt; i++ ) {
    c->tk[i] = c->fk[i] * c->fk[i];
  }

  sphr_k2r(c->sphr, c->tk, c->ffr); /* t(k) --> ff(r) */
}



/* initialize the series for the bridge function */
__inline static int cfs_initbs(cfs_t *c, const model_t *m)
{
  int ret;

  c->bs = brseries_open(m->bslmax, c->sphr->npt, c->sphr->ri);

  ret = brseries_load(c->bs, m->fnbs);
  if ( ret != 0 ) {
    fprintf(stderr, "failed to initialize BS from %s\n", m->fnbs);
    return ret;
  }

  c->hasBr = 1;
  c->hasdBr = 1;

  return 0;
}



__inline static int cfs_save(cfs_t *c, char *fn)
{
  int i, npt = c->sphr->npt;
  FILE *fp;

  if ((fp = fopen(fn, "w")) == NULL ) {
    fprintf(stderr, "cannot write %s\n", fn);
    return -1;
  }

  for ( i = 0; i < npt; i++ ) {
    double Bri = (c->Br != NULL) ? (double) c->Br[i] : 0;
    fprintf(fp, "%8.6f %14.8f %14.8f %14.8f %14.8f "
                "%14.8f %14.8f %14.8f %14.8f %g\n",
        (double) c->sphr->ri[i],
        (double) c->cr[i], (double) c->tr[i], Bri,
        (double) c->dcr[i], (double) c->dtr[i],
        (double) c->Dcr[i], (double) c->Dtr[i],
        (double) c->fr[i], (double) c->bphi[i]);
  }
  fclose(fp);

  return 0;
}



#endif /* CFS_H__ */
