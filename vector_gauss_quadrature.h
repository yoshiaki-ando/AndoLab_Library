/*
 * vector_gauss_quadrature.h
 *
 *  Created on: 2019/07/11
 *      Author: ando
 *
 *tex \section{ベクトルを引数にするGauss-Legendre積分}
 *tex
 *tex \subsection{使用法}
 *tex {\baselineskip=12pt
 *tex \begin{verbatim}
 *tex #include <vector3.h>
 *tex #include <gauss_integration_vector.h>
 *tex
 *tex double f(FDTD::Vector <double> r, void *p){
 *tex   // 関数定義、r 以外はすべて p を経由する
 *tex   Parameters params = *( (Parameters*)p );
 *tex }
 *tex
 *tex double *zero_pts = new double [8];
 *tex double *weight   = new double [8];
 *tex FDTD::Vector <double> r1, r2; // 始点、終点
 *tex zeropoint_weight(zero_pts, weight); // 零点、重みを求める
 *tex
 *tex Parameters params; // パラメタ
 *tex Parameters *prms = &params;
 *tex
 *tex double ans = gauss_integration_vector(f, (void*)prms, r1, r2, zero_pts, weight);
 *tex \end{verbatim}
 *tex }
 */

#ifndef VECTOR_GAUSS_QUADRATURE_H_
#define VECTOR_GAUSS_QUADRATURE_H_

#include "Vector3d.h"

namespace AndoLab {

using func = double (*)(AndoLab::Vector3d <double>, void*);

constexpr double zp[8] = {
    0.09501250983763744018531933542496,
    0.28160355077925891323046050146050,
    0.45801677765722738634241944298358,
    0.61787624440264374844667176404879,
    0.75540440835500303389510119484744,
    0.86563120238783174388046789771239,
    0.94457502307323257607798841553461,
    0.98940093499164993259615417345033 };
constexpr double w[8] = {
    0.18945061045506849628539672320828,
    0.18260341504492358886676366796922,
    0.16915651939500253818931207903036,
    0.14959598881657673208150173054748,
    0.12462897125553387205247628219202,
    0.09515851168249278480992510760225,
    0.06225352393864789286284383699438,
    0.02715245941175409485178057245602 };

/* r1からr2までの 16次ガウス-ルジャンドル積分 */
double vector_gauss_quadrature(
    func Function_of_integrand,
    void *Parameters,
    AndoLab::Vector3d <double> r1, AndoLab::Vector3d <double> r2);
//void zeropoint_weight(double *zeropoint, double *weight);

}

#endif /* VECTOR_GAUSS_QUADRATURE_H_ */
