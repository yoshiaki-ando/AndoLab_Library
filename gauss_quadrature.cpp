/*
 * gauss_quadrature.cpp
 *
 *  Created on: 2021/10/06
 *      Author: ando
 */
#include <cmath>
#include "gauss_quadrature.h"

double AndoLab::gauss_quadrature(
    integrand func,
    void *params, const double a, const double b){

  constexpr int N { 8 };
  double ans = 0.0;
  const double span { 0.5 * (b-a) };
  const double mean { 0.5 * (b+a) };

  for(int i = 0; i < N; i++){
    ans += g_w[i] *
        ( func( span*g_zp[i] + mean, params)
        + func(-span*g_zp[i] + mean, params) );
  }

  return ans * span;
}

double AndoLab::converged_gauss_quadrature(
    integrand func,
    void *params,
    const double a, const double b,
    const double ini_ans, const double eps
    ){

  const double mid { (a + b)/2.0 };

  double ans1 = gauss_quadrature(func, params, a, mid);
  double ans2 = gauss_quadrature(func, params, mid, b);

  if ( std::abs( (ans1 + ans2 - ini_ans) / (ans1 + ans2) ) > eps ){
    ans1 = converged_gauss_quadrature(func, params, a, mid, ans1, eps*2.0);
    ans2 = converged_gauss_quadrature(func, params, mid, b, ans2, eps*2.0);
  }

  return ans1 + ans2;
}
