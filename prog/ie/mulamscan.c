/* compute the chemical potential by explicitly
 * integrating over the parameter, lambda */





#include "sc.h"





enum {
  DBMUFY, /* -rho Int Df [y + (rho/2) dy/drho] dr */
  BMUFY,  /* integral of DBMUFY */
  BMUEMP, /* empirial formula */
  GAM1,   /* gam1 = Int B Dh  dr / Int (B Dh + h DB) dr */
  BMUG1,  /* -rho Int (c - h t / 2 - gam1 h B) dr */
  GAM2,   /* gam2 = Int B Dh  dr / Int DB dr */
  BMUG2,  /* -rho Int (c - h t / 2 + gam2 B) dr */
  DCFFY,  /* DZ = D(beta P / rho) = -rho Int Df [y + rho dy/drho]/2 dr */
  CFFY,   /* compressibility factor, Z */
  BMULAST
};



/* report the result of scanning over the charging parameter */
static int mulamscan_report(const char *fn,
    xdouble (*bmu)[BMULAST], const model_t *m)
{
  FILE *fp;
  int k, nlam = m->nlam;
  xdouble lam;

  if ( fn == NULL ) {
    return -1;
  }

  /* open the report file */
  if ( (fp = fopen(fn, "w")) == NULL ) {
    fprintf(stderr, "cannot write %s\n", fn);
    return -1;
  }

  for ( k = 0; k <= nlam; k++ ) {
    lam = (xdouble) k / nlam;
    fprintf(fp, "%g %g %g %g %g %g %g %g\n",
        (double) lam,
        (double) bmu[k][DBMUFY],  (double) bmu[k][BMUFY],
        (double) bmu[k][BMUEMP], /*  4 items */
        (double) bmu[k][BMUG1],   (double) bmu[k][GAM1], /* 6 items */
        (double) bmu[k][BMUG2],   (double) bmu[k][GAM2] /* 8 items */
	  );
  }
  fprintf(stderr, "saved report to %s\n", fn);
  fclose(fp);
  return 0;
}



/* save the correlation functions */
static int savecrtr(cfs_t *cf, char *fn0, xdouble lam)
{
  char fn[FILENAME_MAX], stem[FILENAME_MAX], *p;
  int i, n, npt = cf->sphr->npt;
  FILE *fp;

  if ( fn0 == NULL ) {
    return -1;
  }

  /* get the stem part of the file name */
  p = strrchr(fn0, '.');
  if ( p == NULL ) {
    n = strlen(fn0);
    p = ".dat";
  } else {
    n = p - fn0;
  }
  strncpy(stem, fn0, n);
  stem[n] = '\0';

  /* construct the target file name */
  sprintf(fn, "%slam%g%s",
      stem, (double) lam, p);

  /* write the file */
  if ( (fp = fopen(fn, "w")) == NULL ) {
    fprintf(stderr, "cannot write %s\n", fn);
    return -1;
  }

  for ( i = 0; i < npt; i++ ) {
    fprintf(fp, "%g %g %g %g %g %g %g %g %g\n",
        (double) cf->sphr->ri[i],
        (double) cf->cr[i], (double) cf->tr[i],
        (double) cf->fr[i],
        (double) cf->sphr->ki[i],
        (double) cf->ck[i], (double) cf->tk[i],
        (double) cf->Dfr[i], (double) cf->Dfk[i]);
  }

  /* close the file */
  fclose(fp);

  return 0;
}



