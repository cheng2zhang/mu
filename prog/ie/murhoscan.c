/* compute the chemical potential by explicitly
 * integrating over the density, rho */





#include "fftx.h"
#include "model.h" /* basic parameters */
#include "cfs.h" /* correlation functions and basic operations */
#include "solver.h" /* Picard and MDIIS solvers */
#include "ref.h" /* reference bmu values from file */
#include "sc.h" /* self-consistent integral equation */




enum {
  /* compressibility route */
  DBMUC, /* -Int c dr */
  BMUC,  /* integral of DBMUC, exact */
  BMUCG1,  /* approximate formula, with correction = h B */
  GAMC1,
  BMUCG2,  /* approximate formula, with correction = B */
  GAMC2,

  /* virial route */
  DBMUV, /* -Int r f' (y + rho dy) dr */
  BMUV,  /* integral of DBMUV */
  BMUVG1,
  GAMV1,
  BMUVG2,
  GAMV2,

  BMUHNC,

  /* reference or ideal gamma */
  GAMR1, /* Delta = h B */
  GAMR2, /* Delta = -B */
  BMUREF,

  IES,

  BMULAST
};



/* report the result of scanning over the density */
static int murhoscan_report(const char *fn, xdouble (*bmu)[BMULAST],
    const model_t *m)
{
  FILE *fp;
  int k;
  xdouble rho;

  /* open the report file */
  if ( fn == NULL || (fp = fopen(fn, "w")) == NULL ) {
    if ( fn != NULL ) {
      fprintf(stderr, "cannot write %s\n", fn);
    }
    return -1;
  }

  fprintf(fp, "# %d %g %g %d %g %s %s %s\n",
    m->nrho, (double) m->temp, (double) m->ies, m->npt, (double) m->rmax,
    pottypes[m->pottype], ietypes[m->ietype], sctypes[m->sctype]);

  for ( k = 0; k <= m->nrho; k++ ) {
    rho = m->drho * k;
    fprintf(fp, "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g\n",
        (double) rho,
        (double) bmu[k][DBMUC],   (double) bmu[k][BMUC],
        (double) bmu[k][BMUCG1],  (double) bmu[k][GAMC1],
        (double) bmu[k][BMUCG2],  (double) bmu[k][GAMC2],
        (double) bmu[k][DBMUV],   (double) bmu[k][BMUV],
        (double) bmu[k][BMUVG1],  (double) bmu[k][GAMV1],
        (double) bmu[k][BMUVG2],  (double) bmu[k][GAMV2],
        (double) bmu[k][BMUHNC],
        (double) bmu[k][GAMR1],   (double) bmu[k][GAMR2],
        (double) bmu[k][BMUREF],  (double) bmu[k][IES]);

    if ( rho > m->rhomax + m->drho / 2 ) {
      break;
    }
  }
  fprintf(stderr, "saved report to %s\n", fn);
  fclose(fp);
  return 0;
}



