#ifndef SC_H__
#define SC_H__



#include "solver.h"



/* determine the free parameter s in the self-consistent closure
 * The self-consistency is based on the agreement of d(bP)/drho
 * from the compressibility and virial routes
 * In the compressibility route,
 *  d(bP)/drho = 1 - rho Int c dr
 * In the virial route,
 *  bP = rho + rho^2/(2dim) Int r df y
 * and
 *  d(bP)/drho = 1 + rho/dim Int r df y + rho^2/2d Int r df dy/drho
 * Thus, the self-consistency condition means that
 *  Int [ c + r df/dim (y + rho/2 dy/drho) ] dr = 0  (*)
 * */
__inline static xdouble sc_getds_p(cfs_t *c,
    const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt, dim = sphr->dim;
  xdouble rDm1, rho = m->rho;
  xdouble num = 0, den = 0, y, dydt, w, dwdt, ds;

  for ( i = 0; i < npt; i++ ) {
    /* To satisfy the self-consistent condition (*),
     * we solve ds, to the first order, from the following equation
     *  0 = Int [ c + r f'/dim (y + rho/2 dy/drho) ] dr
     *    + ds Int [ dc/ds + r f'/dim (dy/ds + rho/2 d^2y/ds/drho) ] dr
     *    = Int [ c + r f'/dim (y + rho/2 dy/drho) ] dr
     *    + ds Int [ (1 + f) w + r f'/dim (w + rho/2 dw/dt dt/drho) ] dr
     * where,
     *  w = dy/ds,
     *  dc/ds = (1 + f) dy/ds = (1 + f) w,
     *    because c = (1 + f) y - t - 1.
     */
    y = getyr(c->tr[i], &dydt, &w, &dwdt, m);
    rDm1 = sphr->rDm1[i];

    num += c->cr[i] * rDm1;
    den += (1 + c->fr[i]) * w * rDm1; /* dc/drho = (1 + f) dy/drho */

    /* Int r f'(r) [y(r) + 0.5 rho dy/drho] / dim dr */
    num += c->rdfr[i] * (y + 0.5 * rho * dydt * c->dtr[i]) * rDm1 / dim;
    /* Int r f'(r) [w(r) + 0.5 rho dw/drho] / dim dr */
    den += c->rdfr[i] * (w + 0.5 * rho * dwdt * c->dtr[i]) * rDm1 / dim;
  }

  /* amount of increase of ds */
  if ( FABS(den) < XDBL_MIN ) {
    ds = 0;
  } else {
    ds = -num / den;
  }

  return ds;
}



/* determine the free parameter s in the self-consistent closure
 * the self consistency is based on the agreement of d^2mu/dxi/drho
 * from the compressibility and virial routes
 * In the compressibility route,
 *  d(b muex)/drho = - Int c dr
 * and
 *  d^2(b muex)/drho/dxi = - Int dc/dxi dr
 * In the virial route,
 *  d(b muex)/dxi = - rho Int df/dxi y dr
 * and
 *  d^2(b muex)/dxi/drho = -Int df/dxi (y + rho dy/drho) dr
 * Thus, the self-consistency condition means that
 *  Int [ dc/dxi - df/dxi (y + rho dy/drho) ] dr = 0  (*)
 * We shall assume df/dxi = f.
 * */
__inline static xdouble sc_getds_mu(cfs_t *c,
    const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;
  xdouble rho = m->rho;
  xdouble num = 0, den = 0, y, dydt, w, dwdt, f, ds;

  for ( i = 0; i < npt; i++ ) {
    /* d(bmu)/dxi = -rho Int (df/dxi) y dr
     *   ==> d^2(bmu)/dxi drho = -Int (df/dxi) (y + rho dy/drho) dr
     * d(bmu)/drho = -Int c dr
     *   ==> d^2(bmu)/dxi drho = -Int (dc/dxi) dr
     *
     * Int [ (dc/dxi) - (df/dxi) (y + rho dy/drho) ] dr
     *  + ds Int [ d^2c/dxi/ds - (df/dxi) (dy/ds + rho d^2y/drho/ds) ] dr = 0
     * With
     *  dc/dxi = (df/dxi) y + (1 + f) dy/dxi - dt/dxi,
     *  d^2c/dxi/ds = (df/dxi) w + (1 + f) dw/dxi,
     *  w = dy/ds,
     * we get
     *  Int [ dc/dxi - (df/dxi) (y + rho dy/drho) ] dr
     *  + ds Int [ (1 + f) dw/dxi - f rho dw/drho ] dr = 0
     * */
    y = getyr(c->tr[i], &dydt, &w, &dwdt, m);
    f = c->fr[i];
    num += (c->Dcr[i] - f * (y + rho * dydt * c->dtr[i])) * sphr->rDm1[i];
    den += ((1 + f) * dwdt * c->Dtr[i] - f * w - f * rho * dwdt * c->dtr[i])
         * sphr->rDm1[i];
  }
  ds = -num/den;

  return ds;
}



/* update the self-consistent parameter, s */
__inline static xdouble sc_updates(cfs_t *c,
    model_t *m, xdouble ds)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;
  xdouble w;

  /* bound the updating magnitude */
  if ( ds > m->scdsmax ) {
    ds = m->scdsmax;
  } else if ( ds < -m->scdsmax ) {
    ds = -m->scdsmax;
  }

  /* use ds to correct the correlation functions */
  for ( i = 0; i < npt; i++ ) {
    getyr(c->tr[i], NULL, &w, NULL, m);
    /* dc/ds = (1 + f) dy/ds - dt/ds (dropping dt/ds)
             = (1 + f) w */
    c->cr[i] += (1 + c->fr[i]) * w * ds;
  }

  return m->ies += ds;
}



static int iter_sc(cfs_t *c, model_t *m)
{
  int k;
  xdouble ds;

  if ( m->sctype == SCTYPE_P ) {
    /* dP/drho consistent */
    for ( k = 0; ; k++ ) {
      iter(c, m);
      ds = sc_getds_p(c, m);
      if ( FABS(ds) < m->sctol ) {
        break;
      } else {
        sc_updates(c, m, ds);
      }
    }
  } else if ( m->sctype == SCTYPE_MU ) {
    /* d^2mu/drho/dxi consistent */
    for ( k = 0; ; k++ ) {
      iter(c, m);
      iterd(c, m);
      iterxD(c, c, m);
      ds = sc_getds_mu(c, m);
      if ( FABS(ds) < m->sctol ) {
        break;
      } else {
        sc_updates(c, m, ds);
      }
    }
  } else {
    iter(c, m);
  }

  /*
  if ( m->sctype != SCTYPE_NONE ) {
      fprintf(stderr, "rho %g, s %g\n", (double) m->rho, (double) m->ies);
  }
  */

  return 0;
}





#endif /* SC_H__ */
