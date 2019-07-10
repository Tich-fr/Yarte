#include "raytracer.h"

// dev includes
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include <float.h> // DBL_MAX

//TODO : make values for light and background configurable
Raytracer::Raytracer(Environment* env) :
    env(env), light(new Light(Matrix(4,1), Color(80, 80, 10), Color(1, 1, 1))),
    cam(new Camera()), background(125, 125, 125), Near(1.0), Far(25.0), Theta(45.0) {

    light->pos(0,0) = 6.0 ;
    light->pos(1,0) = 6.0 ;
    light->pos(2,0) = 1.0 ;
    light->pos(3,0) = 1.0 ;

    env->init() ;
}

Raytracer::~Raytracer() {

    env->quit() ;

    delete env ;
    delete light ;
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

    srand(time(NULL)) ;

    Color c ;

    for (int i = 0; i < env->get_width() ; i++) {
        for (int j = 0; j < env->get_height() ; j++) {
            c = shade(i, j) ;
            env->setPixel(i, j, c.r, c.g, c.b) ;
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

    Matrix d(3,1) ;
    double height = env->get_height() ;
    double width = env->get_width() ;
    double aspect = env->get_ratio() ;

    for (int k = 0; k < 3; k++)
        d(k,0) = -1.0*Near*cam->n(k,0) + width*(2.0*i/width - 1.0)*cam->u(k,0)
            + height*(2.0*j/height - 1.0)*cam->v(k,0) ;

    return d.homogenized(0.0) ;
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
        intersect[i] = objects[i]->intersection(objects[i]->Minv * e, objects[i]->Minv * d) ;
    }

    // get closest intersection points
    int ind = find_min_hit_time(intersect, nobj) ;
    if (ind == -1) // no intersection
        return background ;

    // for now just return the color of the closest object
    return objects[ind]->specular ;
}
