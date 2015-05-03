#ifndef UTIL_H__
#define UTIL_H__



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "xdouble.h"





#ifndef xnew
#define xnew(x, n) { \
  if ((x = calloc(n, sizeof(*(x)))) == NULL) { \
    fprintf(stderr, "no memory for %s x %d\n", #x, (int) (n)); \
    exit(1); } }
#endif

/* copy array */
#define cparr(x, y, n) { int i_; \
  for ( i_ = 0; i_ < n; i_++ ) x[i_] = y[i_]; }

#define newarr(x, n) { int i_; \
  xnew(x, n); for ( i_ = 0; i_ < n; i_++ ) x[i_] = 0; }

/* allocate a two-dimensional array */
#define newarr2d(x, m, n) { int j_; \
  x = malloc(sizeof(x[0]) * m); \
  for ( j_ = 0; j_ < m; j_++ ) newarr( x[j_], n ); }

#define delarr(x) free(x)

/* free a two-dimensional array */
#define delarr2d(x, m) { int j_; \
  for ( j_ = 0; j_ < m; j_++ ) delarr( x[j_] ); \
  free(x); x = NULL; }

/* copy array */
#define cparr2d(x, y, m, n) { int j_; \
  for ( j_ = 0; j_ < m; j_++ ) cparr(x[j_], y[j_], n); }






/* given the array (xi, yi), evaluate the value at x */
__inline static double interp(double x, double *xi, double *yi,
    int imin, int imax, int cutimin, int cutimax)
{
  int i;
  double gam;

  for ( i = imin; i < imax; i++ ) {
    if ( xi[i] > x ) {
      break;
    }
  }

  if ( i == imax ) { /* extrapolate */
    if ( cutimax ) {
      return 0;
    }
    i--;
  } else if ( i == imin ) { /* extrapolate */
    if ( cutimin ) {
      return 0;
    }
    i++;
  }

  /* linear interpolation */
  gam = (xi[i] - x) / (xi[i] - xi[i-1]);
  return gam * yi[i-1] + (1 - gam) * yi[i];
}



/* solve A x = b by L U decomposition
 * the matrix `a' will be destroyed
 * the vector `b' will be replaced by `x' on return */
__inline static int lusolve(xdouble *a, xdouble *b, int n, xdouble tiny)
{
  int i, j, k, ip = 0;
  xdouble x, max;

  for (i = 0; i < n; i++) {  /* normalize each equation */
    for (max = 0.0, j = 0; j < n; j++)
      if ((x = FABS(a[i*n + j])) > max)
        max = x;
    if ( max <= 0 ) return -1;
    for (x = 1./max, j = 0; j < n; j++)
      a[i*n + j] *= x;
    b[i] *= x;
  }

  /* step 1: A = L U, column by column */
  for (j = 0; j < n; j++) {
    /* matrix U */
    for (i = 0; i < j; i++) {
      for (x = a[i*n + j], k = 0; k < i; k++)
        x -= a[i*n + k] * a[k*n + j];
      a[i*n + j] = x;
    }

    /* matrix L, diagonal of L are 1 */
    max = 0.0;
    ip = j;
    for (i = j; i < n; i++) {
      for (x = a[i*n + j], k = 0; k < j; k++)
        x -= a[i*n + k] * a[k*n + j];
      a[i*n + j] = x;
      if ( FABS(x) > max ) {
        max = FABS(x);
        ip = i;
      }
    }

    if (j != ip) { /* swap the pivot row with the jth row */
      for (k = 0; k < n; k++)
        x = a[ip*n + k], a[ip*n + k] = a[j*n + k], a[j*n + k] = x;
      x = b[ip], b[ip] = b[j], b[j] = x;
    }
    if ( FABS(a[j*n + j]) < tiny )
      a[j*n + j] = tiny;
    /* divide by the pivot element, for the L matrix */
    if (j != n - 1)
      for (x = 1./a[j*n + j], i = j + 1; i < n; i++)
        a[i*n + j] *= x;
  }

  /* step 2: solve the equation L U x = b */
  for (i = 0; i < n; i++) { /* L y = b */
    x = b[i];
    for (j = 0; j < i; j++) x -= a[i*n + j] * b[j];
    b[i] = x;
  }
  for (i = n - 1; i >= 0; i--) { /* U x = y. */
    x = b[i];
    for (j = i + 1; j < n; j++) x -= a[i*n + j] * b[j];
    b[i] = x / a[i*n + i];
  }
  return 0;
}



/* String routines */



/* remove leading and trailing spaces */
__inline static char *strstrip(char *s)
{
  char *p, *q;

  /* remove trailing spaces */
  for ( p = s + strlen(s) - 1; isspace(*p); p-- )
    *p = '\0';

  /* remove leading spaces */
  for ( p = s; *p && isspace(*p); p++ )  ;
  if ( p != s )
    for ( q = s; (*q++ = *p++) != '\0'; ) ;
  return s;
}



#define strcmpfuzzy(s, t) strncmpfuzzy(s, t, INT_MAX)

/* comparison, ignoring cases, spaces and punctuations */
__inline static int strncmpfuzzy(const char *s, const char *t, int n)
{
  int is, it, i;
  const char cset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789()[]{}";

  for ( i = 0; i < n; s++, t++, i++ ) {
    while ( *s != '\0' && strchr(cset, *s) == NULL ) s++;
    while ( *t != '\0' && strchr(cset, *t) == NULL ) t++;
    is = tolower(*s);
    it = tolower(*t);
    if ( is != it ) return is - it;
    if ( *s == '\0' ) return 0;
  }
  return 0;
}



/* check if `s' starts with `t', using fuzzy comparison */
__inline static int strstartswith(const char *s, const char *t)
{
  return strncmpfuzzy(s, t, strlen(t)) == 0;
}



/* check if a string is a nonnegative integer */
__inline static int striscnum(const char *s)
{
  for ( ; *s; s++ ) if ( !isdigit(*s) ) return 0;
  return 1;
}




#endif /* UTIL_H__ */

