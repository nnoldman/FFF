#pragma once
#include <math.h>
#include <limits>
//#include <d3dx9math.h>

#define QX q.x
#define QY q.y
#define QZ q.z
#define QW q.w

//void QuaternionToMatrix(const D3DXQUATERNION& q, D3DXMATRIX& m);
//
//
//void MatrixToQuaternion(const D3DXMATRIX& m, D3DXQUATERNION& q);

template<typename T>
T  dScale ( T src, T reference, double scale ) {
    return reference + scale * ( src - reference );
}

template<typename T>
T dClamp ( T src, T minv, T maxv ) {
    T t0 = dMin ( minv, maxv );
    T t1 = dMax ( minv, maxv );
    if ( src < t0 )
        src = t0;
    if ( src > t1 )
        src = t1;
    return src;
}
inline int dRound ( double src, int base = 1 ) {
    int d = ( int ) src / base * base;
    if (src + base * 0.5 > d + base)
        return int(d + base);
    return d;
}