/* get d (beta * mu) / d lam */
static xdouble getLbmu(cfs_t *cf, const model_t *m,
    xdouble lam, xdouble *out)
{
  sphr_t *sphr = cf->sphr;
  int i, npt = sphr->npt;
  xdouble rho = m->rho;
  xdouble yr, dydt, c, t, h, B;
  xdouble dt, dy;
  xdouble Lf, Lc, Lt, Lh, LB;
  xdouble sc = 0, sB = 0, sht = 0, shB = 0, sLB = 0, shLB = 0, sBLh = 0;
  //xdouble sLc = 0, sLt = 0;
  xdouble shLt = 0, stLh = 0, sLfy = 0, sLfdy = 0, sLfyt = 0, sLfyB = 0;
  xdouble num, den, rDm1;

  for ( i = 0; i < npt; i++ ) {
    rDm1 = sphr->rDm1[i];

    Lf = cf->Lfr[i];
    c = cf->cr[i];
    t = cf->tr[i];
    h = c + t;
    dt = cf->dtr[i];

    Lc = cf->Lcr[i];
    Lt = cf->Ltr[i];
    Lh = Lc + Lt;

    yr = getyr(t, &dydt, NULL, NULL, m);
    if ( FABS(yr) < XDBL_MIN ) { /* yr must be positive to use log */
      yr = XDBL_MIN;
    }
    dy = dydt * dt;

    if ( m->ietype == IETYPE_HNC ) {
      B = LOG(1 + t) - t;
      LB = (1/(1 + t) - 1) * Lt;
    } else {
      B = LOG(yr) - t;
      LB = (dydt / yr - 1) * Lt;
    }

    sc += c * rDm1;
    sB += B * rDm1;
    sht += h * t * rDm1;
    shB += h * B * rDm1;
    sLB += LB * rDm1;
    shLt += h * Lt * rDm1;
    stLh += t * Lh * rDm1;
    shLB += h * LB * rDm1;
    sBLh += B * Lh * rDm1;
    sLfy += Lf * yr * rDm1;
    sLfdy += Lf * dy * rDm1;

    sLfyt += Lf * yr * t * rDm1;
    sLfyB += Lf * yr * B * rDm1;

    //sLc += Lc * rDm1;
    //sLt += Lt * rDm1;
  }

  if ( m->hsr ) { /* hard-sphere lam-r */
    //sLc += sLfy;
    sBLh += sLfyB;
    stLh += sLfyt;
  }

  num = shLB + (shLt - stLh)/2 - rho*sLfdy/2;
  //num1 = -(sLfy + rho*sLfdy/2) + sLc-sLB-(shLt+stLh)/2;
  den = sc - sB - sht/2;

  if ( FABS(lam) <= 0 ) {
    out[DBMUFY] = 0;
    out[BMUEMP] = 0;
    out[DCFFY] = 0;
  } else {
    out[DBMUFY] = -rho * (sLfy + rho/2*sLfdy);
    out[BMUEMP] = -rho * (den - shB*2/3);
    out[DCFFY] = -rho * (sLfy + rho*sLfdy)/2;
  }

  /* correction function is h B */
  out[GAM1] = num / (shLB + sBLh);
  out[BMUG1] = -rho * (den - shB * out[GAM1]);

  /* correction function is -B */
  out[GAM2] = num / (-sLB);
  out[BMUG2] = -rho * (den + sB * out[GAM2]);

  return out[DBMUFY];
}



/* solve correlation functions for the lam-c route */
static void lamc_solve(cfs_t *c, cfs_t *cx,
    xdouble lam, const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;
  xdouble rho = m->rho, rlck, x;
  xdouble cr, tr, hr, ck, yr, dydt;
  xdouble Lcr, Ltr, Lhr;

  for ( i = 0; i < npt; i++ ) {
    cr = c->cr[i];
    tr = c->tr[i];
    ck = c->ck[i];

    rlck = rho * lam * ck;
    x = 1 - rlck;

    cx->cr[i] = lam * cr;
    cx->ck[i] = lam * ck;
    cx->tk[i] = lam * lam * rho * ck * ck / x;

    cx->Lcr[i] = cr;
    cx->Lck[i] = ck;
    cx->Ltk[i] = lam * rho * ck * ck * (1 + x) / (x * x);
  }

  sphr_k2r(sphr, cx->tk,  cx->tr);
  sphr_k2r(sphr, cx->Ltk, cx->Ltr);

  for ( i = 0; i < npt; i++ ) {
    cr = cx->cr[i];
    tr = cx->tr[i];
    hr = cr + tr;
    Lcr = cx->Lcr[i];
    Ltr = cx->Ltr[i];
    Lhr = Lcr + Ltr;
    yr = getyr(tr, &dydt, NULL, NULL, m);
    cx->Br[i] = LOG(yr) - tr;
    cx->LBr[i] = (dydt / yr - 1) * Ltr;
    cx->fr[i] = (1 + hr) / yr - 1;
    cx->Lfr[i] = Lhr / yr - (1 + hr) * dydt * Ltr / (yr * yr);
  }
  sphr_r2k(sphr, cx->fr,  cx->fk);
  sphr_r2k(sphr, cx->Lfr, cx->Lfk);
}



