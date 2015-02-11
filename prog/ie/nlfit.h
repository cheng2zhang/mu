/* iteratively compute the chemical potential mu */
#define getmuiter getmuiter_3_1



__inline static xdouble getmuiter_3_1(xdouble rho, xdouble sf, xdouble sfff, xdouble sc, xdouble sdc)
{
  xdouble X = sc, Y = sdc, Z, Z0, nZ, Q0, Q1;
  xdouble A, B = 0, C = 0, D = 0;
  xdouble a11, a12, a21, a22, b1, b2, det;
  int iter, itermax = 1000;

  /* first trial */
  Q0 = sc - sf - rho * sfff;
  Q1 = sdc - sfff;
  Z0 = rho * (sf + sfff*rho/2 +  Q0 * Q0 / (rho*Q1 + Q0 + 1e-8));
  Z = Z0;
  /* solve
   *  (1)     Z (1 + D rho) = A rho + B rho^2 + C rho^3
   *  (2)     X (1 + D rho) + Z D = A + 2 B rho + 3 C rho^2
   *  (3)     Y (1 + D rho) + 2 X D = 2 B + 6 C rho
   * At rho = 0, we have, X0 = sf, Z0 = 0
   *    X0 = A = sf
   *    Y0 + 2 X0 D = 2 B,  B = sfff / 2 + sf D
   * Assume a Z, try to solve D and C from (2) and (3) */
  for ( iter = 0; iter < itermax; iter++ ) {
    A = sf;
    B = sfff / 2 + sf * D;
    a11 = X * rho + Z;
    a21 = Y * rho + 2 * X;
    a12 = -3 * rho * rho;
    a22 = -6 * rho;
    b1 = A - X + 2 * B * rho;
    b2 = - Y + 2 * B;
    det = a11 * a22 - a12 * a21;
    /* solve C and D */
    D = (a22 * b1 - a12 * b2) / det;
    C = (a11 * b2 - a21 * b1) / det;
    nZ = (A * rho + B * rho * rho + C * rho * rho * rho) / (1 + D * rho);
    if ( FABS(nZ - Z) < 1e-10 ) break;
    //printf("Z %g, nZ %g\n", (double) Z, (double) nZ);
    Z = nZ;
  }
  if ( iter > itermax )
    printf("rho %g, iteration %d, Z %g --> %g, det %g\n",
        (double) rho, iter, (double) Z0, (double) Z, (double) det);
  //getchar();
  return -Z;
}




__inline static xdouble getmuiter_2_1(xdouble rho, xdouble sf, xdouble sfff, xdouble sc, xdouble sdc)
{
  xdouble X = sc, Y = sdc, Z, Z0, nZ, Q0, Q1;
  xdouble A, B = 0, C = 0;
  xdouble a11, a12, a21, a22, b1, b2, det;
  int iter, itermax = 100;

  /* first trial */
  Q0 = sc - sf - rho * sfff;
  Q1 = sdc - sfff;
  Z0 = rho * (sf + sfff*rho/2 +  Q0 * Q0 / (rho*Q1 + Q0 + 1e-8));
  Z = Z0;
  /* solve
   *  (1)     Z (1 + C rho) = A rho + B rho^2
   *  (2)     X (1 + C rho) + Z C = A + 2 B rho
   *  (3)     Y (1 + C rho) + 2 X C = 2 B
   * At rho = 0, we have, X0 = sf, Z0 = 0
   *    X0 = A = sf
   * Assume a Z, try to solve C and B from (2) and (3) */
  for ( iter = 0; iter < itermax; iter++ ) {
    A = sf;
    a11 = X * rho + Z;
    a21 = Y * rho + 2 * X;
    a12 = -2 * rho;
    a22 = -2;
    b1 = A - X;
    b2 = - Y;
    det = a11 * a22 - a12 * a21;
    /* solve C, B */
    C = (a22 * b1 - a12 * b2) / det;
    B = (a11 * b2 - a21 * b1) / det;
    nZ = (A * rho + B * rho * rho) / (1 + C * rho);
    if ( FABS(nZ - Z) < 1e-10 ) break;
    //printf("Z %g, nZ %g\n", (double) Z, (double) nZ);
    Z = nZ;
  }
  if ( iter > itermax )
    printf("rho %g, iteration %d, Z %g --> %g, det %g\n",
        (double) rho, iter, (double) Z0, (double) Z, (double) det);
  //getchar();
  return -Z;
}



