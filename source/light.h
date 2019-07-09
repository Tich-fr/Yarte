#ifndef LIGHT_H
#define LIGHT_H

#include "matrix.h"
#include "color.h"

class Light {
 public:
     Light(const Matrix& p, Color c, Color i) : pos(p), col(c), intensity(i) {}
    ~Light() {}

    Matrix pos ;
    Color col ;
    Color intensity ;
};

#endif // LIGHT_H
