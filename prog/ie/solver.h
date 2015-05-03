#ifndef SOLVER_H__
#define SOLVER_H__



#include "mdiis.h"



__inline static xdouble iter(cfs_t *c, const model_t *m)
{
  if ( m->solver == SOLVER_MDIIS ) {
    return iter_mdiis(c, m);
  } else {
    return iter_picard(c, m);
  }
}



__inline static xdouble iterd(cfs_t *c, const model_t *m)
{
  if ( m->solver == SOLVER_MDIIS ) {
    return iterd_mdiis(c, m);
  } else {
    return iterd_picard(c, m);
  }
}



__inline static xdouble iterx(cfs_t *c, cfs_t *cx, const model_t *m)
{
  if ( m->solver == SOLVER_MDIIS ) {
    return iterx_mdiis(c, cx, m);
  } else {
    return iterx_picard(c, cx, m);
  }
}



__inline static xdouble iterxd(cfs_t *c, cfs_t *cx, const model_t *m)
{
  if ( m->solver == SOLVER_MDIIS ) {
    return iterxd_mdiis(c, cx, m);
  } else {
    return iterxd_picard(c, cx, m);
  }
}



__inline static xdouble iterxD(cfs_t *c, cfs_t *cx, const model_t *m)
{
  if ( m->solver == SOLVER_MDIIS ) {
    return iterxD_mdiis(c, cx, m);
  } else {
    return iterxD_picard(c, cx, m);
  }
}



__inline static xdouble iterlL(cfs_t *cx, const model_t *m)
{
  if ( m->solver == SOLVER_MDIIS ) {
    return iterlL_mdiis(cx, m);
  } else {
    return iterlL_picard(cx, m);
  }
}




#endif /* SOLVER_H__ */

