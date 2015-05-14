#ifndef PICARD_H__
#define PICARD_H__





#include "cfs.h"
#include "cfsxi.h"
#include "cfslam.h"
#include "closure.h"





/* do a step of direct (Picard) iteration */
__inline static xdouble step_picard(cfs_t *c, const model_t *m)
{
  int i, npt = c->sphr->npt;
  xdouble rho = m->rho, yr, x, err;

  sphr_r2k(c->sphr, c->cr, c->ck);

  for ( i = 0; i < npt; i++ ) {
    c->tk[i] = rho * c->ck[i] * c->ck[i] / (1 - rho * c->ck[i]);
  }

  sphr_k2r(c->sphr, c->tk, c->tr);

  /* closure */
  for ( err = 0, i = 0; i < npt; i++ ) {
    if ( c->hasBr ) {
      yr = EXP(c->tr[i] + c->Br[i]);
    } else {
      yr = getyr(c->tr[i], NULL, NULL, NULL, m);
    }
    c->res[i] = (1 + c->fr[i]) * yr - (1 + c->tr[i]) - c->cr[i];
    if ( (x = FABS(c->res[i])) > err ) {
      err = x;
    }
  }
  return err;
}



/* Picard iteration */
__inline static xdouble iter_picard(cfs_t *c, const model_t *m)
{
  int i, npt = c->sphr->npt, it, streak = 0;
  xdouble err, errp;

  err = errp = 1e300;
  for ( it = 0; it < m->itmax; it++ ) {
    err = step_picard(c, m);

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    /* if the error is small enough or
     * if it starts to diverge, stop */
    if ( err < m->tol || streak >= m->picard->streakmax ) {
      break;
    }

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iter_picard %d: err %g -> %g, damp %g\n",
              it, (double) errp, (double) err, (double) m->picard->damp);
    }

    errp = err;
    for ( i = 0; i < npt; i++ ) {
      c->cr[i] += m->picard->damp * c->res[i];
    }
  }

  if ( err > m->tol ) {
    fprintf(stderr, "iter %d failed to converge, err %g, streak %d\n",
            it, (double) err, streak);
    return -1;
  } else {
    return 0;
  }
}



/* do a step of direct (Picard) iteration for d/d(rho) functions */
static xdouble stepd_picard(cfs_t *c, const model_t *m)
{
  int i, npt = m->npt;
  xdouble hk, err, dydt, x;

  sphr_r2k(c->sphr, c->dcr, c->dck);

  for ( i = 0; i < npt; i++ ) {
    hk = c->ck[i] + c->tk[i];
    c->dtk[i] = hk * hk + m->rho * hk * (2 + m->rho * hk) * c->dck[i];
  }

  sphr_k2r(c->sphr, c->dtk, c->dtr);

  for ( err = 0, i = 0; i < npt; i++ ) {
    /* dc = (1 + f) dy - dt = [(1 + f) Y' - 1] dt */
    if ( c->hasBr && c->hasdBr ) {
      c->res[i] = (1 + c->fr[i]) * EXP(c->tr[i] + c->Br[i])
                * (c->dtr[i] + c->dBr[i]) - c->dtr[i] - c->dcr[i];
    } else {
      getyr(c->tr[i], &dydt, NULL, NULL, m);
      c->res[i] = ((1 + c->fr[i]) * dydt - 1) * c->dtr[i] - c->dcr[i];
    }
    if ( (x = FABS(c->res[i])) > err ) {
      err = x;
    }
    if ( c->res[i] > m->crmax ) {
      c->res[i] = m->crmax;
    } else if ( c->res[i] < -m->crmax ) {
      c->res[i] = -m->crmax;
    }
  }

  return err;
}



/* solve d/d(rho) functions */
__inline static int iterd_picard(cfs_t *c, const model_t *m)
{
  int i, npt = m->npt, it, streak = 0;
  xdouble err, errp;

  err = errp = 1e300;
  for ( it = 0; it < m->itmax; it++ ) {
    err = stepd_picard(c, m);

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    if ( err < m->tol || streak >= m->picard->streakmax ) {
      break;
    }

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iterd %d, err %g\n",
          it, (double) err);
    }

    errp = err;
    for ( i = 0; i < npt; i++ ) {
      c->dcr[i] += m->picard->damp * c->res[i];
    }
  }

  if ( err > m->tol ) {
    fprintf(stderr, "iterd %d: failed to converge, err %g, streak %d\n",
            it, (double) err, streak);
    return -1;
  } else {
    return 0;
  }
}



