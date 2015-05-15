#ifndef CFSLAM_H__
#define CFSLAM_H__



/* correlation functions for lam */



#include "cfs.h"



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



/* initialize Lfr */
__inline static void cfs_initLfr(cfs_t *c, model_t *m)
{
  int i, npt = c->sphr->npt;

  /* df/dlam */
  for ( i = 0; i < npt; i++ ) {
    if ( m->lamtype == LAMTYPE_U ) {
      c->Lfr[i] = (c->fr[i] + 1) * (-c->bphi[i]);
    } else if ( m->lamtype == LAMTYPE_R ) {
      c->Lfr[i] = -c->rdfr[i];
    } else if ( m->lamtype == LAMTYPE_F ) {
      c->Lfr[i] = c->fr[i];
    }
  }

  cfs_lamr_Lfr2k(c, 1, m);

  for ( i = 0; i < npt; i++ ) {
    c->Lcr[i] = c->Lfr[i];
  }
}



/* initialize a set of correlation functions for lam < 1
 * with lam being prortional to the potential  */
__inline static int cfs_init_lamu(cfs_t *c, cfs_t *cb,
    xdouble lam, const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;

  cfs_mkfr(cb, m, 1, lam);

  for ( i = 0; i < npt; i++ ) {
    cb->Lfr[i] = -cb->bphi[i] * (cb->fr[i] + 1);
    cb->Lcr[i] = cb->Lfr[i];
  }

  cfs_lamr_Lfr2k(cb, lam, m);

  for ( i = 0; i < npt; i++ ) {
    if ( lam < 1 - 1e-8 ) {
      cb->cr[i] = cb->fr[i];
    } else {
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



/* initialize a set of correlation functions for lam < 1
 * with lam being the interaction radius */
__inline static int cfs_init_lamr(cfs_t *c, cfs_t *cb,
    xdouble lam, const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;

  cfs_mkfr(cb, m, lam, 1);

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

  if ( m->lamtype == LAMTYPE_U ) {
    return cfs_init_lamu(c, cb, lam, m);
  } else if ( m->lamtype == LAMTYPE_R ) {
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



#endif /* CFSLAM_H__ */
