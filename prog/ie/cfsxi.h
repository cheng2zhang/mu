#ifndef CFSXI_H__
#define CFSXI_H__



/* correlation functions for xi */



#include "cfs.h"



/* Dfr[] --> Dfk[] */
__inline static void cfs_xir_Dfr2k(cfs_t *c,
    xdouble xi, const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;

  if ( m->dim == 3 || m->pottype == POTTYPE_HS ) {
    /* NOTE: for three dimensions only */
    for ( i = 0; i < npt; i++ ) {
      xdouble k = sphr->ki[i];
      c->Dfk[i] = -4 * PI * xi * SIN(k * xi) / k;
    }
  } else {
    sphr_r2k(sphr, c->Dfr, c->Dfk);
  }
}



/* initialize Dfr */
__inline static void cfs_initDfr(cfs_t *c, model_t *m)
{
  int i, npt = c->sphr->npt;

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
}



/* initialize Dfr */
__inline static void cfs_initDfr2(cfs_t *c1, cfs_t *c2,
    model_t *m)
{
  sphr_t *sphr = c2->sphr;
  int i, npt = sphr->npt;

  /* df/dxi */
  if ( m->xitype == XITYPE_F ) {
    for ( i = 0; i < npt; i++ ) {
      c2->Dfr[i] = c2->fr[i] - c1->fr[i];
    }
  }

  sphr_r2k(sphr, c2->Dfr, c2->Dfk);

  for ( i = 0; i < npt; i++ ) {
    c2->Dcr[i] = c2->Dfr[i];
  }
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



/* initialize a set of correlation functions for xi,
   which satisfies f(r; xi) = f1(r) + xi (f2(r) - f1(r))*/
__inline static int cfs_init_xi2f(cfs_t *c1, cfs_t *c2,
    cfs_t *cb, xdouble xi, int shallow)
{
  sphr_t *sphr = c2->sphr;
  int i, npt = sphr->npt;

  for ( i = 0; i < npt; i++ ) {
    cb->fr[i] = c1->fr[i] + (c2->fr[i] - c1->fr[i]) * xi;
    cb->Dfr[i] = c2->fr[i] - c1->fr[i];
    cb->rdfr[i] = c1->rdfr[i] + (c2->rdfr[i] - c1->rdfr[i]) * xi;
  }

  /* preserve existing correlation functions */
  if ( shallow ) return 0;

  for ( i = 0; i < npt; i++ ) {
    cb->cr[i] = c2->cr[i];
    cb->dcr[i] = c2->dcr[i];
    cb->Dcr[i] = cb->Dfr[i];
    cb->Lcr[i] = cb->Lfr[i];
    cb->tr[i] = c2->tr[i];
    cb->dtr[i] = c2->dtr[i];
    cb->Dtr[i] = c2->Dtr[i];
    cb->Ltr[i] = c2->Ltr[i];
  }

  sphr_r2k(c2->sphr, cb->fr, cb->fk); /* f(r) --> t(k) */

  for ( i = 0; i < npt; i++ ) {
    cb->tk[i] = cb->fk[i] * c2->fk[i];
  }

  sphr_k2r(c2->sphr, cb->tk, cb->ffr); /* t(k) --> ff(r) */

  return 0;
}



#endif /* CFSXI_H__ */
