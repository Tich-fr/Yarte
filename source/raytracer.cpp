#include "raytracer.h"

// dev includes
#include <time.h>
#include <stdlib.h>

//TODO : make values for light and background configurable
Raytracer::Raytracer(Environment* env) :
    env(env), light(new Light(Matrix(4,1), Color(80, 80, 10), Color(1, 1, 1))),
    cam(nullptr), background(250, 250, 250) {

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

//TODO : make it more configurable
void Raytracer::set_camera(double x, double y, double z) {

}

unsigned int Raytracer::add_object( Object *obj ) {

    objects.push_back(obj) ;
    return objects.size() - 1 ;
}

//TODO
void Raytracer::render() {

    srand(time(NULL)) ;
    for (int i = 0; i < env->get_width() ; i++) {
        for (int j = 0; j < env->get_height() ; j++) {
            env->setPixel(i, j, rand()%255, rand()%255, rand()%255) ;
        }
    }
}

//TODO
int Raytracer::find_min_hit_time() {

    return 0 ;
}

//TODO
Matrix Raytracer::ray_direction(int i, int j) {

    return Matrix(4,1) ;
}

//TODO
bool Raytracer::shadowed(const Matrix& e, const Matrix& d) {

    return false ;
}

//TODO
Color Raytracer::shade(int obj, const Matrix& e, const Matrix& d, int rec_level) {

    return Color(125, 125, 125) ;
}
