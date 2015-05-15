#ifndef MDIIS_H__
#define MDIIS_H__



/* MDIIS solver */



#include "picard.h"



typedef struct {
  int npt;
  int mnb; /* maximal number of bases */
  int nb; /* number of functions in the basis */
  xdouble **cr; /* basis */
  xdouble **res; /* residues */
  xdouble *mat; /* correlations of residues */
  xdouble *mat2; /* temporary matrix for the LU decomposition */
  xdouble *coef; /* coefficients */
  xdouble *crbest;
  xdouble errmin;
} mdiis_t;



/* open an mdiis object */
static mdiis_t *mdiis_open(int npt, int mnb)
{
  mdiis_t *m;
  int mnb1;

  xnew(m, 1);
  m->npt = npt;
  m->mnb = mnb;
  m->nb = 0;
  mnb1 = mnb + 1;
  MAKE2DARR(m->cr, mnb1, npt);
  MAKE2DARR(m->res, mnb1, npt);
  MAKE1DARR(m->mat, mnb1 * mnb1);
  MAKE1DARR(m->mat2, mnb1 * mnb1);
  MAKE1DARR(m->coef, mnb1);
  MAKE1DARR(m->crbest, npt);
  m->errmin = 1e300;
  return m;
}



/* close the mdiis object */
static void mdiis_close(mdiis_t *m)
{
  int mnb1, npt;
  if ( m == NULL ) return;
  mnb1 = m->mnb + 1;
  npt = m->npt;
  FREE2DARR(m->cr,      mnb1, npt);
  FREE2DARR(m->res,     mnb1, npt);
  FREE1DARR(m->mat,     mnb1 * mnb1);
  FREE1DARR(m->mat2,    mnb1 * mnb1);
  FREE1DARR(m->coef,    mnb1);
  FREE1DARR(m->crbest,  npt);
  free(m);
}



static int mdiis_solve(mdiis_t *m)
{
  int nb = m->nb, nb1 = m->nb + 1, mnb1 = m->mnb + 1, i, j;

  for ( i = 0; i < nb; i++ ) m->coef[i] = 0;
  m->coef[nb] = -1;
  /* copy the matrix, for the content is to be destroyed */
  for ( i = 0; i < nb1; i++ )
    for ( j = 0; j < nb1; j++ )
      m->mat2[i*nb1 + j] = m->mat[i*mnb1 + j];
  for ( i = 0; i < nb1; i++ )
    m->mat2[i*nb1 + nb] = m->mat2[nb*nb1 + i] = -1;
  m->mat2[nb*nb1 + nb] = 0;
  if ( lusolve(m->mat2, m->coef, nb1, 1e-20) != 0 ) {
    fprintf(stderr, "MDIIS lusolve failed\n");
    exit(1);
  }
  return 0;
}



/* construct the new c(r) */
static void mdiis_gencr(mdiis_t *m, xdouble *cr, xdouble damp)
{
  int npt = m->npt, nb = m->nb;
  int k, il;

  for ( il = 0; il < npt; il++ )
    m->cr[nb][il] = 0;
  for ( k = 0; k < nb; k++ ) {
    xdouble coef = m->coef[k];
    for ( il = 0; il < npt; il++ )
      m->cr[nb][il] += coef * (m->cr[k][il] + damp * m->res[k][il]);
  }

  /* save m->cr[nb] to c(r) */
  cparr(cr, m->cr[nb], npt);
}



/* compute the dot product */
static xdouble mdiis_getdot(xdouble *a, xdouble *b, int n)
{
  int i;
  xdouble x = 0;

  for ( i = 0; i < n; i++ ) x += a[i] * b[i];
  return x / n;
}



/* build the residue correlation matrix */
static int mdiis_build(mdiis_t *m, xdouble *cr, xdouble *res)
{
  int ib, mnb, mnb1, npt = m->npt;

  m->nb = 1;
  mnb = m->mnb;
  mnb1 = m->mnb + 1;

  cparr(m->cr[0], cr, npt);
  cparr(m->res[0], res, npt);

  m->mat[0] = mdiis_getdot(m->res[0], m->res[0], npt);
  for ( ib = 0; ib < mnb; ib++ )
    m->mat[ib*mnb1 + mnb] = m->mat[mnb*mnb1 + ib] = -1;
  m->mat[mnb*mnb1 + mnb] = 0;
  return 0;
}



