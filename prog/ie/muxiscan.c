/* compute the chemical potential by explicitly
 * integrating over the charging parameter xi */




#include "sc.h"





enum {
  DBMUFY, /* -rho Int Df y dr */
  BMUFY,  /* integral of DBMUFY */
  BMUFYB, /* a variant of BMUFY with an exact correction */
  DBMU1,  /* -rho Int (Dc - DB - h Dt - h DB) dr */
  BMU1,   /* integral of DBMU1 */
  BMU0,   /* -rho Int (c - h t / 2) dr */
  BMUEMP, /* empirial formula */
  HDB,    /* rho Int h DB dr */
  IHDB,   /* integral of HDB */
  BDH,    /* rho Int B Dh dr */
  IBDH,   /* integral of BDH */
  GAM1,   /* gam1 = Int B Dh  dr / Int (B Dh + h DB) dr */
  BMUG1,  /* -rho Int (c - h t / 2 - gam1 h B) dr */
  GAM2,   /* gam2 = Int B Dh  dr / Int DB dr */
  BMUG2,  /* -rho Int (c - h t / 2 + gam2 B) dr */
  HB,
  DBR,
  BR,
  DH,
  H,
  IDH,
  BMULAST
};



/* report the result of scanning over the charging parameter */
static int muxiscan_report(const char *fn,
    xdouble (*bmu)[BMULAST], const model_t *m)
{
  FILE *fp;
  int k, nxi = m->nxi;
  xdouble xi;

  if ( fn == NULL ) {
    return -1;
  }

  /* open the report file */
  if ( (fp = fopen(fn, "w")) == NULL ) {
    fprintf(stderr, "cannot write %s\n", fn);
    return -1;
  }

  for ( k = 0; k <= nxi; k++ ) {
    xi = (xdouble) k / nxi;
    fprintf(fp, "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g\n",
        (double) xi,
        (double) bmu[k][DBMUFY],  (double) bmu[k][BMUFY], (double) bmu[k][BMUFYB],
        (double) bmu[k][DBMU1],   (double) bmu[k][BMU1],
        (double) bmu[k][BMU0],    (double) bmu[k][BMUEMP], /*  8 items */
        (double) bmu[k][BMUG1],   (double) bmu[k][GAM1], /* 10 items */
        (double) bmu[k][BMUG2],   (double) bmu[k][GAM2], /* 12 items */
        (double) bmu[k][HDB],     (double) bmu[k][IHDB], /* 14 items */
        (double) bmu[k][BDH],     (double) bmu[k][IBDH], /* 16 items */
        (double) bmu[k][DBR],     (double) bmu[k][BR],
        (double) bmu[k][DH],      (double) bmu[k][H],  /* 20 items */
        (double) bmu[k][IDH],     (double) bmu[k][HB]);
  }
  fprintf(stderr, "saved report to %s\n", fn);
  fclose(fp);
  return 0;
}



/* save the correlation functions */
static int savecrtr(cfs_t *cf, char *fn0, xdouble xi)
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
  sprintf(fn, "%sxi%g%s",
      stem, (double) xi, p);

  /* write the file */
  if ( (fp = fopen(fn, "w")) == NULL ) {
    fprintf(stderr, "cannot write %s\n", fn);
    return -1;
  }

  for ( i = 0; i < npt; i++ ) {
    fprintf(fp, "%g %g %g %g %g %g %g %g\n",
        (double) cf->sphr->ri[i],
        (double) cf->cr[i], (double) cf->tr[i],
        (double) cf->sphr->ki[i],
        (double) cf->ck[i], (double) cf->tk[i],
        (double) cf->Dfr[i], (double) cf->Dfk[i]);
  }

  /* close the file */
  fclose(fp);

  return 0;
}