/* solve correlation functions for the lam-h route */
static void lamh_solve(cfs_t *c, cfs_t *cx,
    xdouble lam, const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;
  xdouble rho = m->rho, rlhk;
  xdouble cr, tr, hr, ck, tk, hk, yr, dydt;
  xdouble Lcr, Ltr, Lhr;

  for ( i = 0; i < npt; i++ ) {
    ck = c->ck[i];
    tk = c->tk[i];
    hk = ck + tk;

    rlhk = rho * lam * hk;

    cx->tk[i] = lam * lam * rho * hk * hk / (1 + rlhk);
    cx->ck[i] = lam * hk - cx->tk[i];

    cx->Ltk[i] = lam * rho * hk * hk * (2 + rlhk)
               / ((1 + rlhk) * (1 + rlhk));
    cx->Lck[i] = hk - cx->Ltk[i];
  }

  sphr_k2r(sphr, cx->ck,  cx->cr);
  sphr_k2r(sphr, cx->Lck, cx->Lcr);
  sphr_k2r(sphr, cx->tk,  cx->tr);
  sphr_k2r(sphr, cx->Ltk, cx->Ltr);

  for ( i = 0; i < npt; i++ ) {
    cr = cx->cr[i];
    tr = cx->tr[i];
    hr = cr + tr;
    Lcr = cx->Lcr[i];
    Ltr = cx->Ltr[i];
    Lhr = Lcr + Ltr;
    yr = getyr(tr, &dydt, NULL, NULL, m);
    cx->Br[i] = LOG(yr) - tr;
    cx->LBr[i] = (dydt / yr - 1) * Ltr;
    cx->fr[i] = (1 + hr) / yr - 1;
    cx->Lfr[i] = Lhr / yr - (1 + hr) * dydt * Ltr / (yr * yr);
  }
  sphr_r2k(sphr, cx->fr,  cx->fk);
  sphr_r2k(sphr, cx->Lfr, cx->Lfk);
}



/* solve correlation functions for the lam-t route */
static void lamt_solve(cfs_t *c, cfs_t *cx,
    xdouble lam, const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;
  xdouble rho = m->rho;
  xdouble cr, tr, hr, tk, clk, tlk, yr, dydt;
  xdouble Lcr, Ltr, Lhr, x;

  for ( i = 0; i < npt; i++ ) {
    tk = c->tk[i];

    tlk = tk * lam;
    x = tlk * tlk + 4 * tlk / rho;
    if ( x < 0 ) {
      x = 0;
    }
    x = -SQRT(x);
    clk = (x - tlk)/2;

    cx->tk[i] = tlk;
    cx->ck[i] = clk;

    cx->Ltk[i] = tk;
    if ( FABS(lam) < 1e-8 ) {
      cx->Lck[i] = -tk / 2;
    } else {
      cx->Lck[i] = ((tlk + 2/rho) / x - 1) * tk / 2;
    }
  }

  sphr_k2r(sphr, cx->ck,  cx->cr);
  sphr_k2r(sphr, cx->Lck, cx->Lcr);
  sphr_k2r(sphr, cx->tk,  cx->tr);
  sphr_k2r(sphr, cx->Ltk, cx->Ltr);

  for ( i = 0; i < npt; i++ ) {
    cr = cx->cr[i];
    tr = cx->tr[i];
    hr = cr + tr;
    Lcr = cx->Lcr[i];
    Ltr = cx->Ltr[i];
    Lhr = Lcr + Ltr;
    yr = getyr(tr, &dydt, NULL, NULL, m);
    cx->Br[i] = LOG(yr) - tr;
    cx->LBr[i] = (dydt / yr - 1) * Ltr;
    cx->fr[i] = (1 + hr) / yr - 1;
    cx->Lfr[i] = Lhr / yr - (1 + hr) * dydt * Ltr / (yr * yr);
  }
  sphr_r2k(sphr, cx->fr,  cx->fk);
  sphr_r2k(sphr, cx->Lfr, cx->Lfk);
}



