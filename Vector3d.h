/*
 * Vector3d.h
 *
 * 3次元ベクトルを扱うテンプレートライブラリ
 *
 *  Created on: 2019/07/10
 *      Author: ando
 */

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <iostream>
#include <cmath>
#include <complex>
#include <string>

namespace AndoLab {
enum class coordinate { Cartesian, Spherical };

constexpr double DEG2RAD { M_PI / 180.0 };
constexpr double RAD2DEG { 180.0 / M_PI };

template <class T>
class Vector3d{
private:
  T pX, pY, pZ;
  T pR, pTheta, pPhi;

public:
  /* Constructor */
  Vector3d(void):
    pX(T(0)), pY(T(0)), pZ(T(0)),
    pR(T(0)), pTheta(T(0)), pPhi(T(0)) { };
  Vector3d(T vx, T vy, T vz);
  Vector3d(T v1, T v2, T v3, coordinate);

  void convert2spherical(void);
  void convert2cartesian(void);

  /* アクセサ */
  T x(void){ return pX; }
  T y(void){ return pY; }
  T z(void){ return pZ; }
  void x(T vx){ pX = vx; }
  void y(T vy){ pY = vy; }
  void z(T vz){ pZ = vz; }

  T r(void){ return pR; }
  T theta(void){ return pTheta; }
  T phi(void){ return pPhi; }

  void set(T vx, T vy, T vz);
  void set(T v1, T v2, T v3, coordinate);

  /* 演算子 */
  Vector3d <T> operator + (Vector3d <T>);
  Vector3d <T> operator - (Vector3d <T>);
  template <class T2>
  friend Vector3d <T2> operator * (T2, Vector3d <T2>);
  Vector3d <T> operator *(T);
  Vector3d <T> operator /(T);
  /* ベクトルの演算 */
  T operator % (Vector3d <T>); /* 内積 */
  Vector3d <T> operator * (Vector3d <T>); /* 外積 */

  template <class T2>
  Vector3d <T> operator & (Vector3d <T2>); /* ベクトル成分同士のかけ算 */
  template <class T2>
  Vector3d <T> operator / (Vector3d <T2>); /* ベクトル成分同士の割り算 */

  /* メンバ関数 */
  T abs(void);
  Vector3d <T> n(void){ return (*this) / this->abs(); }; /* 正規化 */
  std::string string(
      std::string separtor = "",
      std::string kakko = "  "
      );
  Vector3d <T> rotate(const T Rotation_Angle, Vector3d <T> Axis_vector);

  /* その点を基準とした 𝒓^ , 𝜽^ , 𝝓^ */
  Vector3d <T> r_vector(void);
  Vector3d <T> theta_vector(void);
  Vector3d <T> phi_vector(void);

  /* 緯度・経度 */
  T latitude(void);
  T longitude(void);

