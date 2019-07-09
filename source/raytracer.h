#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "light.h"
#include "object.h"
#include "environment.h"
#include "matrix.h"
#include "camera.h"
#include "color.h"

#include <vector>

#define MAX_OBJ 8

class Raytracer {
 public:
    Raytracer(Environment* env) ;
    ~Raytracer() ;

    void show() ;
    
    void set_camera(double x, double y, double z) ;
    
    unsigned int add_object(Object* obj) ;

 private:
    void render() ;
    int find_min_hit_time() ;
    Matrix ray_direction(int i, int j) ;
    bool shadowed(const Matrix& e, const Matrix& d) ;
    Color shade(int obj, const Matrix& e, const Matrix& d, int rec_level) ;
    
    Environment* env ;
    Light* light ;
    Camera* cam ;
    Color background ;
    std::vector<Object*> objects ;
};
    

#endif // RAYTRACER_H