/* replace base ib by cr */
static int mdiis_update(mdiis_t *m, xdouble *cr, xdouble *res,
    xdouble err, int verbose)
{
  int i, ib, nb, mnb1, npt = m->npt;
  xdouble dot, max;

  nb = m->nb;
  mnb1 = m->mnb + 1;

  /* save this function if it achieves the minimal error so far */
  if ( err < m->errmin ) {
    cparr(m->crbest, m->cr[nb], npt);
    m->errmin = err;
  }

  if ( nb < m->mnb ) {
    ib = nb;
    m->nb = ++nb;
  } else {
    /* choose the base with the largest residue */
    ib = 0;
    for ( i = 1; i < nb; i++ )
      /* the diagonal represents the error */
      if ( m->mat[i*mnb1+i] > m->mat[ib*mnb1 + ib] )
        ib = i;
    max = m->mat[ib*mnb1 + ib];

    dot = mdiis_getdot(res, res, npt);
    if ( dot > max ) {

#ifndef MDIIS_THRESHOLD
#define MDIIS_THRESHOLD 10.0
#endif

      if ( SQRT(dot) < MDIIS_THRESHOLD ) {
        static int once;

        /* stagnant, rebuild the matrix */
        mdiis_build(m, cr, res);
        if ( verbose >= 2 || (verbose && !once) ) {
          fprintf(stderr, "MDIIS: bad basis, %g is greater than %g, reset, error:",
            (double) dot, (double) max);
          for ( i = 0; i < nb; i++ )
            fprintf(stderr, " %g", (double) m->mat[i*mnb1+i]);
          fprintf(stderr, "\n");
          once = 1;
        }
        return 0;
      }
    }
  }

  /* replace base ib by cr */
  cparr(m->cr[ib], cr, npt);
  cparr(m->res[ib], res, npt);

  /* update the residue correlation matrix
   * note: we do not need to update the last row & column */
  for ( i = 0; i < nb; i++ )
    m->mat[i*mnb1 + ib] = m->mat[ib*mnb1 + i]
      = mdiis_getdot(m->res[i], res, npt);
  return ib;
}



/* compute correlation functions by the MDIIS method */
__inline static xdouble iter_mdiis(cfs_t *c, const model_t *m)
{
  mdiis_t *mdiis;
  sphr_t *sphr = c->sphr;
  xdouble err, errp = 1e300;
  int it, streak = 0, ibp = 0, ib, npt = sphr->npt;

  /* open an mdiis object */
  mdiis = mdiis_open(npt, m->mdiis->nbases);

  /* construct the initial basis */
  cparr(mdiis->crbest, c->cr, npt);
  mdiis->errmin = errp = step_picard(c, m);
  mdiis_build(mdiis, c->cr, c->res);

  for ( it = 0; it < m->itmax; it++ ) {
    /* compute a set of coefficients of combining basic functions */
    mdiis_solve(mdiis);
    /* construct a new cr from the combination */
    mdiis_gencr(mdiis, c->cr, m->mdiis->damp);
    /* compute the residue vector and error */
    err = step_picard(c, m);
    /* add the new cr into the basis */
    ib = mdiis_update(mdiis, c->cr, c->res, err, m->verbose);

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iter_mdiis: it %d, err %g -> %g (min %g), ib %d -> %d\n",
          it, (double) errp, (double) err, (double) mdiis->errmin, ibp, ib);
    }

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    if ( err < m->tol || streak > m->mdiis->streakmax ) {
      break;
    }

    ibp = ib;
    errp = err;
  }
  /* use the best cr discovered so far */
  cparr(c->cr, mdiis->crbest, npt);
  /* update the corresponding ck, tr, tk */
  err = step_picard(c, m);
  if ( m->verbose || err > m->tol ) {
    fprintf(stderr, "iter_mdiis finished in %d steps, err %g, streak %d\n",
        it, (double) err, streak);
  }

  mdiis_close(mdiis);
  return err;
}