/* get d (beta * mu) / d xi */
static xdouble getDbmu(cfs_t *cf,
    const model_t *m, xdouble *out)
{
  sphr_t *sphr = cf->sphr;
  int i, npt = sphr->npt;
  xdouble rho = m->rho;
  xdouble yr, dydt, c, t, h, B, Df, Dc, Dt, Dh, DB;
  xdouble sDfy = 0, sDfyB = 0, sc = 0, sht = 0, sDc = 0, shDt = 0;
  xdouble sh = 0, sDh = 0;
  xdouble sB = 0, sDB = 0, shB = 0, shDB = 0, sBDh = 0;
  xdouble rDm1;

  for ( i = 0; i < npt; i++ ) {
    rDm1 = sphr->rDm1[i];

    Df = cf->Dfr[i];
    c = cf->cr[i];
    t = cf->tr[i];
    h = c + t;
    Dc = cf->Dcr[i];
    Dt = cf->Dtr[i];
    Dh = Dc + Dt;

    yr = getyr(t, &dydt, NULL, NULL, m);
    if ( FABS(yr) < XDBL_MIN ) { /* yr must be positive to use log */
      yr = XDBL_MIN;
    }
    B = LOG(yr) - t;
    DB = (dydt / yr - 1) * Dt;

    sc += c * rDm1;
    sB += B * rDm1;
    sh += h * rDm1;
    sht += h * t * rDm1;
    shB += h * B * rDm1;
    sDc += Dc * rDm1;
    sDB += DB * rDm1;
    sDh += Dh * rDm1;
    shDt += h * Dt * rDm1;
    shDB += h * DB * rDm1;
    sBDh += B * Dh * rDm1;
    sDfy += Df * yr * rDm1;
    sDfyB += Df * yr * B * rDm1;
  }

  if ( m->hsr ) {
    sDc += sDfy;
    sDh += sDfy;
    sBDh += sDfyB;
  }

  out[DBMUFY] = -rho * sDfy;

  out[DBMU1] = -rho * (sDc - sDB - shDt - shDB);
  out[BMU0] = -rho * (sc - sht/2);
  out[BMUEMP] = -rho * (sc - sB - sht/2 - shB*2/3);

  /* correction function is h B */
  out[GAM1] = shDB / (shDB + sBDh);
  out[BMUG1] = -rho * (sc - sB - sht/2 - shB * out[GAM1]);

  /* correction function is -B */
  out[GAM2] = shDB / (-sDB);
  out[BMUG2] = -rho * (sc - sB - sht/2 + sB * out[GAM2]);

  out[HDB] = rho * shDB;
  out[BDH] = rho * sBDh;
  out[HB] = rho * shB;
  out[DBR] = rho * sDB;
  out[BR] = rho * sB;
  out[DH] = rho * sDh;
  out[H] = rho * sh;
  return out[DBMUFY];
}



/* solve correlation functions for the xi-t route */
static void xit_solve(cfs_t *c, cfs_t *cx,
    xdouble xi, const model_t *m)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;
  xdouble cr, tr, hr, ck, tk, yr, dydt;

  for ( i = 0; i < npt; i++ ) {
    cr = c->cr[i];
    tr = c->tr[i];
    hr = cr + tr;
    ck = c->ck[i];
    tk = c->tk[i];

    cx->cr[i] = xi * cr;
    cx->tr[i] = xi * tr;
    cx->ck[i] = xi * ck;
    cx->tk[i] = xi * tk;

    cx->Dcr[i] = cr;
    cx->Dtr[i] = tr;
    cx->Dck[i] = ck;
    cx->Dtk[i] = tk;

    yr = getyr(xi * tr, &dydt, NULL, NULL, m);
    cx->Br[i] = LOG(yr) - xi * tr;
    cx->DBr[i] = dydt * tr / yr - tr;
    cx->fr[i] = (1 + xi * hr) / yr - 1;
    cx->Dfr[i] = hr / yr - (1 + xi * hr) * dydt * tr/(yr*yr);
  }
  sphr_r2k(sphr, cx->fr, cx->fk);
  sphr_r2k(sphr, cx->Dfr, cx->Dfk);
}