/* do a step of direct (Picard) iteration
   for the xi != 1 case, xi is the charging parameter */
static xdouble stepx_picard(cfs_t *c, cfs_t *cx, const model_t *m)
{
  int i, npt = m->npt;
  xdouble err, yr, x;

  sphr_r2k(cx->sphr, cx->cr, cx->ck);

  for ( i = 0; i < npt; i++ ) {
    cx->tk[i] = m->rho * cx->ck[i] * (c->ck[i] + c->tk[i]);
  }

  sphr_k2r(cx->sphr, cx->tk, cx->tr);

  for ( err = 0, i = 0; i < npt; i++ ) {
    if ( cx->hasBr ) {
      yr = EXP(cx->tr[i] + cx->Br[i]);
    } else {
      yr = getyr(cx->tr[i], NULL, NULL, NULL, m);
    }
    cx->res[i] = (1 + cx->fr[i]) * yr - (1 + cx->tr[i]) - cx->cr[i];
    if ( (x = FABS(cx->res[i])) > err ) {
      err = x;
    }
  }

  return err;
}



/* solve the xi != 1 case, xi is the charging parameter */
__inline static int iterx_picard(cfs_t *c, cfs_t *cx,
    const model_t *m)
{
  int i, npt = m->npt, it, streak = 0;
  xdouble err, errp;

  err = errp = 1e300;
  for ( it = 0; it < m->itmax; it++ ) {
    err = stepx_picard(c, cx, m);

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    if ( err < m->tol || streak >= m->picard->streakmax ) {
      break;
    }

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iterx %d: err %g, damp %g\n",
              it, (double) err, (double) m->picard->damp);
    }

    errp = err;
    for ( i = 0; i < npt; i++ ) {
      cx->cr[i] += m->picard->damp * cx->res[i];
    }
  }

  if ( err > m->tol ) {
    fprintf(stderr, "iterx %d: failed to converge, err %g, streak %d\n",
            it, (double) err, streak);
    return -1;
  } else {
    return 0;
  }
}



/* do a step of direct (Picard) iteration
   for the d/d(rho) functions
   for the xi != 1 case, xi is the charging parameter */
static xdouble stepxd_picard(cfs_t *c, cfs_t *cx, const model_t *m)
{
  int i, npt = m->npt;
  xdouble hk, dhk, err, dydt, x;

  sphr_r2k(cx->sphr, cx->dcr, cx->dck);

  for ( i = 0; i < npt; i++ ) {
    hk = c->ck[i] + c->tk[i];
    dhk = c->dck[i] + c->dtk[i];
    cx->dtk[i] = cx->ck[i] * hk
               + m->rho * (cx->dck[i] * hk + cx->ck[i] * dhk);
  }

  sphr_k2r(cx->sphr, cx->dtk, cx->dtr);

  for ( err = 0, i = 0; i < npt; i++ ) {
    /* dC = (1 + F) dY - dT = [(1 + F) Y' - 1] dT */
    getyr(cx->tr[i], &dydt, NULL, NULL, m);
    cx->res[i] = ((1 + cx->fr[i]) * dydt - 1) * cx->dtr[i] - cx->dcr[i];
    if ((x = FABS( cx->res[i] )) > err) {
      err = x;
    }
  }

  return err;
}



/* solve d/d(rho) functions with xi != 1 */
__inline static int iterxd_picard(cfs_t *c, cfs_t *cx,
    const model_t *m)
{
  int i, npt = m->npt, it, streak = 0;
  xdouble err, errp;

  err = errp = 1e9;
  for ( it = 0; it < m->itmax; it++ ) {
    err = stepxd_picard(c, cx, m);

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    if ( err < m->tol || streak >= m->mdiis->streakmax ) {
      break;
    }

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iterxd %d: err %g, damp %g\n",
              it, (double) err, (double) m->mdiis->damp);
    }

    errp = err;
    for ( i = 0; i < npt; i++ ) {
      cx->dcr[i] += m->mdiis->damp * cx->res[i];
    }
  }

  if ( err > m->tol ) {
    fprintf(stderr, "iterxd %d: failed to converge, err %g, streak %d\n",
            it, (double) err, streak);
    return -1;
  } else {
    return 0;
  }
}



