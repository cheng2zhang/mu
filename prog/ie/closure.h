#ifndef CLOSURE_H__
#define CLOSURE_H__





#include "model.h"





/* compute the cavity distribution function */
static xdouble getyr(xdouble tr, xdouble *dy,
    xdouble *w, xdouble *dw, const model_t *m)
{
  int ietype = m->ietype;
  xdouble s = m->ies;
  xdouble u, z, y = 0;

  if ( ietype == IETYPE_PY ) { /* Percus-Yevick */
    if ( dy ) *dy = 1;
    if ( w ) *w = 0;
    if ( dw ) *dw = 0;
    y = 1 + tr;
  } else if ( ietype == IETYPE_HNC ) { /* hypernetted-chain */
    z = EXP(tr);
    if ( dy ) *dy = z;
    if ( w ) *w = 0;
    if ( dw ) *dw = 0;
    y = z;
  } else if ( ietype == IETYPE_SQR ) { /* quadratic */
    if ( dy ) *dy = 1 + s * tr;
    if ( w ) *w = .5 * tr * tr;
    if ( dw ) *dw = tr;
    y = 1 + tr + s * .5 * tr * tr;
  } else if ( ietype == IETYPE_IR ) { /* inverse Rowlinson */
    z = EXP(tr);
    if ( dy ) *dy = 1 + s * (z - 1);
    if ( w ) *w = z - 1 - tr;
    if ( dw ) *dw = z - 1;
    y = 1 + tr + s * (z - 1 - tr);
  } else if ( ietype == IETYPE_HC ) { /* Hutchinson-Conkie */
    /* y = (1 + s t)^(1/s); */
    u = 1 + s * tr;
    if (u < 1e-300) u = 1e-300;
    z = POW(u, 1.0/s);
    if ( dy ) *dy = z/u;
    if ( w ) *w = (-LOG(u) + 1 - 1/u) * z / (s * s);
    if ( dw ) *dw = (-LOG(u) + (1 - s) * (1 - 1/u)) * z / u / (s * s);
    y = z;
  } else {
    fprintf(stderr, "unknown closure type %d\n", ietype);
    exit(1);
  }

  /* make sure y is positive, for we may the logarithm */
  if ( y < XDBL_MIN ) {
    y = XDBL_MIN;
  }

  return y;
}



#endif /* CLOSURE_H__ */
