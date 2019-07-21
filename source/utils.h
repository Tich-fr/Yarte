#ifndef UTILS_H
#define UTILS_H

#include "matrix.h"

constexpr double EPSILON = 0.001 ;

Matrix rotated(double x, double y, double z, double angle) ;

Matrix translated(double x, double y, double z) ;

Matrix scaled(double x, double y, double z) ;

/*
 * return the min positive solution of a quadratic, -1 if no solution
 */
double solve_quadratic_min(double a, double b, double c) ;

Matrix vector_a_to_b(const Matrix& a, const Matrix& b) ;

Matrix vector_to_specular_reflection(const Matrix& n, const Matrix& s) ;

Matrix coordinate_on_segment(const Matrix& e, const Matrix& d, double t) ;

#endif // UTILS_H
