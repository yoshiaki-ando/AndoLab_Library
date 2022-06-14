/*
 * Matrix3d.h
 *
 *  Created on: 2022/06/14
 *      Author: ando
 */

#ifndef MATRIX3D_H_
#define MATRIX3D_H_

namespace AndoLab {

#include <Vector3d.h>

template <class T>
class Matrix3d{
private:
  T pE[3][3]; /* 要素 */

public:
  Matrix3d(void);
  Matrix3d(T** vE);
  Matrix3d(T* vE);
  Matrix3d(T e00, T e01, T e02, T e10, T e11, T e12, T e20, T e21, T e22);

  /* アクセサ */
  T e(int m, int n){ return pE[m][n]; }

  /* 演算子 */
  template <class T2>
  friend Vector3d <T2> operator * ( Matrix3d <T2>, Vector3d <T2> );
  Matrix3d <T> operator *( Matrix3d <T> );
};


/***** コンストラクタ *****/
template <class T>
Matrix3d <T>::Matrix3d(void){ /* 全て 0 で初期化 */
  for(int m = 0; m < 3; m++){
    for(int n = 0; n < 3; n++){
      pE[m][n] = (T)0;
    }
  }
}

template <class T>
Matrix3d <T>::Matrix3d(T** vE){ /* 2次元配列で初期値 */
  for(int m = 0; m < 3; m++){
    for(int n = 0; n < 3; n++){
      pE[m][n] = vE[m][n];
    }
  }
}

template <class T>
Matrix3d <T>::Matrix3d(T* vE){ /* 1次元配列で初期値(行優先) */
  /* vE = { E00, E01, E02, E10, E11, ... } */
  for(int m = 0; m < 3; m++){
    for(int n = 0; n < 3; n++){
      pE[m][n] = vE[m*3 + n];
    }
  }
}

template <class T>
Matrix3d <T>::Matrix3d(T e00, T e01, T e02, T e10, T e11, T e12, T e20, T e21, T e22){
  pE[0][0] = e00;
  pE[0][1] = e01;
  pE[0][2] = e02;
  pE[1][0] = e10;
  pE[1][1] = e11;
  pE[1][2] = e12;
  pE[2][0] = e20;
  pE[2][1] = e21;
  pE[2][2] = e22;
}

template <class T>
Vector3d <T> operator * (Matrix3d <T> A, Vector3d <T> v){
  return Vector3d <T> (
      A.pE[0][0]*v.pX + A.pE[0][1]*v.pY + A.pE[0][2]*v.pZ,
      A.pE[1][0]*v.pX + A.pE[1][1]*v.pY + A.pE[1][2]*v.pZ,
      A.pE[2][0]*v.pX + A.pE[2][1]*v.pY + A.pE[2][2]*v.pZ );
}

template <class T>
Matrix3d <T> Matrix3d <T>::operator * (Matrix3d <T> B){
  Matrix3d <T> ans;
  for(int m = 0; m < 3; m++){
    for(int n = 0; n < 3; n++){
      ans.pE[m][n] = pE[m][0]*B.pE[0][n] + pE[m][1]*B.pE[1][n] + pE[m][2]*B.pE[2][n];
    }
  }

  return ans;
}

template <class T>
Matrix3d <T> rotation_matrix(T th, Vector3d <T> n){
  double C = std::cos(th);
  double S = std::sin(th);
  double cC = 1.0 - C;
  return Matrix3d <T> (
      cC * n.pX*n.pX + C,      cC * n.pX*n.pY - S*n.pZ, cC * n.pX*n.pZ + S*n.pY,
      cC * n.pY*n.pX + S*n.pZ, cC * n.pY*n.pY + C,      cC * n.pY*n.pZ - S*n.pX,
      cC * n.pZ*n.pX - S*n.pY, cC * n.pZ*n.pY + S*n.pX, cC * n.pZ*n.pZ + C
      );
}

}

#endif /* MATRIX3D_H_ */
