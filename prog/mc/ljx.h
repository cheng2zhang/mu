#ifndef LJX_H__
#define LJX_H__



INLINE real lj_widom(lj_t *lj, real beta)
{
  real du, bu;

  du = lj_duinsert(lj, NULL);
  bu = beta * du;
  return (bu > 700) ? 0 : exp(-bu);
}



/* randomly displace particle i with random amplitude */
INLINE int lj_randmv3dx(lj_t *lj, real *xi, real amp)
{
  int i, d;

  /* skip particles 1 and 2 */
  i = (int)(rnd0() * (lj->n - 2)) + 2;
  amp /= lj->l;
  rv3_copy(xi, lj->x + i*3);
  for (d = 0; d < 3; d++) /* displacement */
    xi[d] += (real)(amp * (2.*rnd0() - 1.));
  return i;
}



/* Metropolis moves */
INLINE int lj_metrolj3dx(lj_t *lj, real amp, real bet)
{
  int i;
  real xi[3], du = 0.f, dvir = 0.f;

  i = lj_randmv3dx(lj, xi, amp);
  du = lj_depotlj3d(lj, i, xi, &dvir);
  if (metroacc1(du, bet)) {
    lj_commitlj3d(lj, i, xi, du, dvir);
    return 1;
  }
  return 0;
}



/* compute energy data for a 3D Lennard-Jones pair */
INLINE int lj_pairlj3dx(real *xi, real *xj, real *dx,
    real l, real rc2, real *dr2, real *u, real *vir)
{
  real invr2, invr6;
  *dr2 = lj_pbcdist2_3d(dx, xi, xj, l);
  if (*dr2 < rc2) {
    invr2 = 1.0f / *dr2;
    invr6 = invr2 * invr2 * invr2;
    *vir = invr6 * (48.f * invr6 - 24.f); /* f.r */
    *u  = 4.f * invr6 * (invr6 - 1.f);
    return 1;
  } else return 0;
}



/* compute the excess mean force between 0 and 1 */
INLINE real lj_getrf(lj_t *lj)
{
  int j;
  real dr2, u, vir, dr01, dr01sqr, rf;
  real *x0 = lj->x, *x1 = lj->x + 3;
  rv3_t dx, dx01;

  dr01sqr = lj_pbcdist2_3d(dx01, x0, x1, lj->l);
  dr01 = (real) sqrt(dr01sqr);
  for ( j = 2; j < lj->n; j++ ) {
    lj_pairlj3dx(x0, lj->x + j*3, dx, lj->l, lj->rc2, &dr2, &u, &vir);
    rf -= vir * rv3_dot(dx01, dx) / dr2 / dr01;
    lj_pairlj3dx(x1, lj->x + j*3, dx, lj->l, lj->rc2, &dr2, &u, &vir);
    rf += vir * rv3_dot(dx01, dx) / dr2 / dr01;
  }
  return rf / 2;
}



/* 3D compute force and virial, return energy */
INLINE real lj_energylj3dx(lj_t *lj, rv3_t *x, real *virial, real *ep0, real *eps)
{
  real dx[3], dr2, dr6, ep, vir, l = lj->l, rc2 = lj->rc2;
  int i, j, prcnt = 0;

  if (virial) *virial = 0.f;
  /* skip the pair (0, 1) */
  for (ep = vir = 0, i = 0; i < lj->n - 1; i++) {
    for (j = (i == 0) ? 2 : i + 1; j < lj->n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 > rc2) continue;
      dr2 = 1.f / dr2;
      dr6 = dr2 * dr2 * dr2;
      vir += dr6 * (48.f * dr6 - 24.f); /* f.r */
      ep += 4 * dr6 * (dr6 - 1);
      prcnt++;
    }
  }
  if (ep0) *ep0 = ep;
  if (eps) *eps = ep - prcnt * lj->epot_shift; /* shifted energy */
  if (virial) *virial = vir;
  return ep + lj->epot_tail; /* unshifted energy */
}


