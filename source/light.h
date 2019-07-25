#ifndef LIGHT_H
#define LIGHT_H

#include "matrix.h"
#include "color.h"

// TODO : a class to separate ambiant/directional/point light
class Light {
 public:
    Light(const Matrix& p, Color i, Color a) : pos(p), intensity(i), ambiant(a) {}
    ~Light() {}

    Matrix pos ;
    Color intensity ;
    Color ambiant ;
};

#endif // LIGHT_H
