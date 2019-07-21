#include "raytracer.h"

// dev includes
#include <iostream>

#include <float.h> // DBL_MAX
#include <cmath>

//TODO : make values for light and background configurable
Raytracer::Raytracer(Environment* env) :
    env(env), light(new Light(Matrix(4,1), Color(80, 80, 10), Color(1, 1, 1))),
    cam(new Camera()), background(125, 125, 125), Near(1.0), Far(25.0), Theta(45.0) {

    H = Near * tan(M_PI/180 * Theta/2) ;
    W = H * env->get_ratio() ;

    light->pos(0,0) = 6.0 ;
    light->pos(1,0) = 6.0 ;
    light->pos(2,0) = 1.0 ;
    light->pos(3,0) = 1.0 ;

    env->init() ;
}

Raytracer::~Raytracer() {

    env->quit() ;

    delete cam ;
    delete light ;
    delete env ;
}

void Raytracer::show() {

    render() ;
    env->show() ;
}

unsigned int Raytracer::add_object( Object *obj ) {

    objects.push_back(obj) ;
    return objects.size() - 1 ;
}

//TODO
void Raytracer::render() {

    Color c ;
    int h = env->get_height() ;
    int w = env->get_width() ;
    int jp ; // is turning upside-down the final rendering

    for (int i = 0; i < w ; i++) {
        for (int j = 0, jp = h-1 ; j < h ; j++, jp--) {
            c = shade(i, j) ;
            env->setPixel(i, jp, c.r, c.g, c.b) ;
        }
    }
}

int Raytracer::find_min_hit_time(double intersect[], int size) {

    double min_t = DBL_MAX ;
    int ind = -1 ;

    for (int i=0 ; i<size ; i++) {
        if (intersect[i] != -1.0 && intersect[i] < min_t) {
            min_t = intersect[i] ;
            ind = i ;
        }
    }

    return ind ;
}

Matrix Raytracer::ray_direction(int i, int j) {

    Matrix d(4,1) ;

    for (int k = 0; k < 3; k++)
        d(k,0) = -1.0*Near*cam->n(k,0) + W*(2.0*i/env->get_width() - 1.0)*cam->u(k,0)
            + H*(2.0*j/env->get_height() - 1.0)*cam->v(k,0) ;
    d(3,0) = 0.0 ;

    return d ;
}

//TODO
bool Raytracer::shadowed(const Matrix& e, const Matrix& d) {

    return false ;
}

//TODO : make recursive after simple lighting done
Color Raytracer::shade(int i, int j) {

    Matrix e = cam->pos ;
    Matrix d = ray_direction(i, j) ;

    // find all intersections
    const int nobj = objects.size() ;
    double intersect[nobj] ;
    for (int i=0 ; i<nobj ; i++) {
        intersect[i] = objects[i]->intersection(e, d) ;
    }

    // get closest intersection points
    int ind = find_min_hit_time(intersect, nobj) ;
    if (ind == -1) // no intersection
        return background ;

    // for now just return the color of the closest object
    return objects[ind]->specular ;
}