/* return the energy change from displacing x[i] to xi */
INLINE real lj_depotlj3dx(lj_t *lj, int i, real *xi, real *vir)
{
  int j;
  real l = lj->l, rc2 = lj->rc2, u = 0.f, du = 0.f, dvir = 0.f;
  rv3_t *x = (rv3_t *) lj->x;

  *vir = 0.0f;
  for (j = 2; j < lj->n; j++) { /* pair */
    if (j == i) continue;
    if (lj_pairlj3d(x[i], x[j], l, rc2, &du, &dvir)) {
      u -= du;
      *vir -= dvir;
    }
    if (lj_pairlj3d(xi, x[j], l, rc2, &du, &dvir)) {
      u += du;
      *vir += dvir;
    }
  }
  return u;
}



INLINE int lj_insert(lj_t *lj, real beta, real bmu0, int nmax)
{
  int j, nn = lj->n;
  real du = 0, dvir = 0, u, vir, fac, xi[3];

  if (lj->n >= nmax) return 0;

  for (j = 0; j < 3; j++) xi[j] = (real) rnd0();
  for (u = vir = 0, j = 0; j < nn; j++) { /* pair energy */
    if (lj_pair(lj, xi, lj->x + 3*j, &du, &dvir)) {
      u += du;
      vir += dvir;
    }
  }
  du  = lj_gettail(lj, (nn+1)/lj->vol, nn+1, NULL);
  du -= lj_gettail(lj, nn/lj->vol, nn, NULL);

  /* we do not consider utail in the acceptance ratio */
  fac = lj->vol*exp(bmu0 - beta*(u+du))/(nn+1);
  if ( fac > 1 || rnd0() < fac ) { /* accept */
    rv3_copy(lj->x + nn*3, xi);
    lj->epot0 += u;
    lj->vir += vir;
    lj->n = nn + 1;
    lj_setrho(lj, lj->n/lj->vol);
    lj->epot = lj->epot0 + lj->epot_tail;
    //real ep1, ep0, vir1;
    //ep1 = lj_energylj3d(lj, (rv3_t *) lj->x, &vir1, &ep0, NULL);
    //printf("insert: epot0 %g(%g), epot %g(%g), vir %g(%g)\n", lj->epot0, ep0, lj->epot, ep1, lj->vir, vir1); getchar();
    lj->dof = lj->n * lj->d;
    return 1;
  }
  return 0;
}



INLINE int lj_delete(lj_t *lj, real beta, real bmu0)
{
  int i, j, nn = lj->n;
  real du = 0, dvir = 0, u, vir, fac, *xi;

  if (nn <= 0) return 0;

  i = (int) (rnd0() * nn);
  xi = lj->x + 3*i;
  for (u = vir = 0, j = 0; j < nn; j++) { /* pair energy */
    if ( j == i ) continue;
    if (lj_pair(lj, xi, lj->x + 3*j, &du, &dvir)) {
      u += du;
      vir += dvir;
    }
  }
  du  = lj_gettail(lj, nn/lj->vol, nn, NULL);
  du -= lj_gettail(lj, (nn-1)/lj->vol, nn-1, NULL);

  fac = nn*exp(beta*(u+du) - bmu0)/lj->vol;
  if ( fac > 1 || rnd0() < fac ) { /* accept */
    rv3_copy(xi, lj->x + (nn-1)*3);
    lj->epot0 -= u;
    lj->vir -= vir;
    lj->n = nn - 1;
    lj_setrho(lj, lj->n/lj->vol);
    lj->epot = lj->epot0 + lj->epot_tail;
    lj->dof = lj->n * lj->d;
    //real ep1, ep0, vir1;
    //ep1 = lj_energylj3d(lj, (rv3_t *) lj->x, &vir1, &ep0, NULL);
    //printf("delete: epot0 %g(%g), epot %g(%g), vir %g(%g)\n", lj->epot0, ep0, lj->epot, ep1, lj->vir, vir1); getchar();
    return 1;
  }
  return 0;
}




#endif /* LJX_H__ */

