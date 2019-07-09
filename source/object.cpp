#include "object.h"
#include "utils.h" // define macro EPSILON, include <cmath>

Object::Object(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f) :
    M(Matrix::Id()), Minv(Matrix::Id()), specular(spec), diffuse(diff), ambiant(amb),
    specular_coeff(spec_c), diffuse_coeff(diff_c), ambiant_coeff(amb_c),
    density(1.0), reflectivity(reflect), f(f) {
}

Object::~Object() {}

// Infinite plane

IPlane::IPlane(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f)
    : Object(spec, spec_c, diff, diff_c, amb, amb_c, reflect, f) {}

double IPlane::intersection(const Matrix &e, const Matrix &d) const {

    if (fabs(d(2,0)) < EPSILON) // too small
        return -1.0 ;

    double t = -e(2,0) / d(2,0) ;
    return t<=0.0 ? -1.0 : t ;
}

Matrix IPlane::normal(const Matrix& intersection) const {

    Matrix normal(4,1) ;

    normal(0,0) = 0.0 ;
    normal(1,0) = 0.0 ;
    normal(2,0) = 1.0 ;
    normal(3,0) = 0.0 ;

    return normal.normalized() ;
}

// Plane

Plane::Plane(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f)
    : Object(spec, spec_c, diff, diff_c, amb, amb_c, reflect, f) {}

double Plane::intersection(const Matrix &e, const Matrix &d) const {

    if (fabs(d(2,0)) < EPSILON)
        return -1.0 ;

    double t = -e(2,0) / d(2,0) ;
    if (t <= 0.0)
        return -1.0 ;

    Matrix i = coordinate_on_segment(e, d, t) ;
    return ((fabs(i(0,0)) > 1.0) || (fabs(i(1,0)) > 1.0)) ? -1.0 : t ;
}

Matrix Plane::normal(const Matrix& intersection) const {

    Matrix normal(4,1) ;

    normal(0,0) = 0.0 ;
    normal(1,0) = 0.0 ;
    normal(2,0) = 1.0 ;
    normal(3,0) = 0.0 ;

    return normal.normalized() ;
}

// Sphere

Sphere::Sphere(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f)
    : Object(spec, spec_c, diff, diff_c, amb, amb_c, reflect, f) {}

double Sphere::intersection(const Matrix& e, const Matrix& d) const {

    Matrix dd = d.unhomogenized() ;
    Matrix ee = e.unhomogenized() ;

    double a = dd.dot(ee) ;
    double b = ee.dot(dd) ;
    double c = ee.dot(ee) - 1.0 ;

    return solve_quadratic_min(a, b, c) ;
}

Matrix Sphere::normal(const Matrix& intersection) const {

    Matrix normal(4,1) ;

    normal(0,0) = intersection(0,0) ;
    normal(1,0) = intersection(1,0) ;
    normal(2,0) = intersection(2,0) ;
    normal(3,0) = 0.0 ;

    return normal.normalized() ;
}

// Cone

Cone::Cone(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f)
    : Object(spec, spec_c, diff, diff_c, amb, amb_c, reflect, f) {}

double Cone::intersection( const Matrix &e, const Matrix &d ) const {

    double a = d(0,0)*d(0,0) + d(1,0)*d(1,0) - d(2,0)*d(2,0) ;
    double b = d(0,0)*e(0,0) + d(1,0)*e(1,0) + d(2,0)*(1-e(2,0)) ;
    double c = e(0,0)*e(0,0) + e(1,0)*e(1,0) - (1-e(2,0))*(1-e(2,0)) ;

    double t = solve_quadratic_min(a, b, c) ;
    double z = e(2,0) + d(2,0)*t ;

    return (z<=1 && z>=-1) ? t : -1.0 ;
}

Matrix Cone::normal( const Matrix &intersection ) const {

    Matrix normal(4,1) ;

    normal(0,0) = intersection(0,0) ;
    normal(1,0) = intersection(1,0) ;
    normal(2,0) = 1 - intersection(2,0) ;
    normal(3,0) = 0.0 ;

    return normal.normalized() ;
}
    