/* this interpolation is unstable */
__inline static xdouble getmuiter_2_2(xdouble rho, xdouble sf, xdouble sfff, xdouble sc, xdouble sdc)
{
  xdouble X = sc, Y = sdc, Z, Z0, nZ, Q0, Q1;
  xdouble A, B, C = 0, D = 0;
  xdouble a11, a12, a21, a22, b1, b2, det;
  int iter;

  /* first trial */
  Q0 = sc - sf - rho * sfff;
  Q1 = sdc - sfff;
  Z0 = rho * (sf + sfff*rho/2 +  Q0 * Q0 / (rho*Q1 + Q0 + 1e-8));
  Z = Z0;
  /* solve
   *  (1)     Z (1 + C rho + D rho^2) = A rho + B rho^2
   *  (2)     X (1 + C rho + D rho^2) + Z (C + 2 D rho) = A + 2 B rho
   *  (3)     Y (1 + C rho + D rho^2) + 2 X (C + 2 D rho) + Z 2 D  = 2 B
   * At rho = 0, we have, X0 = sf, Y0 = sfff, Z0 = 0
   *    X0 = A = sf
   *    Y0 + 2 X0 C = 2 B, --> B = sfff/2 + sf C
   * Assume a Z, try to solve C and D from (2) and (3) */
  for ( iter = 0; iter < 1000; iter++ ) {
    A = sf;
    B = sfff / 2 + sf * C;
    a11 = X * rho + Z;
    a21 = Y * rho + 2 * X;
    a12 = X * rho * rho + 2 * Z * rho;
    a22 = Y * rho * rho + 4 * X * rho + 2 * Z;
    b1 = A + 2 * B * rho - X;
    b2 = 2 * B - Y;
    det = a11 * a22 - a12 * a21;
    /* solve C, D */
    C = (a22 * b1 - a12 * b2) / det;
    D = (a11 * b2 - a21 * b1) / det;
    nZ = (A * rho + B * rho * rho) / (1 + C * rho + D * rho * rho);
    if ( FABS(nZ - Z) < 1e-10 ) break;
    //printf("Z %g, nZ %g\n", (double) Z, (double) nZ);
    Z = nZ;
  }
  printf("rho %g, iteration %d, Z %g --> %g, det %g\n",
      (double) rho, iter, (double) Z0, (double) Z, (double) det);
  getchar();
  return -Z;
}




#define getpresiter getpresiter_3_1

__inline static xdouble getpresiter_3_1(xdouble rho, xdouble sf, xdouble sfff, xdouble sc, xdouble sdc)
{
  xdouble X = rho * sc, Y = sc + rho * sdc, Z, Z0, nZ, Q0, Q1;
  xdouble A, B = 0, C = 0, D = 0;
  xdouble a11, a12, a21, a22, b1, b2, det;
  int iter, itermax = 1000;

  /* first trial */
  Q0 = sc - sf - rho * sfff;
  Q1 = sdc - sfff;
  //Z0 = rho * (sf + sfff*rho/2 +  Q0 * Q0 / (rho*Q1 + Q0 + 1e-8));
  //*pres4 = rho - rho*rho*(sf*.5 + sfff*rho/3 +  Q0*Q0/(rho*Q1 + 2*Q0 + 1e-8));
  Z0 = rho*rho*(sf*.5 + sfff*rho/3 +  Q0*Q0/(rho*Q1 + 2*Q0 + 1e-8));
  Z = Z0;
  /*
   * d (beta P) / d rho = rho \int c dr
   * d^2 (beta P) / d rho^2 = \int c dr + rho \int dc dr
   *
   * solve
   *  (1)     Z (1 + D rho) = A rho^2 + B rho^3 + C rho^4
   *  (2)     X (1 + D rho) + Z D = 2 A rho + 3 B rho^2 + 4 C rho^3
   *  (3)     Y (1 + D rho) + 2 X D = 2 A + 6 B rho + 12 C rho^2
   * At rho --> 0, we have, Z0 = 0, X0 = rho sf, Y0 = sf + rho sfff
   *    X0 = 2 A rho, --> A = sf / 2
   *    (sf + 2 rho sfff) (1 + D rho) + 2 rho sf D = 2 A + 6 B rho
   *    (2 sfff + 3 sf D) = 6 B,  --> B = sfff / 3 + sf D / 2
   * Assume a Z, try to solve D and C from (2) and (3) */
  for ( iter = 0; iter < itermax; iter++ ) {
    A = sf / 2;
    B = sfff / 3 + sf * D / 2;
    a11 = X * rho + Z;
    a21 = Y * rho + 2 * X;
    a12 = -4 * rho * rho * rho;
    a22 = -12 * rho * rho;
    b1 = 2 * A * rho + 3 * B * rho * rho - X;
    b2 = 2 * A + 6 * B * rho - Y;
    det = a11 * a22 - a12 * a21;
    /* solve C and D */
    D = (a22 * b1 - a12 * b2) / det;
    C = (a11 * b2 - a21 * b1) / det;
    nZ = rho * rho * (A + B * rho + C * rho * rho) / (1 + D * rho);
    if ( FABS(nZ - Z) < 1e-10 ) break;
    //printf("iter %d: Z %g, nZ %g, Z0 %g\n", iter, (double) Z, (double) nZ, (double) Z0);
    Z = nZ;
  }
  if ( iter > itermax )
    printf("rho %g, iteration %d, Z %g --> %g, det %g\n",
        (double) rho, iter, (double) Z0, (double) Z, (double) det);
  //getchar();
  return rho - Z;
}





