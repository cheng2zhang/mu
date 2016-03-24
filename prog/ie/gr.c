/* compute the radial distribution function */



#include "fftx.h"
#include "model.h"
#include "cfs.h"
#include "solver.h"



__inline static int cfs_save_ez(cfs_t *c, char *fn)
{
  int i, npt = c->sphr->npt;
  FILE *fp;

  if ((fp = fopen(fn, "w")) == NULL ) {
    fprintf(stderr, "cannot write %s\n", fn);
    return -1;
  }

  for ( i = 0; i < npt; i++ ) {
    xdouble gr = c->cr[i] + c->tr[i] + 1;
    fprintf(fp, "%8.6f %14.8f %14.8f %14.8f\n",
        (double) c->sphr->ri[i],
        (double) c->cr[i], (double) c->tr[i], (double) gr);
  }
  fclose(fp);

  return 0;
}



/* compute the coordination number
 * by integrating g(r) */
static xdouble getcoordnum(cfs_t *c)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;
  xdouble rm, gr, cnum;

  /* integrate g(r) dr until rm */
  cnum = 0;
  /* rm is the distance to the next nearest neighbor
   * in the close packing configuration */
  rm = SQRT( (sphr->dim + 1.) / (sphr->dim - 1.) );
  for ( i = 0; i < npt; i++ ) {
    gr = c->cr[i] + c->tr[i] + 1;
    if ( sphr->ri[i] >= rm ) {
      break;
    }
    if ( gr > 0 ) {
      cnum += sphr->rDm1[i] * gr;
    }
  }

  return cnum;
}



/* find the minimal value of gr */
static xdouble getgrmin(cfs_t *c)
{
  sphr_t *sphr = c->sphr;
  int i, npt = sphr->npt;
  xdouble gr = 1, grold = DBL_MAX;

  /* find the first nonvanishing bin */
  for ( i = 0; i < npt; i++ ) {
    gr = c->cr[i] + c->tr[i] + 1;
    if ( gr >= 0.9 ) {
      break;
    }
  }

  //fprintf(stderr, "starting: i %d, r %g, rDm1 %g\n", i, sphr->ri[i], sphr->rDm1[i]);
  for ( ; i < npt; i++ ) {
    gr = c->cr[i] + c->tr[i] + 1;
    if ( gr > grold ) {
      break;
    }
    grold = gr;
  }

  //fprintf(stderr, "ending: i %d, r %g, rDm1 %g\n", i, sphr->ri[i], sphr->rDm1[i]);
  return gr;
}



static int getgr(model_t *m)
{
  sphr_t *sphr;
  cfs_t *c;
  int k;
  xdouble cnum = 0, grmin = 1;

  /* initialize an object for Fourier transform
   * of a spherical function */
  sphr = sphr_open(m->dim, m->npt, m->rmax, 0, m->ffttype);

  /* prepare the structure for correlation functions */
  c = cfs_open(sphr);

  /* initialize the correlation functions for zero density */
  cfs_init(c, m);

  /* use a loop to increase the density gradually */
  for ( k = 0; k <= m->nrho; k++ ) {
    m->rho = m->rhomin + m->drho * k;

    /* iteratively solve c(r) and t(r) */
    iter(c, m);

    /* compute the coordination number */
    cnum = getcoordnum(c);

    /* compute the minimal value of g(r) */
    grmin = getgrmin(c);

    /* save the correlation functions */
    cfs_save_ez(c, m->fncrtr);

    fprintf(stderr, "rho %g, cnum %g, grmin %g, c(0) %g\n",
        (double) m->rho, (double) cnum, (double) grmin, (double) c->cr[0]);

    /* the integral equation fail to have meaning
     * when g(r) becomes negative */
    if ( grmin < 1e-3 ) {
      break;
    }
  }

  printf("rho %g, cnum %g\n", (double) m->rho, (double) cnum);

  return 0;
}



int main(int argc, char **argv)
{
  model_t m[1] = {0};

  model_doargs(m, argc, argv);

  if ( m->fncrtr == NULL ) {
    m->fncrtr = "crtr.dat";
  }

  getgr(m);

  return 0;
}
