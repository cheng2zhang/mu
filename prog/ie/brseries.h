#ifndef BRSERIES_H__
#define BRSERIES_H__



/* handle series of the bridge function
   for the three-dimensional hard-sphere fluid
   An example file is crtrD3M8192ms.dat   */



#include "util.h"



typedef struct {
  int lmax;
  int npt;
  xdouble *ri;
  xdouble **Brs;
} brseries_t;



/* open an object for the series of the Bridge function */
__inline static brseries_t *brseries_open(int lmax, int npt, xdouble *ri)
{
  brseries_t *bs;
  int i, l;

  xnew(bs, 1);
  bs->lmax = lmax;
  bs->npt = npt;
  bs->ri = ri;
  xnew(bs->Brs, lmax + 1);

  for ( l = 0; l <= lmax; l++ ) {
    xnew(bs->Brs[l], npt);
  }

  for ( l = 0; l < 2; l++ ) {
    for ( i = 0; i < npt; i++ ) {
      bs->Brs[l][i] = 0;
    }
  }

  return bs;
}



/* close the brseries object */
__inline static void brseries_close(brseries_t *bs)
{
  int l;

  for ( l = 0; l <= bs->lmax; l++ ) {
    free(bs->Brs[l]);
  }
  free(bs);
}



/* load components of the bridge function from `fn` */
__inline static int brseries_load(brseries_t *bs, const char *fn)
{
  FILE *fp;
  char buf[8192];
  int l, i, id = 0, imin, nptb;
  double *r, cr, tr, *br, wr;

  if ( (fp = fopen(fn, "r")) == NULL ) {
    fprintf(stderr, "cannot open %s\n", fn);
    return -1;
  }

  if ( fgets(buf, sizeof buf, fp) == NULL ||
       buf[0] != '#') {
    fprintf(stderr, "%s: no information line\n", fn);
    return -1;
  }

  sscanf(buf + 1, "%d", &nptb);

  /* allocate space for the raw data */
  xnew(r, nptb);
  xnew(br, nptb);

  for ( l = 1; l <= bs->lmax; l++ ) {
    /* read the raw data */
    for ( i = 0; i < nptb; i++ ) {

      if ( fgets(buf, sizeof buf, fp) == NULL ) {
        if (i != 0) {
          fprintf(stderr, "%s: no line %d, l %d\n", fn, i, l);
        } else {
          fprintf(stderr, "%s stop at order l %d\n", fn, l - 1);
        }
        goto EXIT;
      }

      if ( 6 != sscanf(buf, "%lf %lf %lf %d %lf %lf",
                       &r[i], &cr, &tr, &id, &br[i], &wr) ||
          id != l ) {
        fprintf(stderr, "%s: error on line %d, l %d\n%s", fn, i, l, buf);
        goto EXIT;
      }
    }

    if ( fgets(buf, sizeof buf, fp) == NULL
      || !isspace(buf[0]) ) {
      fprintf(stderr, "error at the end of %s\n", fn);
      break;
    }

    /* no bridge function at l = 1, or n = 3 */
    if ( l == 1 ) {
      continue;
    }

    /* find imin, the Mayer sampling results for r < 0.1
     * are usually unreliable due to sparse data points
     * so they are unused */
    for ( imin = 0; imin < nptb; imin++ ) {
      if ( r[imin] > 0.1 ) {
        break;
      }
    }

    /* interpolation */
    for ( i = 0; i < bs->npt; i++ ) {
      bs->Brs[l][i] = interp((double) bs->ri[i], r,
        br, imin, nptb, 0, 1);
    }
  }
EXIT:
  free(r);
  free(br);
  fclose(fp);

  bs->lmax = l - 1;
  if ( bs->lmax > 0 ) {
    fprintf(stderr, "loaded the bridge function from %s\n", fn);
    return 0;
  } else {
    fprintf(stderr, "failed to load the bridge function from %s\n", fn);
    return -1;
  }
}



/* compute the bridge function at a certain density
   by combining the density components */
__inline static int brseries_combine(brseries_t *bs,
    xdouble rho, xdouble *Br, xdouble *dBr)
{
  int i, l, npt = bs->npt, lmax = bs->lmax;
  xdouble rp;

  for ( i = 0; i < npt; i++ ){
    dBr[i] = Br[i] = 0;
    rp = rho; /* rp = rho^l */
    for ( l = 2; l <= lmax; l++ ) {
      dBr[i] += bs->Brs[l][i] * l * rp;
      rp *= rho;
      Br[i] += bs->Brs[l][i] * rp;
    }
  }
  return 0;
}



#endif /* BRSERIES_H__ */