  /* 非メンバ関数 */
  template <class T2>
  friend T2 abs(Vector3d <T2>);
  template <class T2>
  friend Vector3d <T2> geographic_coordinate( /* 緯度経度を単位ベクトルに変換 */
      T2 Latitude_in_deg, T2 Longitude_in_deg);

};

template <class T>
Vector3d <T>::Vector3d(T vx, T vy, T vz):
pX( vx ), pY( vy ), pZ( vz )
{
  convert2spherical();
}

template <class T>
Vector3d <T>::Vector3d(T v1, T v2, T v3, coordinate present_coord){
  set(v1, v2, v3, present_coord);
}

template <class T>
void Vector3d <T>::set(T vx, T vy, T vz){
  pX = vx;
  pY = vy;
  pZ = vz;
  convert2spherical();
}

template <class T>
void Vector3d <T>::set(T v1, T v2, T v3, coordinate present_coord){
  if ( present_coord == coordinate::Cartesian ){
    pX = v1;
    pY = v2;
    pZ = v3;
    convert2spherical();
  } else if ( present_coord == coordinate::Spherical ){
    pR = v1;
    pTheta = v2;
    pPhi = v3;
    convert2cartesian();
  }
}

template <class T>
void Vector3d <T>::convert2spherical(void){
  pR = std::sqrt(pX*pX + pY*pY + pZ*pZ);
  pPhi = std::atan2( pY, pX );
  pTheta = std::atan2( std::sqrt(pX*pX + pY*pY), pZ );
}

template <class T>
void Vector3d <T>::convert2cartesian(void){
  pX = pR * std::sin(pTheta) * std::cos(pPhi);
  pY = pR * std::sin(pTheta) * std::sin(pPhi);
  pZ = pR * std::cos(pTheta);
}

template <class T>
Vector3d <T> Vector3d<T>::operator +(Vector3d <T> op){
  return Vector3d <T> (pX + op.pX, pY+op.pY, pZ+op.pZ);
}

template <class T>
Vector3d <T> Vector3d<T>::operator -(Vector3d <T> op){
  return Vector3d <T> (pX - op.pX, pY-op.pY, pZ-op.pZ);
}

template <class T>
Vector3d <T> operator *(T coef, Vector3d <T> op){
  return Vector3d <T> (coef*op.pX, coef*op.pY, coef*op.pZ);
}

template <class T>
Vector3d <T> Vector3d <T>::operator *(T coef){
  return Vector3d <T> (coef*pX, coef*pY, coef*pZ);
}

template <class T>
Vector3d <T> Vector3d <T>::operator /(T divider){
  return Vector3d <T> (pX/divider, pY/divider, pZ/divider);
}

template <class T>
Vector3d <T> Vector3d <T>::r_vector(void){
  return n();
}

template <class T>
Vector3d <T> Vector3d <T>::theta_vector(void){
  return Vector3d <T> { 1.0, pTheta + M_PI/2.0, pPhi, coordinate::Spherical };
}

template <class T>
Vector3d <T> Vector3d <T>::phi_vector(void){
  return Vector3d <T> { 1.0, M_PI/2.0, pPhi + M_PI/2.0, coordinate::Spherical };
}

template <class T>
T Vector3d <T>::abs(void){
  return std::sqrt(pX*pX + pY*pY + pZ*pZ);
}

template <class T>
T abs(Vector3d <T> v){
  return std::sqrt(v.pX*v.pX + v.pY*v.pY + v.pZ*v.pZ);
}

template <class T>
T Vector3d <T>::operator % (Vector3d <T> op){
  return pX*op.pX + pY*op.pY + pZ*op.pZ;
}

template <class T>
Vector3d <T> Vector3d <T>::operator *(Vector3d <T> op){
  return Vector3d <T> (
      pY*op.pZ - pZ*op.pY,
      pZ*op.pX - pX*op.pZ,
      pX*op.pY - pY*op.pX );
}

template <class T>
template <class T2>
Vector3d <T> Vector3d <T>::operator &(Vector3d <T2> op){
  return Vector3d <T> ( pX * op.x(), pY * op.y(), pZ * op.z() );
}

template <class T>
template <class T2>
Vector3d <T> Vector3d <T>::operator /(Vector3d <T2> op){
  return Vector3d <T> ( pX / op.x(), pY / op.y(), pZ / op.z() );
}

template <class T>
T angle_between(Vector3d <T> v1, Vector3d <T> v2){

  if ( v1.abs() == 0.0 ){
    throw std::string("(my_vector3.h) The 1st vector is zero.");
  } else if ( v2.abs() == 0.0 ){
    throw std::string("(my_vector3.h) The 2nd vector is zero.");
  }

  const double cos_th = v1%v2 / v1.abs() / v2.abs();

  return acos( cos_th>1.0?1.0:cos_th );
}

/* 緯度経度を単位ベクトルに変換 */
template <class T>
Vector3d <T> geographic_coordinate(T lat, T lon){
  T th = M_PI/2.0 - lat*DEG2RAD;
  T ph = lon * DEG2RAD;
  return Vector3d <T> { 1.0, th, ph, coordinate::Spherical };
}

/* ベクトルの緯度を計算 */
template <class T>
T Vector3d <T>::latitude(void){
  return (0.5*M_PI - pTheta) * RAD2DEG;
}

/* ベクトルの経度を計算 */
template <class T>
T Vector3d <T>::longitude(void){
  return pPhi * RAD2DEG;
}

template <class T>
Vector3d <T> Vector3d <T>::rotate(const T th, Vector3d <T> axis_v){
  const T cth { std::cos(th) };
  const T sth { std::sin(th) };
  const T m_cth { 1.0 - cth };
  Vector3d <T> naxis_v = axis_v.n();

  return m_cth * (naxis_v%(*this)) * naxis_v
      + cth*(*this) + sth * (naxis_v * (*this));
}


template <class T>
std::string Vector3d <T>::string(
    std::string separator,
    std::string kakko
        ){
  const int l = kakko.size();
  const double X { pX };
  const double Y { pY };
  const double Z { pZ };

  std::string str =
      kakko.substr(0, l/2) +
      std::to_string(X) + separator + " "
      + std::to_string(Y) + separator + " "
      + std::to_string(Z) + kakko.substr(l/2, l/2);
  return str;
}

} /* namespace */

#endif /* VECTOR3D_H_ */
