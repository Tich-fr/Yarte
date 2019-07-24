#include "object.h"
#include "utils.h" // define EPSILON, <cmath>, ..

Object::Object(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f) :
    M(Matrix::Id()), Minv(Matrix::Id()), specular(spec), diffuse(diff), ambiant(amb),
    specular_coeff(spec_c), diffuse_coeff(diff_c), ambiant_coeff(amb_c),
    density(1.0), reflectivity(reflect), f(f) {
}

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

IPlane::IPlane(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f)
    : Object(spec, spec_c, diff, diff_c, amb, amb_c, reflect, f) {}

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

    return normal.normalized() ;
}

// Plane

Plane::Plane(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f)
    : Object(spec, spec_c, diff, diff_c, amb, amb_c, reflect, f) {}

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

    return normal.normalized() ;
}

// Sphere

Sphere::Sphere(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f)
    : Object(spec, spec_c, diff, diff_c, amb, amb_c, reflect, f) {}

double Sphere::intersect(const Ray& ray) const {

    Matrix e = (Minv * ray.get_pos()).unhomogenized() ;
    Matrix d = (Minv * ray.get_dir()).unhomogenized() ;

    double a = d.dot(d) ;
    double b = e.dot(d) ;
    double c = e.dot(e) - 1.0 ;

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
