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
   fills c->bphi, c->fr, and c->rdfr */
__inline static void cfs_mkfr(cfs_t *c,
    const model_t *m, xdouble xi)
{
  sphr_t *sphr = c->sphr;
  int i, npt = m->npt;
  xdouble x, u, usr, rdu;
  xdouble dr = sphr->dr;

  /* set the hard-core boundary */
  c->bm = (int) (xi / dr + 0.5);

  /* compute f(r) */
  for ( i = 0; i < npt; i++ ) { /* compute f(r) = exp(-beta u(r)) - 1 */
    xdouble r = sphr->ri[i] * xi;

    if ( m->pottype == POTTYPE_GAUSS ) { /* f(r) = exp(-r^2) */
      xdouble r2 = pow_si(r, 2);
      c->fr[i] = -EXP(-r2);
      c->rdfr[i] = -2 * r2 * c->fr[i];
      c->bphi[i] = -LOG(c->fr[i] + 1);
    } else if ( m->pottype == POTTYPE_WCA
             || m->pottype == POTTYPE_LJ ) {
      xdouble invr, invr2, invr6;

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
      x = EXP( -c->bphi[i] );
      c->fr[i] = x - 1;
      c->rdfr[i] = m->beta * rdu * x;
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



/* Dfr[] --> Dfk[] */
__inline static void cfs_xir_Dfr2k(cfs_t *cb,
    xdouble xi, const model_t *m)
{
  sphr_t *sphr = cb->sphr;
  int i, npt = sphr->npt;

  if ( m->dim == 3 || m->pottype == POTTYPE_HS ) {
    /* NOTE: for three dimensions only */
    for ( i = 0; i < npt; i++ ) {
      xdouble k = sphr->ki[i];
      cb->Dfk[i] = -4 * PI * xi * SIN(k * xi) / k;
    }
  } else {
    sphr_r2k(sphr, cb->Dfr, cb->Dfk);
  }
}



/* Lfr[] --> Lfk[] */
__inline static void cfs_lamr_Lfr2k(cfs_t *cb,
    xdouble lam, const model_t *m)
{
  sphr_t *sphr = cb->sphr;
  int i, npt = sphr->npt;

  if ( m->dim == 3 || m->pottype == POTTYPE_HS ) {
    /* NOTE: for three dimensions only */
    for ( i = 0; i < npt; i++ ) {
      xdouble k = sphr->ki[i];
      cb->Lfk[i] = -4 * PI * lam * SIN(k * lam) / k;
    }
  } else {
    sphr_r2k(sphr, cb->Lfr, cb->Lfk);
  }
}



/* initialize the correlation functions */
__inline static void cfs_init(cfs_t *c, const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;

  /* initialize c->bphi, c->fr, c->rdfr, and c->bm */
  cfs_mkfr(c, m, 1);

  for ( i = 0; i < npt; i++ ) {
    c->dcr[i] = c->cr[i] = c->fr[i];
    c->tr[i] = 0;
  }

  /* df/dxi */
  if ( m->xitype == XITYPE_R ) {
    for ( i = 0; i < npt; i++ ) {
      c->Dfr[i] = -c->rdfr[i];
    }
  } else if ( m->xitype == XITYPE_F ) {
    for ( i = 0; i < npt; i++ ) {
      c->Dfr[i] = c->fr[i];
    }
  }

  cfs_xir_Dfr2k(c, 1, m);

  for ( i = 0; i < npt; i++ ) {
    c->Dcr[i] = c->Dfr[i];
  }

  /* df/dlam */
  if ( m->lamtype == LAMTYPE_R ) {
    for ( i = 0; i < npt; i++ ) {
      c->Lfr[i] = -c->rdfr[i];
    }
  } else {
    for ( i = 0; i < npt; i++ ) {
      c->Lfr[i] = c->fr[i];
    }
  }

  cfs_lamr_Lfr2k(c, 1, m);

  for ( i = 0; i < npt; i++ ) {
    c->Lcr[i] = c->Lfr[i];
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



/* initialize a set of correlation functions for xi < 1
 * with xi being the interaction radius */
__inline static int cfs_init_xir(cfs_t *c, cfs_t *cb,
    xdouble xi, const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;

  cfs_mkfr(cb, m, xi);

  for ( i = 0; i < npt; i++ ) {
    cb->Dfr[i] = (xi > 0 ? -cb->rdfr[i] / xi : 0.0);
  }

  cfs_xir_Dfr2k(cb, xi, m);

  if ( xi < 1 - 1e-8 ) {
    for ( i = 0; i < npt; i++ ) {
      cb->cr[i] = cb->fr[i];
    }
  } else {
    for ( i = 0; i < npt; i++ ) {
      cb->cr[i] = c->cr[i];
    }
  }

  sphr_r2k(cb->sphr, cb->fr, cb->fk); /* f(r) --> t(k) */

  for ( i = 0; i < npt; i++ ) {
    cb->tk[i] = cb->fk[i] * c->fk[i];
  }

  sphr_k2r(cb->sphr, cb->tk, cb->ffr); /* t(k) --> ff(r) */

  return 0;
}



/* initialize a set of correlation functions for xi,
   which satisfies f(r; xi) = xi f(r) */
__inline static int cfs_init_xif(cfs_t *c, cfs_t *cb,
    xdouble xi, int shallow)
{
  int i, npt = c->sphr->npt;

  for ( i = 0; i < npt; i++ ) {
    cb->fr[i] = c->fr[i] * xi;
    cb->Dfr[i] = c->Dfr[i];
    cb->rdfr[i] = c->rdfr[i] * xi;
  }

  /* preserve existing correlation functions */
  if ( shallow ) return 0;

  for ( i = 0; i < npt; i++ ) {
    cb->cr[i] = c->cr[i];
    cb->dcr[i] = c->dcr[i];
    cb->Dcr[i] = cb->Dfr[i];
    cb->Lcr[i] = cb->Lfr[i];
    cb->tr[i] = c->tr[i];
    cb->dtr[i] = c->dtr[i];
    cb->Dtr[i] = c->Dtr[i];
    cb->Ltr[i] = c->Ltr[i];
  }

  sphr_r2k(c->sphr, cb->fr, cb->fk); /* f(r) --> t(k) */

  for ( i = 0; i < npt; i++ ) {
    cb->tk[i] = cb->fk[i] * c->fk[i];
  }

  sphr_k2r(c->sphr, cb->tk, cb->ffr); /* t(k) --> ff(r) */

  return 0;
}



/* initialize a set of correlation functions for xi */
__inline static int cfs_init_xi(cfs_t *c, cfs_t *cb,
    xdouble xi, model_t *m, int shallow)
{
  int i;

  for ( i = 0; i < c->sphr->npt; i++ ) {
    cb->tr[i] = 0;
  }

  if ( m->xitype == XITYPE_R ) {
    return cfs_init_xir(c, cb, xi, m);
  } else if ( m->xitype == XITYPE_F ) {
    return cfs_init_xif(c, cb, xi, shallow);
  } else {
    return 0;
  }
}



/* initialize a set of correlation functions for lam < 1
 * with lam being the interaction radius */
__inline static int cfs_init_lamr(cfs_t *c, cfs_t *cb,
    xdouble lam, const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;

  cfs_mkfr(cb, m, lam);

  for ( i = 0; i < npt; i++ ) {
    cb->Lfr[i] = (lam > 0 ? -cb->rdfr[i] / lam : 0);
  }

  cfs_lamr_Lfr2k(cb, lam, m);

  if ( lam < 1 - 1e-8 ) {
    for ( i = 0; i < npt; i++ ) {
      cb->cr[i] = cb->fr[i];
    }
  } else {
    for ( i = 0; i < npt; i++ ) {
      cb->cr[i] = c->cr[i];
    }
  }

  sphr_r2k(cb->sphr, cb->fr, cb->fk); /* f(r) --> t(k) */

  for ( i = 0; i < npt; i++ ) {
    cb->tk[i] = cb->fk[i] * c->fk[i];
  }

  sphr_k2r(cb->sphr, cb->tk, cb->ffr); /* t(k) --> ff(r) */

  return 0;
}



/* initialize a set of correlation functions for xi */
__inline static int cfs_init_lamf(cfs_t *c, cfs_t *cb,
    xdouble lam, int shallow)
{
  int i, npt = c->sphr->npt;

  for ( i = 0; i < npt; i++ ) {
    cb->fr[i] = c->fr[i] * lam;
    cb->Lfr[i] = c->Lfr[i];
    cb->rdfr[i] = c->rdfr[i] * lam;
  }

  if ( shallow ) return 0;

  for ( i = 0; i < npt; i++ ) {
    cb->cr[i] = c->cr[i];
    cb->dcr[i] = c->dcr[i];
    cb->Dcr[i] = cb->Dfr[i];
    cb->Lcr[i] = cb->Lfr[i];
    cb->tr[i] = c->tr[i];
    cb->dtr[i] = c->dtr[i];
    cb->Dtr[i] = c->Dtr[i];
    cb->Ltr[i] = c->Ltr[i];
  }

  sphr_r2k(c->sphr, cb->fr, cb->fk); /* f(r) --> t(k) */

  for ( i = 0; i < npt; i++ ) {
    cb->tk[i] = cb->fk[i] * c->fk[i];
  }

  sphr_k2r(c->sphr, cb->tk, cb->ffr); /* t(k) --> ff(r) */

  return 0;
}



/* initialize a set of correlation functions for xi */
__inline static int cfs_init_lam(cfs_t *c, cfs_t *cb,
    xdouble lam, model_t *m, int shallow)
{
  int i;

  for ( i = 0; i < c->sphr->npt; i++ ) {
    cb->tr[i] = 0;
  }

  if ( m->lamtype == LAMTYPE_R ) {
    return cfs_init_lamr(c, cb, lam, m);
  } else if ( m->lamtype == LAMTYPE_F ) {
    return cfs_init_lamf(c, cb, lam, shallow);
  } else {
    /* for the c, h, t routes,
       correlation functions are to be computed explicitly
       so no need for initialization */
    return 0;
  }
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
    fprintf(fp, "%8.6f %14.8f %14.8f %14.8f %14.8f %14.8f %14.8f %14.8f %14.8f %g\n",
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
