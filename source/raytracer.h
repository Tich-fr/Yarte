#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "light.h"
#include "object.h"
#include "environment.h"
#include "matrix.h"
#include "camera.h"
#include "color.h"
#include "ray.h"

#include <vector>

class Raytracer {
 public:
    explicit Raytracer(Environment* env) ;
    ~Raytracer() ;

    void show() ;
    
    unsigned int add_object(Object* obj) ;

 private:
    void render() ;
    Ray ray_at_pixel(int i, int j) ;
    bool shadowed(const Matrix& pos) ;
    double closest_intersection(const Ray& r, Object **o) ;
    Color shade(const Ray& ray) ;
    
    Environment* env ;
    Light* light ;
    Camera* cam ;
    Color background ;
    std::vector<Object*> objects ;
    double Near, Theta, W, H ;
};
    

#endif // RAYTRACER_H
