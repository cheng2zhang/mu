#include "ljeos.h"



/* verify the diameter */
static void verifyd(double beta, double delta)
{
  double d1, dd1, d2, dd2;
  d1 = lj_eos3d_dhBH(1./(beta - delta), &dd1);
  d2 = lj_eos3d_dhBH(1./(beta + delta), &dd2);
  printf("T %g: d1 %.10f, dd1 %.10f\n", 1/beta, d1, dd1);
  printf("T %g: d2 %.10f, dd2 %.10f\n", 1/beta, d2, dd2);
  printf("T %g: dd %.10f  vs  %.10f\n", 1/beta, (d2 - d1)/(2*delta), (dd1 + dd2)/2);
}



/* verify the residual B2 */
static void verifydB2(double beta, double delta)
{
  double B1, dB1, B2, dB2;
  B1 = lj_eos3d_dB2hBH(1./(beta - delta), &dB1);
  B2 = lj_eos3d_dB2hBH(1./(beta + delta), &dB2);
  printf("T %g: B2_1 %.10f, dB2_1 %.10f\n", 1/beta, B1, dB1);
  printf("T %g: B2_2 %.10f, dB2_2 %.10f\n", 1/beta, B2, dB2);
  printf("T %g: dB2  %.10f  vs    %.10f\n", 1/beta, (B2 - B1)/(2*delta), (dB1 + dB2)/2);
}



int main(void)
{
  double T, rho;
  double u1 = 0, P1 = 0, F1 = 0, mu1 = 0;
  double u2 = 0, P2 = 0, F2 = 0, mu2 = 0;
  double u3 = 0, P3 = 0, F3 = 0, mu3 = 0;

  verifyd(2, 0.001);
  verifydB2(2, 0.001);

  for ( T = 0.75; T <= 1.51; T += 0.25)
    for ( rho = 0.1; rho <= 1.001; rho += 0.1) {
      u1 = lj_eos3dMBWRJZG(rho, T, &P1, &F1, &mu1);
      u2 = lj_eos3dMBWRKN(rho, T, &P2, &F2, &mu2);
      u3 = lj_eos3dPVEhBH(rho, T, &P3, &F3, &mu3);
      printf("T %4.2f rho %3.1f: "
             "u %8.5f,%8.5f,%8.5f, P %8.5f,%8.5f,%8.5f; "
             "F %8.5f,%8.5f,%8.5f, mu %8.5f,%8.5f,%8.5f\n", T, rho,
          u1, u2, u3, P1, P2, P3, F1, F2, F3, mu1, mu2, mu3);
    }
  return 0;
}