/* compute d/d(rho) functions by the MDIIS method */
__inline static xdouble iterd_mdiis(cfs_t *c, const model_t *m)
{
  mdiis_t *mdiis;
  sphr_t *sphr = c->sphr;
  xdouble err, errp = 1e300;
  int it, streak = 0, ibp = 0, ib, npt = sphr->npt;

  /* open an mdiis object */
  mdiis = mdiis_open(npt, m->mdiis->nbases);

  /* construct the initial basis */
  cparr(mdiis->crbest, c->dcr, npt);
  mdiis->errmin = errp = stepd_picard(c, m);
  mdiis_build(mdiis, c->dcr, c->res);

  for ( it = 0; it < m->itmax; it++ ) {
    /* compute a set of coefficients of combining basic functions */
    mdiis_solve(mdiis);
    /* construct a new dcr from the combination */
    mdiis_gencr(mdiis, c->dcr, m->mdiis->damp);
    /* compute the residue vector and error */
    err = stepd_picard(c, m);
    /* add the new dcr into the basis */
    ib = mdiis_update(mdiis, c->dcr, c->res, err, m->verbose);

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iterd_mdiis: it %d, err %g -> %g (min %g), ib %d -> %d\n",
          it, (double) errp, (double) err, (double) mdiis->errmin, ibp, ib);
    }

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    if ( err < m->tol || streak > m->mdiis->streakmax ) {
      break;
    }

    ibp = ib;
    errp = err;
  }

  /* use the best cr discovered so far */
  cparr(c->dcr, mdiis->crbest, npt);
  /* update the corresponding ck, tr, tk */
  err = stepd_picard(c, m);
  if ( m->verbose || err > m->tol ) {
    fprintf(stderr, "iterd_mdiis finished in %d steps, err %g, streak %d\n",
        it, (double) err, streak);
  }

  mdiis_close(mdiis);
  return err;
}



/* solver the xi != 1 case by the MDIIS method */
__inline static xdouble iterx_mdiis(cfs_t *c, cfs_t *cx, const model_t *m)
{
  mdiis_t *mdiis;
  sphr_t *sphr = c->sphr;
  xdouble err, errp = 1e300;
  int it, streak = 0, ibp = 0, ib, npt = sphr->npt;

  /* open an mdiis object */
  mdiis = mdiis_open(npt, m->mdiis->nbases);

  /* construct the initial basis */
  cparr(mdiis->crbest, cx->cr, npt);
  mdiis->errmin = errp = stepx_picard(c, cx, m);
  mdiis_build(mdiis, cx->cr, cx->res);

  for ( it = 0; it < m->itmax; it++ ) {
    /* compute a set of coefficients of combining basic functions */
    mdiis_solve(mdiis);
    /* construct a new dcr from the combination */
    mdiis_gencr(mdiis, cx->cr, m->mdiis->damp);
    /* compute the residue vector and error */
    err = stepx_picard(c, cx, m);
    /* add the new dcr into the basis */
    ib = mdiis_update(mdiis, cx->cr, cx->res, err, m->verbose);

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iterx_mdiis: it %d, err %g -> %g (min %g), ib %d -> %d\n",
          it, (double) errp, (double) err, (double) mdiis->errmin, ibp, ib);
    }

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    if ( err < m->tol || streak > m->mdiis->streakmax ) {
      break;
    }

    ibp = ib;
    errp = err;
  }

  /* use the best cr discovered so far */
  cparr(cx->cr, mdiis->crbest, npt);
  /* update the corresponding ck, tr, tk */
  err = stepx_picard(c, cx, m);
  if ( m->verbose || err > m->tol ) {
    fprintf(stderr, "iterx_mdiis finished in %d steps, err %g, streak %d\n",
        it, (double) err, streak);
  }

  mdiis_close(mdiis);
  return err;
}



/* solve d/d(rho) functions with xi != 1 by the MDIIS method */
__inline static xdouble iterxd_mdiis(cfs_t *c, cfs_t *cx, const model_t *m)
{
  mdiis_t *mdiis;
  sphr_t *sphr = c->sphr;
  xdouble err, errp = 1e300;
  int it, streak = 0, ibp = 0, ib, npt = sphr->npt;

  /* open an mdiis object */
  mdiis = mdiis_open(npt, m->mdiis->nbases);

  /* construct the initial basis */
  cparr(mdiis->crbest, cx->dcr, npt);
  mdiis->errmin = errp = stepxd_picard(c, cx, m);
  mdiis_build(mdiis, cx->dcr, cx->res);

  for ( it = 0; it < m->itmax; it++ ) {
    /* compute a set of coefficients of combining basic functions */
    mdiis_solve(mdiis);
    /* construct a new dcr from the combination */
    mdiis_gencr(mdiis, cx->dcr, m->mdiis->damp);
    /* compute the residue vector and error */
    err = stepxd_picard(c, cx, m);
    /* add the new dcr into the basis */
    ib = mdiis_update(mdiis, cx->dcr, cx->res, err, m->verbose);

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iterxd_mdiis: it %d, err %g -> %g (min %g), ib %d -> %d\n",
          it, (double) errp, (double) err, (double) mdiis->errmin, ibp, ib);
    }

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    if ( err < m->tol || streak > m->mdiis->streakmax ) {
      break;
    }

    ibp = ib;
    errp = err;
  }

  /* use the best cr discovered so far */
  cparr(cx->dcr, mdiis->crbest, npt);
  /* update the corresponding ck, tr, tk */
  err = stepxd_picard(c, cx, m);
  if ( m->verbose || err > m->tol ) {
    fprintf(stderr, "iterxd_mdiis finished in %d steps, err %g, streak %d\n",
        it, (double) err, streak);
  }

  mdiis_close(mdiis);
  return err;
}



