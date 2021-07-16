# 安藤研究室用ライブラリ
## 目次
* [目次](#概要)
* [Vector3d.h 3次元ベクトル](#vector3dh-3次元ベクトル)
* [vector_gauss_quadrature 位置ベクトルを引数とするガウス・ルジャンドル積分](#vector_gauss_quadrature-位置ベクトルを引数とするガウス・ルジャンドル積分)

## 概要
* 全て namespace は <b>AndoLab</b>

## Vector3d.h: 3次元ベクトル

### インクルード
```C++:Vector3d.h
#include <Vector3d.h>
```

### 定数
```C++:
enum class Andolab::coordinate { Cartesian, Spherical };
```

### コンストラクタ
Tは任意の型
```C++:
Vector3d <T> v;
Vector3d <T> v(T x, T y, T z); /* デカルト座標系でのベクトル(x,y,z)  */
Vector3d <T> v(T x1, T x2, T x3, AndoLab::coordinate cs); /* 座標系csで指定されたベクトル(x1,x2,x3) */
```

### アクセサ
```C++:
T x(void); /* デカルト座標系のx成分 */
T y(void); /* デカルト座標系のy成分 */
T z(void); /* デカルト座標系のz成分 */
T r(void); /* 球座標系のr成分(θ、φ方向) */
T theta(void); /* 球座標系のθ方向 */
T phi(void); /* 球座標系のφ方向 */

void set(T x, T y, T z); /* デカルト座標系でのベクトル(x,y,z)  */
void set(T x1, T x2, T x3, AndoLab::coordinate cs); /* 座標系csで指定されたベクトル(x1,x2,x3) */
```

### 演算子
`a, b`は `Vector3d <T>`とする。pは`T`型の変数・定数とする。
* `a + b` : 和
* `a - b` : 差
* `p * a`, `a * p` : スカラー倍
* `a / p` : スカラー割
* `a * b` : 外積、ベクトル積
* `a % b` : 内積、スカラー積
* `a & b` : 成分毎の掛け算
* `a / b` : 成分ごとの割り算

### メンバ関数
* `T abs(void)` : 大きさ
* `Vector3d <T> n(void)` : 正規化、単位ベクトル化
* `std::string string(std::string separator, std::string kakko)` : 表示用のstring型作成。separator(kakkoが省略なら省略可)は,(カンマ)などを指定する(省略時は空白一文字)。kakko(省略可)は ```()``` といった、3成分を囲むカッコの組を与える(省略時は囲みなし)。

### 非メンバ関数
* `T abs(Vector3d <T> a)` : ベクトルaの大きさ
* `T angle_between(Vector3d <T> a, Vector3d <T> b)` : ベクトルa, bのなす角 [rad]

## vector_gauss_quadrature: 位置ベクトルを引数とするガウス・ルジャンドル積分

### 概要
位置ベクトルｒを変数に持つスカラ関数f(ｒ, a1, a2, ...)を、位置ｒ1からｒ2までの直線距離を経路として

<img src="img/eq_vector_gauss_quadrature.png">

を計算する。

### 使用法
1. 被積分関数として
`double function(AndoLab::Vector3d <double>, void*)`
で定義される関数を準備する。void*の引数は、別の型、構造体、クラスのポインタにキャストし直すことで、積分変数以外の任意のパラメタを加えることが出来る。
2. 積分範囲を定義して呼び出す。
```C++:
double result = AndoLab::vector_gauss_quadrature(r1, r2, function, (void*)pointer_of_parameters)
```

### 使用例
<img src="img/eq_vector_gauss_quadrature_sample.png">の計算
```C++:
class params{
public:
  double a, b;
};

double func1(AndoLab::Vector3d <double> r, void* vp){
  params p = *( (params*)vp );

  return p.a * AndoLab::abs(r) + p.b;
}

int main(void){
  params p0;
  p0.a = 3.0;
  p0.b = 2.0;

  AndoLab::Vector3d <double> r1(0.0, 0.0, 0.0);
  AndoLab::Vector3d <double> r2(1.0, 2.0, 3.0);
  double v = vector_gauss_quadrature(r1, r2, func, (void*)&p0);
}
```