/* get d (beta * mu) / d xi, and related values for a certain xi */
static xdouble getdbmu(cfs_t *cf,
    const model_t *m, xdouble *out)
{
  sphr_t *sphr = cf->sphr;
  int i, npt = sphr->npt;
  xdouble rho = m->rho;
  xdouble yr, dydt, c, t, h, B;
  xdouble dc, dt, dh, dy, dB;
  xdouble sc = 0, sht = 0, sh = 0, sB = 0, shB = 0;
  xdouble sdc = 0, shdt = 0, stdh = 0, sdB = 0, shdB = 0, sBdh = 0;
  xdouble srdfy = 0, srdfdy = 0;
  xdouble den1, den2, num0, num;
  xdouble rDm1;

  for ( i = 0; i < npt; i++ ) {
    rDm1 = sphr->rDm1[i];

    c = cf->cr[i];
    t = cf->tr[i];
    h = c + t;
    dc = cf->dcr[i];
    dt = cf->dtr[i];
    dh = dc + dt;

    if ( cf->hasBr ) {
      yr = EXP(cf->tr[i] + cf->Br[i]);
      dy = yr * (cf->dtr[i] + cf->dBr[i]);
    } else {
      yr = getyr(t, &dydt, NULL, NULL, m);
      dy = dydt * dt;
    }

    if ( m->ietype == IETYPE_HNC ) {
      /* pseudo bridge functions */
      B = LOG(1 + t) - t;
      dB = (1/(1 + t) - 1) * dt;
    } else if ( m->ietype == IETYPE_BS ) {
      /* explicit bridge function and the rho derivative */
      B = cf->Br[i];
      dB = cf->dBr[i];
    } else {
      /* general case */
      B = LOG(yr) - t;
      dB = dy / yr - dt;
    }

    sc    += c * rDm1;
    sB    += B * rDm1;
    sh    += h * rDm1;
    sht   += h * t * rDm1;
    shB   += h * B * rDm1;

    sdc   += dc * rDm1;
    sdB   += dB * rDm1;
    stdh  += t * dh * rDm1;
    shdt  += h * dt * rDm1;
    shdB  += h * dB * rDm1;
    sBdh  += B * dh * rDm1;

    srdfy   += cf->rdfr[i] * yr * rDm1;
    srdfdy  += cf->rdfr[i] * dy * rDm1;
  }

  /* compressibility and virial routes */
  out[DBMUC] = -sc;
  out[DBMUV] = (srdfy + rho * srdfdy / 2) / m->dim;

  den1 = shB + rho * (sBdh + shdB) + 1e-300;
  den2 = -(sB + rho * sdB + 1e-300);
  num0 = sc - sB - sht/2;
  num  = num0 + rho * (sdc - sdB - stdh/2 - shdt/2);

  /* correction is h B */
  out[GAMC1]  = (num + out[DBMUC]) / den1;
  out[BMUCG1] = -rho * (num0 - out[GAMC1] * shB);
  out[GAMV1]  = (num + out[DBMUV]) / den1;
  out[BMUVG1] = -rho * (num0 - out[GAMV1] * shB);

  /* correction is -B */
  out[GAMC2]  = (num + out[DBMUC]) / den2;
  out[BMUCG2] = -rho * (num0 + out[GAMC2] * sB);
  out[GAMV2]  = (num + out[DBMUV]) / den2;
  out[BMUVG2] = -rho * (num0 + out[GAMV2] * sB);

  /* standard HNC equation */
  out[BMUHNC] = -rho * (sc - sht/2);

  /* compute the ideal gamma values, which
     make the approximate formula yield exact values */
  out[BMUREF] = m->bmuref;
  num = out[BMUREF] - (out[BMUHNC] + rho * sB);

  /* correction is h B */
  if ( FABS(shB) > 0 ) {
    out[GAMR1] = num / (rho * shB);
  } else {
    out[GAMR1] = (xdouble) 2 / 3;
  }

  /* correction is -B */
  if ( FABS(sB) > 0 ) {
    out[GAMR2] = num / (-rho * sB + XDBL_MIN);
  } else {
    out[GAMR2] = 0.5;
  }

  out[IES] = m->ies;

  return out[DBMUC];
}



static int murhoscan(model_t *m)
{
  xdouble (*bmu)[BMULAST];
  int k;
  sphr_t *sphr;
  cfs_t *c;
  ref_t *ref = NULL;

  /* initialize an object for the spherical Fourier transform */
  sphr = sphr_open(m->dim, m->npt, m->rmax, 0, m->ffttype);

  /* prepare correlation functions for xi = 1 */
  c = cfs_open(sphr);

  /* initialize correlation functions for xi = 1 */
  cfs_init(c, m);

  /* initialize bridge functions */
  if ( m->ietype == IETYPE_BS ) {
    if ( cfs_initbs(c, m) != 0 ) {
      return -1;
    }
  }

  /* load the reference values */
  if ( m->pottype == POTTYPE_HS ) {
    ref = ref_open(m->fnref);
  }

  xnew(bmu, m->nrho + 1);

  bmu[0][BMUC] = 0;
  bmu[0][BMUV] = 0;

  /* scan over rho */
  for ( k = 0; k <= m->nrho; k++ ) {
    m->rho = m->drho * k;

    if ( c->bs != NULL ) {
      brseries_combine(c->bs, m->rho, c->Br, c->dBr);
    }

    iter_sc(c, m);
    iterd(c, m);

    /* reference value */
    if ( ref != NULL ) {
      m->bmuref = ref_getbmu(ref, m->rho);
    } else {
      model_getref(m);
    }

    getdbmu(c, m, bmu[k]);

    /* integrate over the differential quantities */
    if ( k > 0 ) {
      bmu[k][BMUC] = bmu[k - 1][BMUC] + (bmu[k][DBMUC] + bmu[k - 1][DBMUC]) / 2 * m->drho;
      bmu[k][BMUV] = bmu[k - 1][BMUV] + (bmu[k][DBMUV] + bmu[k - 1][DBMUV]) / 2 * m->drho;
    }

    printf("rho %g, T %g, bmuc %g, %g, %g; bmuv %g, %g, %g; %g; ref %g; s %g\n",
      (double) m->rho, (double) m->temp,
      (double) bmu[k][BMUC], (double) bmu[k][BMUCG1], (double) bmu[k][BMUCG2],
      (double) bmu[k][BMUV], (double) bmu[k][BMUVG1], (double) bmu[k][BMUVG2],
      (double) bmu[k][BMUHNC], (double) bmu[k][BMUREF], (double) bmu[k][IES]);
  }

  /* report the scanning result */
  murhoscan_report(m->fnrep, bmu, m);

  sphr_close(sphr);
  cfs_close(c);
  ref_close(ref);

  free(bmu);

  return 0;
}



int main(int argc, char **argv)
{
  model_t m[1] = {0};

  model_doargs(m, argc, argv);
  model_getref(m);

  murhoscan(m);
  return 0;
}
