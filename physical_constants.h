/*
 * 物理定数
 *
 */
#include <cmath>

#ifndef PHYSICAL_CONSTANTS_H_
#define PHYSICAL_CONSTANTS_H_

/*
 * 真空の光速 c0 = 299792458 m/s
 */
constexpr double C0 { 299792458.0 };

/*
 * 真空の透磁率 μ0 = 4 \pi \times 10^{-7}$~H/m
 */
constexpr double MU0 { 4.0e-7 * M_PI };

/*
 * 真空の誘電率 ε0 = 1/(\mu_0 c_0^2) F/m
 */
constexpr double EPS0 { 1.0/C0/C0/MU0 };

/*
 * モル気体定数 R = 8.3144598 J /K /mol
 */
constexpr double MOLAR_GAS_CONSTANT { 8.3144598 };

/*
 * ボルツマン定数 k_B = 1.38064852 × 10^{-23} m^2 kg /s^2 /K
 */
constexpr double BOLTZMANN_CONSTANT { 1.38064852e-23 };

#endif