static int mulamscan(model_t *m)
{
  xdouble lam, (*bmu)[BMULAST];
  int k, nlam = m->nlam;
  sphr_t *sphr;
  cfs_t *c, *cx;

  /* initialize an object for the spherical Fourier transform */
  sphr = sphr_open(m->dim, m->npt, m->rmax, 0, m->ffttype);

  /* prepare correlation functions for lam = 1 */
  c = cfs_open(sphr);

  /* prepare correlation functions for lam != 1 */
  cx = cfs_open(sphr);

  /* initialize correlation functions for lam = 1 */
  cfs_init(c, m);

  /* Lfr */
  cfs_initLfr(c, m);

  /* 1. solve the case of lam = 1 */
  iter_sc(c, m);
  iterd(c, m);

  xnew(bmu, m->nlam + 1);

  /* 2. scan over xi */
  for ( k = m->nlam; k >= 0; k-- ) {
    lam = (xdouble) k / m->nlam;

    /* 2.1 initialize correlation functions for lam != 1
       preserve the old c(r) if k < m->nlam */
    cfs_init_lam(c, cx, lam, m, k < m->nlam);

    /* 2.2 solve the case of xi = 1 - delta  */
    if ( m->lamtype == LAMTYPE_C ) {
      lamc_solve(c, cx, lam, m);
      iterd(cx, m);
    } else if ( m->lamtype == LAMTYPE_H ) {
      lamh_solve(c, cx, lam, m);
      iterd(cx, m);
    } else if ( m->lamtype == LAMTYPE_T ) {
      lamt_solve(c, cx, lam, m);
      iterd(cx, m);
    } else if ( m->lamtype == LAMTYPE_U
             || m->lamtype == LAMTYPE_F
             || m->lamtype == LAMTYPE_R ) {
      iter(cx, m);
      iterd(cx, m);
      iterlL(cx, m);
    } else {
      fprintf(stderr, "not implemented\n");
      exit(1);
    }

    savecrtr(cx, m->fncrtr, lam);

    getLbmu(cx, m, lam, bmu[k]);

    printf("rho %g, lam %g, Lbmu %g, bm %d\n",
        (double) m->rho, (double) lam,
        (double) bmu[k][DBMUFY], cx->bm);
  }

  /* integrate over the differential quantities */
  bmu[0][BMUFY] = 0;
  bmu[0][CFFY] = 1;
  for ( k = 1; k <= nlam; k++ ) {
    bmu[k][BMUFY] = bmu[k - 1][BMUFY] + (bmu[k][DBMUFY] + bmu[k - 1][DBMUFY]) / 2 / nlam;
    bmu[k][CFFY]  = bmu[k - 1][CFFY]  + (bmu[k][DCFFY]  + bmu[k - 1][DCFFY] ) / 2 / nlam;
  }

  printf("bmu %g; emp %g; hB %g %g; B %g %g; bmuref %g, Z %g, Zref %g\n",
    (double) bmu[nlam][BMUFY], (double) bmu[nlam][BMUEMP],
    (double) bmu[nlam][BMUG1], (double) bmu[nlam][GAM1],
    (double) bmu[nlam][BMUG2], (double) bmu[nlam][GAM2],
    (double) m->bmuref,
    (double) bmu[nlam][CFFY], (double) m->cfref);

  /* report the scanning result */
  mulamscan_report(m->fnrep, bmu, m);

  sphr_close(sphr);
  cfs_close(c);
  cfs_close(cx);
  free(bmu);

  return 0;
}



int main(int argc, char **argv)
{
  model_t m[1] = {0};

  model_doargs(m, argc, argv);
  model_getref(m);

  mulamscan(m);
  return 0;
}