/* do a step of direct (Picard) iteration
   for the d/d(xi) functions
   for xi = r, and the hard-sphere fluid */
static xdouble stepxD_hsr_picard(cfs_t *c, cfs_t *cx, const model_t *m)
{
  int i, j, npt = m->npt;
  xdouble err, yi, yj, yr, dydt, x;

  sphr_r2k(cx->sphr, cx->Dcr, cx->Dck);

  i = cx->bm;
  j = (i == 0) ? 1 : i - 1;
  yi = getyr(cx->tr[i], NULL, NULL, NULL, m);
  yj = getyr(cx->tr[j], NULL, NULL, NULL, m);
  if ( i > 0 ) {
    yr = (yi + yj) / 2;
  } else {
    yr = (3*yi - yj) / 2;
  }
  for ( i = 0; i < npt; i++ ) {
    cx->Dtk[i] = m->rho * (yr * cx->Dfk[i] + cx->Dck[i])
                 * (c->ck[i] + c->tk[i]);
  }

  sphr_k2r(cx->sphr, cx->Dtk, cx->Dtr);

  for ( err = 0, i = 0; i < npt; i++ ) {
    /* Dc(r) = -Dt(r) + (1 + f(r)) Dy(r) + Df(r) y(r)
     * for the hard-sphere, Df(r) is the negative of
     * a delta function dipped at cx->bm */
    yr = getyr(cx->tr[i], &dydt, NULL, NULL, m);
    cx->res[i] = (1 + cx->fr[i]) * dydt * cx->Dtr[i]
               - cx->Dtr[i] - cx->Dcr[i];
    if ( (x = FABS(cx->res[i])) > err ) {
      err = x;
    }
  }

  return err;
}



/* do a step of direct (Picard) iteration
   for the d/d(xi) functions */
static xdouble stepxD_picard(cfs_t *c, cfs_t *cx, const model_t *m)
{
  int i, npt = m->npt;
  xdouble err, yr, dydt, x;

  if ( m->hsr ) {
    return stepxD_hsr_picard(c, cx, m);
  }

  sphr_r2k(cx->sphr, cx->Dcr, cx->Dck);

  for ( i = 0; i < npt; i++ ) {
    cx->Dtk[i] = m->rho * cx->Dck[i] * (c->ck[i] + c->tk[i]);
  }

  sphr_k2r(cx->sphr, cx->Dtk, cx->Dtr);

  for ( err = 0, i = 0; i < npt; i++ ) {
    /* Dc(r) = -Dt(r) + (1 + f(r)) Dy(r) + Df(r) y(r) */
    yr = getyr(cx->tr[i], &dydt, NULL, NULL, m);
    cx->res[i] = (1 + cx->fr[i]) * dydt * cx->Dtr[i] + cx->Dfr[i] * yr
               - cx->Dtr[i] - cx->Dcr[i];
    if ( (x = FABS(cx->res[i])) > err ) {
      err = x;
    }
  }

  return err;
}



/* solve d/d(xi) functions, where xi is the charging parameter
 * which can be 1 or not 1 */
__inline static int iterxD_picard(cfs_t *c, cfs_t *cx,
    const model_t *m)
{
  int i, npt = m->npt, it, streak = 0;
  xdouble err, errp;

  err = errp = 1e9;
  for ( it = 0; it < m->itmax; it++ ) {
    err = stepxD_picard(c, cx, m);

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    if ( err < m->tol || streak >= m->mdiis->streakmax ) {
      break;
    }

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iterxD %d err %g\n",
              it, (double) err);
    }

    errp = err;
    for ( i = 0; i < npt; i++ ) {
      cx->Dcr[i] += m->mdiis->damp * cx->res[i];
    }
  }

  if ( err > m->tol ) {
    fprintf(stderr, "iterxD %d: failed to converge, err %g, streak %d\n",
            it, (double) err, streak);
    return -1;
  } else {
    return 0;
  }
}



