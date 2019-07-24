#include "ray.h"

Ray::Ray(const Matrix& e, const Matrix& d) : pos(e), dir(d) {}

Ray::~Ray() {}

Matrix Ray::position_at(double t) const {

    Matrix res(4,1) ;

    res(0,0) = pos(0,0) + dir(0,0) * t ;
    res(1,0) = pos(1,0) + dir(1,0) * t ;
    res(2,0) = pos(2,0) + dir(2,0) * t ;
    res(3,0) = 1.0 ;

    return res;
}

void Ray::shift(double val) {
    pos = pos + (dir * val) ;
}

const Matrix& Ray::get_pos() const {
    return pos ;
}

const Matrix& Ray::get_dir() const {
    return dir ;
}
