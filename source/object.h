#ifndef OBJECT_H
#define OBJECT_H

#include "matrix.h"
#include "color.h"

class Object {
 public:
    Object(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f) ;
    virtual ~Object() ;

    virtual double intersection(const Matrix& e, const Matrix& d) const = 0 ;
    virtual Matrix normal(const Matrix& intersection) const = 0 ;

    // TODO encapsulate all of that as protected and do getters/setters
    Matrix M, Minv ;
    Color specular, diffuse, ambiant ;
    double specular_coeff, diffuse_coeff, ambiant_coeff ;
    double density, reflectivity, f ;
};

class IPlane : public Object {
 public:
    IPlane(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f) ;

    double intersection(const Matrix& e, const Matrix& d) const ;
    Matrix normal(const Matrix& intersection) const ;
};

class Plane : public Object {
 public:
    Plane(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f) ;

    double intersection(const Matrix& e, const Matrix& d) const ;
    Matrix normal(const Matrix& intersection) const ;
};

class Sphere : public Object {
 public:
    Sphere(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f) ;

    double intersection(const Matrix& e, const Matrix& d) const ;
    Matrix normal(const Matrix& intersection) const ;
};

class Cone : public Object {
 public:
    Cone(const Color& spec, double spec_c, const Color& diff, double diff_c, const Color& amb, double amb_c, double reflect, double f) ;

    double intersection(const Matrix& e, const Matrix& d) const ;
    Matrix normal(const Matrix& intersection) const ;
};

#endif // OBJECT_H