/* solve d/d(xi) functions with xi != 1 by the MDIIS method */
__inline static xdouble iterxD_mdiis(cfs_t *c, cfs_t *cx, const model_t *m)
{
  mdiis_t *mdiis;
  sphr_t *sphr = c->sphr;
  xdouble err, errp = 1e300;
  int it, streak = 0, ibp = 0, ib, npt = sphr->npt;

  /* open an mdiis object */
  mdiis = mdiis_open(npt, m->mdiis->nbases);

  /* construct the initial basis */
  cparr(mdiis->crbest, cx->Dcr, npt);
  mdiis->errmin = errp = stepxD_picard(c, cx, m);
  mdiis_build(mdiis, cx->Dcr, cx->res);

  for ( it = 0; it < m->itmax; it++ ) {
    /* compute a set of coefficients of combining basic functions */
    mdiis_solve(mdiis);
    /* construct a new dcr from the combination */
    mdiis_gencr(mdiis, cx->Dcr, m->mdiis->damp);
    /* compute the residue vector and error */
    err = stepxD_picard(c, cx, m);
    /* add the new dcr into the basis */
    ib = mdiis_update(mdiis, cx->Dcr, cx->res, err, m->verbose);

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iterxD_mdiis: it %d, err %g -> %g (min %g), ib %d -> %d\n",
          it, (double) errp, (double) err, (double) mdiis->errmin, ibp, ib);
    }

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    if ( err < m->tol || streak > m->mdiis->streakmax ) {
      break;
    }

    ibp = ib;
    errp = err;
  }

  /* use the best cr discovered so far */
  cparr(cx->Dcr, mdiis->crbest, npt);
  /* update the corresponding ck, tr, tk */
  err = stepxD_picard(c, cx, m);
  if ( m->verbose || err > m->tol ) {
    fprintf(stderr, "iterxD_mdiis finished in %d steps, err %g, streak %d\n",
        it, (double) err, streak);
  }

  mdiis_close(mdiis);
  return err;
}



/* solve d/d(lam) functions with lam != 1 by the MDIIS method */
__inline static xdouble iterlL_mdiis(cfs_t *cx, const model_t *m)
{
  mdiis_t *mdiis;
  sphr_t *sphr = cx->sphr;
  xdouble err, errp = 1e300;
  int it, streak = 0, ibp = 0, ib, npt = sphr->npt;

  /* open an mdiis object */
  mdiis = mdiis_open(npt, m->mdiis->nbases);

  /* construct the initial basis */
  cparr(mdiis->crbest, cx->Lcr, npt);
  mdiis->errmin = errp = steplL_picard(cx, m);
  mdiis_build(mdiis, cx->Lcr, cx->res);

  for ( it = 0; it < m->itmax; it++ ) {
    /* compute a set of coefficients of combining basic functions */
    mdiis_solve(mdiis);
    /* construct a new dcr from the combination */
    mdiis_gencr(mdiis, cx->Lcr, m->mdiis->damp);
    /* compute the residue vector and error */
    err = steplL_picard(cx, m);
    /* add the new dcr into the basis */
    ib = mdiis_update(mdiis, cx->Lcr, cx->res, err, m->verbose);

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iterlL_mdiis: it %d, err %g -> %g (min %g), ib %d -> %d\n",
          it, (double) errp, (double) err, (double) mdiis->errmin, ibp, ib);
    }

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    if ( err < m->tol || streak > m->mdiis->streakmax ) {
      break;
    }

    ibp = ib;
    errp = err;
  }

  /* use the best cr discovered so far */
  cparr(cx->Lcr, mdiis->crbest, npt);
  /* update the corresponding ck, tr, tk */
  err = steplL_picard(cx, m);
  if ( m->verbose || err > m->tol ) {
    fprintf(stderr, "iterxD_mdiis finished in %d steps, err %g, streak %d\n",
        it, (double) err, streak);
  }

  mdiis_close(mdiis);
  return err;
}



#endif /* defined(IEMDIIS_H__) */

