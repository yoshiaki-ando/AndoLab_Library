/*
 * gauss_quadrature.h
 *
 *  Created on: 2021/10/06
 *      Author: ando
 */

#ifndef GAUSS_QUADRATURE_H_
#define GAUSS_QUADRATURE_H_


namespace AndoLab {

using integrand = double (*)(double, void*);

constexpr double g_zp[8] = {
    0.09501250983763744018531933542496,
    0.28160355077925891323046050146050,
    0.45801677765722738634241944298358,
    0.61787624440264374844667176404879,
    0.75540440835500303389510119484744,
    0.86563120238783174388046789771239,
    0.94457502307323257607798841553461,
    0.98940093499164993259615417345033 };
constexpr double g_w[8] = {
    0.18945061045506849628539672320828,
    0.18260341504492358886676366796922,
    0.16915651939500253818931207903036,
    0.14959598881657673208150173054748,
    0.12462897125553387205247628219202,
    0.09515851168249278480992510760225,
    0.06225352393864789286284383699438,
    0.02715245941175409485178057245602 };

double gauss_quadrature(
    integrand,
    void *Parameters,   /* for variables other than integral variable */
    const double a, const double b /* interval [a, b] */
    );

double converged_gauss_quadrature(
    integrand,
    void *Parameter,
    const double a, const double b,
    const double Initial_value,
    const double Epsilon_relative
    );

}

#endif /* GAUSS_QUADRATURE_H_ */
