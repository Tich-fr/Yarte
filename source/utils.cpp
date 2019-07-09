#include "utils.h"

#include <cmath>

Matrix rotate(double x, double y, double z, double angle) {
    //TODO : optimize this function
    Matrix I = Matrix::Id(3) ;
    Matrix J(3,3) ;
    Matrix V(3,1) ;

    V(0,0) = x ;
    V(1,0) = y ;
    V(2,0) = z ;
    V.normalize() ;
    
    J(1,2) = -V(0,0) ;
    J(2,1) =  V(0,0) ;
    J(2,0) = -V(1,0) ;
    J(0,2) =  V(1,0) ;
    J(0,1) = -V(2,0) ;
    J(1,0) =  V(2,0) ;

    return (I + J*sin(angle) + (J*J * (1.0 - cos(angle)))).homogenized() ;
}

Matrix translate(double x, double y, double z) {
    Matrix res = Matrix::Id() ;

    res(0,3) = x ;
    res(1,3) = y ;
    res(2,3) = z ;

    return res ;
}

Matrix scale(double x, double y, double z) {
    Matrix res = Matrix::Id() ;
    
    res(0,0) = x ;
    res(1,1) = y ;
    res(2,2) = z ;

    return res ;
}

double solve_quadratic_min(double a, double b, double c) {

    double discriminant, t1, t2, min ;

    discriminant = b*b - 4*a*c ;

    if (discriminant < 0.0) {
        return -1.0 ;
    } else if (discriminant < EPSILON) { // ~= 0 
        return -b/a ;
    } else {
        t1 = (-b - sqrtl(discriminant)) / a ;
        t2 = (-b + sqrtl(discriminant)) / a ;

        min = t1<t2 ? t1 : t2 ;

        return min>EPSILON ? min : -1.0 ;
    }
}

Matrix vector_a_to_b(const Matrix& a, const Matrix& b) {
    return (b - a).normalized() ;
}

Matrix vector_to_specular_reflection(const Matrix& n, const Matrix& s) {
    return ((s * -1.0) + (n * 2 * n.dot(s))).normalized() ;
}

Matrix coordinate_on_segment(const Matrix& e, const Matrix& d, double t) {

    Matrix res(4,1) ;

    res(0,0) = e(0,0) + d(0,0) * t ;
    res(0,0) = e(1,0) + d(1,0) * t ;
    res(0,0) = e(2,0) + d(2,0) * t ;
    res(0,0) = 1.0 ;

    return res;
}
