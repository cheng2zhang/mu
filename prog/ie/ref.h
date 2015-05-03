#ifndef REF_H__
#define REF_H__



/* handle reference values
   for the three-dimensional hard-sphere fluid
   An example file is Pmuhsvs12.dat   */



#include "util.h"



typedef struct {
  int n;
  double *rho;
  double *bP;
  double *Z;
  double *bmu;
} ref_t;



__inline static ref_t *ref_open(const char *fn)
{
  ref_t *ref;
  int i;
  FILE *fp;
  char buf[8192];

  if ( (fp = fopen(fn, "r")) == NULL ) {
    fprintf(stderr, "cannot open %s\n", fn);
    return NULL;
  }

  if ( fgets(buf, sizeof buf, fp) == NULL ||
       buf[0] != '#') {
    fprintf(stderr, "%s: no information line\n", fn);
    return NULL;
  }

  xnew(ref, 1);

  if ( 1 != sscanf(buf + 1, "%d", &ref->n) ) {
    fprintf(stderr, "cannot get the number of lines from %s\n", fn);
    free(ref);
    return NULL;
  }

  xnew(ref->rho, ref->n + 1);
  xnew(ref->bP,  ref->n + 1);
  xnew(ref->Z,   ref->n + 1);
  xnew(ref->bmu, ref->n + 1);

  for ( i = 0; i <= ref->n; i++ ) {
    if ( fgets(buf, sizeof buf, fp) == NULL ) {
      fprintf(stderr, "%s stop at i = %d\n", fn, i);
      break;
    }

    if ( buf[0] == '#' ) { /* a comment line */
      continue;
    }

    if ( 4 != sscanf(buf, "%lf %lf %lf %lf",
                     &ref->rho[i], &ref->bP[i], &ref->Z[i], &ref->bmu[i]) ) {
      fprintf(stderr, "%s: error on line %d\n%s", fn, i, buf);
      break;
    }
  }

  fclose(fp);

  return ref;
}



__inline static void ref_close(ref_t *ref)
{
  if ( ref == NULL ) return;
  free(ref->rho);
  free(ref->bP);
  free(ref->Z);
  free(ref->bmu);
  free(ref);
}



__inline static double ref_getbmu(ref_t * ref, xdouble rho)
{
  /* extrapolate on the right side,
     cut off on the left side */
  return interp((double) rho, ref->rho, ref->bmu,
                0, ref->n, 1, 0);
}



#endif /* REF_H__ */