/* do a step of direct (Picard) iteration
   for the d/d(lam) functions
   for lam = r, and the hard-sphere fluid */
static xdouble steplL_hsr_picard(cfs_t *cx, const model_t *m)
{
  int i, j, npt = m->npt;
  xdouble rho = m->rho;
  xdouble err, yi, yj, yr, dydt, x;

  sphr_r2k(cx->sphr, cx->Lcr, cx->Lck);

  i = cx->bm;
  j = (i == 0) ? 1 : i - 1;
  yi = getyr(cx->tr[i], NULL, NULL, NULL, m);
  yj = getyr(cx->tr[j], NULL, NULL, NULL, m);
  if ( i > 0 ) {
    yr = (yi + yj) / 2;
  } else {
    yr = (3*yi - yj) / 2;
  }
  for ( i = 0; i < npt; i++ ) {
    x = 1 - rho * cx->ck[i];
    cx->Ltk[i] = rho * cx->ck[i] * (yr * cx->Lfk[i] + cx->Lck[i])
                 * (1 + x) / x;
  }

  sphr_k2r(cx->sphr, cx->Ltk, cx->Ltr);

  for ( err = 0, i = 0; i < npt; i++ ) {
    /* Lc(r) = -Lt(r) + (1 + f(r)) Ly(r) + Lf(r) y(r)
     * for the hard-sphere, Lf(r) is the negative of
     * a delta function dipped at cx->bm */
    yr = getyr(cx->tr[i], &dydt, NULL, NULL, m);
    cx->res[i] = (1 + cx->fr[i]) * dydt * cx->Ltr[i]
               - cx->Ltr[i] - cx->Lcr[i];
    if ( (x = FABS(cx->res[i])) > err ) {
      err = x;
    }
  }

  return err;
}



/* do a step of direct (Picard) iteration
   for the d/d(lam) functions */
static xdouble steplL_picard(cfs_t *cx, const model_t *m)
{
  int i, npt = m->npt;
  xdouble rho = m->rho;
  xdouble err, yr, dydt, x;

  if ( m->hsr ) {
    return steplL_hsr_picard(cx, m);
  }

  sphr_r2k(cx->sphr, cx->Lcr, cx->Lck);

  for ( i = 0; i < npt; i++ ) {
    x = 1 - rho * cx->ck[i];
    cx->Ltk[i] = m->rho * cx->ck[i] * cx->Lck[i] * (1 + x) / (x * x);
  }

  sphr_k2r(cx->sphr, cx->Ltk, cx->Ltr);

  for ( err = 0, i = 0; i < npt; i++ ) {
    /* Lc(r) = -Lt(r) + [f(r) + 1] Ly(r) + Lf(r) y(r) */
    yr = getyr(cx->tr[i], &dydt, NULL, NULL, m);
    cx->res[i] = (1 + cx->fr[i]) * dydt * cx->Ltr[i] + cx->Lfr[i] * yr
               - cx->Ltr[i] - cx->Lcr[i];
    if ( (x = FABS(cx->res[i])) > err ) {
      err = x;
    }
  }

  return err;
}



/* solve d/d(lam) functions,
 * where lam is the global charging parameter
 * which can be 1 or not 1 */
__inline static int iterlL_picard(cfs_t *cx,
    const model_t *m)
{
  int i, npt = m->npt, it, streak = 0;
  xdouble err, errp;

  err = errp = 1e9;
  for ( it = 0; it < m->itmax; it++ ) {
    err = steplL_picard(cx, m);

    if ( err > errp ) {
      streak++;
    } else {
      streak = 0;
    }

    if ( err < m->tol || streak >= m->mdiis->streakmax ) {
      break;
    }

    if ( m->verbose >= 2 ) {
      fprintf(stderr, "iterlL %d err %g\n",
              it, (double) err);
    }

    errp = err;
    for ( i = 0; i < npt; i++ ) {
      cx->Lcr[i] += m->mdiis->damp * cx->res[i];
    }
  }

  if ( err > m->tol ) {
    fprintf(stderr, "iterlL %d: failed to converge, err %g, streak %d\n",
            it, (double) err, streak);
    return -1;
  } else {
    return 0;
  }
}



#endif /* PICARD_H__ */
