#include "xdouble.h"



/* compressibility-route chemical potential */
__inline static xdouble hs3d_getbmuc(xdouble rho)
{
  xdouble eta = rho * PI / 6, e1 = 1 - eta;
  return eta * (14 + eta * (-13 + 5 * eta)) / (2 * e1 * e1 * e1) - LOG(e1);
}



/* compressibility-route pressure */
__inline static xdouble hs3d_getbPc(xdouble rho)
{
  xdouble eta = rho * PI / 6, e1 = 1 - eta, z;
  z = (1 + eta * (1 + eta)) / (e1 * e1 * e1);
  return z * rho;
}



/* virial-route chemical potential */
__inline static xdouble hs3d_getbmuv(xdouble rho)
{
  xdouble eta = rho * PI / 6, e1 = 1 - eta;
  return 2 * eta * (5 - 2 * eta) / (e1 * e1) + 2 * LOG(e1);
}



/* virial-route chemical potential */
__inline static xdouble hs3d_getbPv(xdouble rho)
{
  xdouble eta = rho * PI / 6, e1 = 1 - eta, z;
  z = (1 + eta * (2 + eta * 3)) / (e1 * e1);
  return z * rho;
}



/* chemical-potential-route chemical potential
 * the charging parameter is the radius of the test particle */
__inline static xdouble hs3d_getbmux(xdouble rho)
{
  xdouble eta = rho * PI / 6, e1 = 1 - eta;
  return eta * (14 + eta) / (2 * e1 * e1) - LOG(e1);
}



/* chemical-potential-route pressure
 * the charging parameter is the radius of the test particle */
__inline static xdouble hs3d_getbPx(xdouble rho)
{
  xdouble eta = rho * PI / 6, e1 = 1 - eta, z;
  z = -9 * LOG(e1)/eta - 8*(1 - eta*31/16)/(e1*e1);
  return z * rho;
}
