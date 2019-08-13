#ifndef OBJECT_H
#define OBJECT_H

#include "matrix.h"
#include "color.h"
#include "ray.h"

class Object {
 public:
    Object(const Color& col, double spec_c, double diff_c, double amb_c, double reflect) ;
    virtual ~Object() ;

    virtual double intersect(const Ray& r) const = 0 ;
    virtual Matrix normal(const Matrix& intersection) const = 0 ;

    Object& rotate(double x, double y, double z, double angle) ;
    Object& translate(double x, double y, double z) ;
    Object& scale(double x, double y, double z) ;

    // TODO encapsulate all of that as protected and do getters/setters
    Matrix M, Minv ;
    Color color ;
    double specular_coeff, diffuse_coeff, ambiant_coeff ;
    double reflectivity ;
};

class IPlane : public Object {
 public:
    IPlane(const Color& col, double spec_c, double diff_c, double amb_c, double reflect) ;

    double intersect(const Ray& r) const ;
    Matrix normal(const Matrix& intersection) const ;
};

class Plane : public Object {
 public:
    Plane(const Color& col, double spec_c, double diff_c, double amb_c, double reflect) ;

    double intersect(const Ray& r) const ;
    Matrix normal(const Matrix& intersection) const ;
};

class Sphere : public Object {
 public:
    Sphere(const Color& col, double spec_c, double diff_c, double amb_c, double reflect) ;

    double intersect(const Ray& r) const ;
    Matrix normal(const Matrix& intersection) const ;
};

#endif // OBJECT_H
