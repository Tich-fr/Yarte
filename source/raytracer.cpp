#include "raytracer.h"
#include "utils.h"

#include <float.h> // DBL_MAX
#include <cmath>

//TODO : make values for light and background configurable
Raytracer::Raytracer(Environment* env) :
    env(env), light(new Light(Matrix(4,1), Color(1.0, 1.0, 1.0), Color(0.2, 0.2, 0.2))),
    cam(new Camera()), background(0, 0, 0), Near(1.0), Theta(45.0) {

    H = Near * tan(M_PI/180 * Theta/2) ;
    W = H * env->get_ratio() ;

    light->pos(0,0) = 2.0 ;
    light->pos(1,0) = 3.0 ;
    light->pos(2,0) = 4.0 ;
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
            c = shade(ray_at_pixel(i, j), 1) ;
            env->setPixel(i, j, c.red(), c.green(), c.blue()) ;
        }
    }
}

Ray Raytracer::ray_at_pixel(int i, int j) {

    Matrix d(4,1) ;

    for (int k = 0; k < 3; k++)
        d(k,0) = -1.0*Near*cam->n(k,0) + W*(2.0*i/env->get_width() - 1.0)*cam->u(k,0)
            + H*(2.0*j/env->get_height() - 1.0)*cam->v(k,0) ;
    d(3,0) = 0.0 ;

    return Ray(cam->pos, d.normalized()) ;
}

bool Raytracer::shadowed(const Matrix& pos) {

    Ray pos_to_light(pos, vector_a_to_b(pos, light->pos)) ;

    // prevent shadowing acne
    pos_to_light.shift(EPSILON) ;
    
    const int nobj = objects.size() ;
    for (int i=0 ; i<nobj ; i++)
        if (objects[i]->intersect(pos_to_light) > 0)
            return true ;
    
    return false ;
}

double Raytracer::closest_intersection(const Ray& r, Object **o) {

    double intersection = DBL_MAX ;
    double tmp ;
    *o = nullptr ;
    const int nobj = objects.size() ;
    for (int k=0 ; k<nobj ; k++) {
        tmp = objects[k]->intersect(r) ;
        if (tmp >= 0.0 && tmp < intersection) {
            intersection = tmp ;
            *o = objects[k] ;
        }
    }

    // no intersection ?
    if (intersection == DBL_MAX)
        return -1.0 ;

    return intersection ;
}

//TODO opacity, atmoshpere (effect of the distance on the light)
Color Raytracer::shade(const Ray& ray, int level) {

    Object* nearest ;
    double t = closest_intersection(ray, &nearest) ;
    
    if (t < 0.0 || nearest == nullptr)
        return background ;
    
    Matrix intersection = ray.position_at(t) ;
    Matrix to_light = vector_a_to_b(intersection, light->pos, false).unhomogenized() ;
    Matrix to_cam = vector_a_to_b(intersection, cam->pos, false).unhomogenized() ;
    Matrix normal = nearest->normal(intersection).unhomogenized() ;
    Matrix reflected = vector_to_specular_reflection(normal, to_light, false) ;
    
    Color local = nearest->color * phong(intersection, to_light, to_cam,
                                         normal, reflected, nearest) ;

    if (level <= 0 || nearest->reflectivity < 0.0)
        return local ;
    
    // Reflectivity
    Ray next_ray = Ray(intersection,reflected.homogenized(1)) ;
    next_ray.shift(EPSILON) ;
    Color reflection = shade(next_ray, --level) ;

    return local*(1-nearest->reflectivity) + reflection*nearest->reflectivity ;
}

Color Raytracer::phong(const Matrix& intersection, const Matrix& to_light, const Matrix& to_cam,
                       const Matrix& normal, const Matrix& reflected, Object *nearest) {

    // shadow
    // sum if multiple ambiant lights
    if(shadowed(intersection))
        return light->ambiant ;
    
    Color intensity ;

    // ambiant
    // sum if multiple ambiant lights
    intensity = light->ambiant ;

    // diffuse
    double diffuse_coef = normal.dot(to_light) ;
    if (diffuse_coef > 0.0) {
        diffuse_coef /= to_light.norm() ;
        intensity = intensity + light->intensity*diffuse_coef ;
    }

    // specular
    double spec_coef = reflected.dot(to_cam) ;
    if (spec_coef > 0.0 ) {
        spec_coef = pow(spec_coef/(reflected.norm() * to_cam.norm()), 50) ;
        intensity = intensity +light->intensity*spec_coef ;
    }

    return intensity ;
}
