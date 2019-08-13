#include "object.h"
#include "utils.h" // define EPSILON, <cmath>, ..

Object::Object(const Color& col, double spec_c, double diff_c, double amb_c, double reflect) :
    M(Matrix::Id()), Minv(Matrix::Id()), color(col),
    specular_coeff(spec_c), diffuse_coeff(diff_c), ambiant_coeff(amb_c),
    reflectivity(reflect)
{}

Object::~Object() {}

Object& Object::rotate(double x, double y, double z, double angle) {

    M = rotated(x,y,z,angle) * M ;
    Minv = M.inversed() ;

    return *this ;
}

Object& Object::translate(double x, double y, double z) {

    M = translated(x,y,z) * M ;
    Minv = M.inversed() ;

    return *this ;
}

Object& Object::scale(double x, double y, double z) {

    M = scaled(x,y,z) * M ;
    Minv = M.inversed() ;

    return *this ;
}

// Infinite plane

IPlane::IPlane(const Color& col, double spec_c, double diff_c, double amb_c, double reflect)
    : Object(col, spec_c, diff_c, amb_c, reflect) {}

double IPlane::intersect(const Ray& ray) const {

    Matrix e = Minv * ray.get_pos() ;
    Matrix d = Minv * ray.get_dir() ;

    if (fabs(d(2,0)) < EPSILON) // too small
        return -1.0 ;

    double t = -1.0 * e(2,0) / d(2,0) ;
    return t<=0.0 ? -1.0 : t ;
}

Matrix IPlane::normal(const Matrix& intersection) const {

    Matrix normal(4,1) ;

    normal(0,0) = 0.0 ;
    normal(1,0) = 0.0 ;
    normal(2,0) = 1.0 ;
    normal(3,0) = 0.0 ;

    return normal ;
}

// Plane

Plane::Plane(const Color& col, double spec_c, double diff_c, double amb_c, double reflect)
    : Object(col, spec_c, diff_c, amb_c, reflect) {}

double Plane::intersect(const Ray& ray) const {

    Ray r(Minv*ray.get_pos(), Minv*ray.get_dir()) ;

    if (fabs(r.get_dir()(2,0)) < EPSILON)
        return -1.0 ;

    double t = -r.get_pos()(2,0) / r.get_dir()(2,0) ;
    if (t <= 0.0)
        return -1.0 ;

    Matrix i = r.position_at(t) ;
    return ((fabs(i(0,0)) > 1.0) || (fabs(i(1,0)) > 1.0)) ? -1.0 : t ;
}

Matrix Plane::normal(const Matrix& intersection) const {

    Matrix normal(4,1) ;

    normal(0,0) = 0.0 ;
    normal(1,0) = 0.0 ;
    normal(2,0) = 1.0 ;
    normal(3,0) = 0.0 ;

    return normal ;
}

// Sphere

Sphere::Sphere(const Color& col, double spec_c, double diff_c, double amb_c, double reflect)
    : Object(col, spec_c, diff_c, amb_c, reflect) {}

double Sphere::intersect(const Ray& ray) const {

    Matrix e = (Minv * ray.get_pos()).unhomogenized() ;
    Matrix d = (Minv * ray.get_dir()).unhomogenized() ;

    double a = d.dot(d) ;
    double b = e.dot(d) ;
    double c = e.dot(e) - 1.0 ;

    return solve_quadratic_min(a, b, c) ;
}

Matrix Sphere::normal(const Matrix& intersection) const {

    Matrix res(4,1) ;
    Matrix center(3,1) ;

    center(0,0) = M(0,3) ;
    center(1,0) = M(1,3) ;
    center(2,0) = M(2,3) ;

    res(0,0) = intersection(0,0) - center(0,0) ;
    res(1,0) = intersection(1,0) - center(1,0) ;
    res(2,0) = intersection(2,0) - center(2,0) ;
    res(3,0) = 0.0 ;

    return res.normalized() ;
}
