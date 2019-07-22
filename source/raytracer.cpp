#include "raytracer.h"
#include "utils.h"

#include <float.h> // DBL_MAX
#include <cmath>

//TODO : make values for light and background configurable
Raytracer::Raytracer(Environment* env) :
    env(env), light(new Light(Matrix(4,1), Color(80, 80, 10), Color(1, 1, 1))),
    cam(new Camera()), background(0, 0, 0), Near(1.0), Theta(45.0) {

    H = Near * tan(M_PI/180 * Theta/2) ;
    W = H * env->get_ratio() ;

    light->pos(0,0) = 8.0 ;
    light->pos(1,0) = 5.0 ;
    light->pos(2,0) = 5.0 ;
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

void Raytracer::render() {

    Color c ;
    int h = env->get_height() ;
    int w = env->get_width() ;

    for (int i = 0; i < w ; i++) {
        for (int j = 0 ; j < h ; j++) {
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

    Matrix d(4,1) ;

    for (int k = 0; k < 3; k++)
        d(k,0) = -1.0*Near*cam->n(k,0) + W*(2.0*i/env->get_width() - 1.0)*cam->u(k,0)
            + H*(2.0*j/env->get_height() - 1.0)*cam->v(k,0) ;
    d(3,0) = 0.0 ;

    return d.normalized() ;
}

bool Raytracer::shadowed(const Matrix& e, const Matrix& d) {

    Matrix e_shifted = e + (d * EPSILON) ; // prevent shadowing acne
    const int nobj = objects.size() ;
    for (int i=0 ; i<nobj ; i++)
        if (objects[i]->intersection(e_shifted, d) > 0)
            return true ;
    
    return false ;
}

Color Raytracer::shade(int i, int j) {

    Matrix e = cam->pos ;
    Matrix d = ray_direction(i, j) ;

    // find closest intersections
    double intersection = DBL_MAX ;
    double tmp ;
    Object* nearest ;
    const int nobj = objects.size() ;
    for (int k=0 ; k<nobj ; k++) {
        tmp = objects[k]->intersection(e, d) ;
        if (tmp >= 0.0 && tmp < intersection) {
            intersection = tmp ;
            nearest = objects[k] ;
        }
    }

    // no intersection ?
    if (intersection == DBL_MAX)
        return background ;

    Matrix pos_intersection = coordinate_on_segment(e, d, intersection) ;

    // shadowed or not ?
    // TODO : does not work, nothing is in shadow
    if (shadowed(pos_intersection, vector_a_to_b(pos_intersection, light->pos)))
        return nearest->ambiant ;
    
    // for now just return the color of the closest object
    return nearest->specular ;

    //TODO opacity
    //TODO reflectivity
}