static int muxiscan(model_t *m)
{
  xdouble xi, (*bmu)[BMULAST];
  int k, nxi = m->nxi;
  sphr_t *sphr;
  cfs_t *c, *cx;

  /* initialize an object for the spherical Fourier transform */
  sphr = sphr_open(m->dim, m->npt, m->rmax, 0, m->ffttype);

  /* prepare correlation functions for xi = 1 */
  c = cfs_open(sphr);

  /* prepare correlation functions for xi != 1 */
  cx = cfs_open(sphr);

  /* initialize correlation functions for xi = 1 */
  cfs_init(c, m);

  /* 1. solve the case of xi = 1 */
  iter_sc(c, m);

  xnew(bmu, m->nxi + 1);

  /* 2. scan over xi */
  for ( k = m->nxi; k >= 0; k-- ) {
    xi = (xdouble) k / m->nxi;

    /* 2.1 initialize correlation functions for xi = 1 - delta
       preserve the old c(r) if k < m->nxi */
    cfs_init_xi(c, cx, xi, m, k < m->nxi);

    /* 2.2 solve the case of xi = 1 - delta  */
    if ( m->xitype == XITYPE_T ) {
      xit_solve(c, cx, xi, m);
    } else {
      iterx(c, cx, m);
      iterxD(c, cx, m);
    }

    savecrtr(cx, m->fncrtr, xi);

    /* 2.3 compute quantities */
    getDbmu(cx, m, bmu[k]);

    printf("rho %g, xi %g, Dbmu %g, %g, bm %d\n",
        (double) m->rho, (double) xi,
        (double) bmu[k][DBMUFY], (double) bmu[k][DBMU1], cx->bm);
  }

  /* integrate over the differential quantities */
  bmu[0][BMUFY] = 0;
  bmu[0][BMU1]  = 0;
  bmu[0][IHDB]  = 0;
  bmu[0][IBDH]  = 0;
  bmu[0][IDH]   = 0;
  for ( k = 1; k <= nxi; k++ ) {
    bmu[k][BMUFY] = bmu[k - 1][BMUFY] + (bmu[k][DBMUFY] + bmu[k - 1][DBMUFY]) / 2 / nxi;
    bmu[k][BMU1]  = bmu[k - 1][BMU1]  + (bmu[k][DBMU1]  + bmu[k - 1][DBMU1] ) / 2 / nxi;
    bmu[k][IHDB]  = bmu[k - 1][IHDB]  + (bmu[k][HDB]    + bmu[k - 1][HDB]   ) / 2 / nxi;
    bmu[k][IBDH]  = bmu[k - 1][IBDH]  + (bmu[k][BDH]    + bmu[k - 1][BDH]   ) / 2 / nxi;
    bmu[k][IDH]   = bmu[k - 1][IDH]   + (bmu[k][DH]     + bmu[k - 1][DH]    ) / 2 / nxi;
  }

  /* if the system is hard-sphere and the charging parameter, xi, is
     proportional to the hard-core radius, the integral of xi over (0, 1/2)
     can be done exactly without resorting to the integral equations */
  if ( m->hsr ) {
    for ( k = 0; k <= nxi/2; k++ ) {
      bmu[k][BMUFYB] = -LOG(1 - m->rho*4*PI/3*POW((xdouble) k/nxi, 3) );
    }
    for ( ; k <= nxi; k++ ) {
      bmu[k][BMUFYB] = bmu[k][BMUFY] - bmu[nxi/2][BMUFY]
                     + bmu[nxi/2][BMUFYB];
    }
  } else {
    for ( k = 0; k <= nxi; k++ ) {
      bmu[k][BMUFYB] = bmu[k][BMUFY];
    }
  }

  printf("bmu %g, %g, %g; emp %g; hB %g %g; B %g %g\n",
    (double) bmu[nxi][BMUFY], (double) bmu[nxi][BMUFYB], (double) bmu[nxi][BMU1],
    (double) bmu[nxi][BMUEMP],
    (double) bmu[nxi][BMUG1], (double) bmu[nxi][GAM1],
    (double) bmu[nxi][BMUG2], (double) bmu[nxi][GAM2]);

  /* report the scanning result */
  muxiscan_report(m->fnrep, bmu, m);

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

  muxiscan(m);
  return 0;
}
