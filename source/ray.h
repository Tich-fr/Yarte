#ifndef RAY_H
#define RAY_H

#include "matrix.h"

class Ray {
 public:
    Ray(const Matrix& e, const Matrix& d) ;
    ~Ray() ;

    Matrix position_at(double t) const ;

    void shift(double val) ;

    const Matrix& get_pos() const ;
    const Matrix& get_dir() const ;

private:
    Matrix pos ;
    Matrix dir ;
} ;

#endif // RAY_H
