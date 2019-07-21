#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "light.h"
#include "object.h"
#include "environment.h"
#include "matrix.h"
#include "camera.h"
#include "color.h"

#include <vector>

constexpr int MAX_OBJ = 8 ;

class Raytracer {
 public:
    explicit Raytracer(Environment* env) ;
    ~Raytracer() ;

    void show() ;
    
    unsigned int add_object(Object* obj) ;

 private:
    void render() ;
    int find_min_hit_time(double intersect[], int size) ;
    Matrix ray_direction(int i, int j) ;
    bool shadowed(const Matrix& e, const Matrix& d) ;
    Color shade(int i, int j) ;
    
    Environment* env ;
    Light* light ;
    Camera* cam ;
    Color background ;
    std::vector<Object*> objects ;
    double Near, Theta, W, H ;
};
    

#endif // RAYTRACER_H
