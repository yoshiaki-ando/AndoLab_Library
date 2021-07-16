#include <iostream>

#include "vector_gauss_quadrature.h"
#include "Vector3d.h"

double AndoLab::vector_gauss_quadrature(
    AndoLab::func integrand,
    void *params,
    AndoLab::Vector3d <double> r1, AndoLab::Vector3d <double> r2){

  constexpr int N = 8; /* (Half) Order of Gauss-Legendre quadrature */

  double ans = 0.0;
  AndoLab::Vector3d <double> ar = 0.5*(r2-r1);
  AndoLab::Vector3d <double> br = 0.5*(r2+r1);

  for(int i = 0; i < N; i++){
    ans += w[i] *
        (integrand(ar*zp[i] + br, params)
        +  integrand(ar*(-zp[i]) + br, params) );
  }

  return ans * AndoLab::abs(ar);
}

//void zeropoint_weight(double *zeropoint, double *weight){
//
//  constexpr double zp[8] = {
//      0.09501250983763744018531933542496,
//      0.28160355077925891323046050146050,
//      0.45801677765722738634241944298358,
//      0.61787624440264374844667176404879,
//      0.75540440835500303389510119484744,
//      0.86563120238783174388046789771239,
//      0.94457502307323257607798841553461,
//      0.98940093499164993259615417345033 };
//  constexpr double w[8] = {
//      0.18945061045506849628539672320828,
//      0.18260341504492358886676366796922,
//      0.16915651939500253818931207903036,
//      0.14959598881657673208150173054748,
//      0.12462897125553387205247628219202,
//      0.09515851168249278480992510760225,
//      0.06225352393864789286284383699438,
//      0.02715245941175409485178057245602 };
//
//  for(int i = 0; i < 8; i++){
//    zeropoint[i] = zp[i];
//    weight[i] = w[i];
//  }
//}
