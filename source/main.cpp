#include <iostream>

#include "environment.h"
#include "raytracer.h"
#include "object.h"
#include "color.h"

int main(int argc, char* argv[]) {

    Raytracer* rt = new Raytracer(new XEnvironment(512, 512)) ;

    rt->set_camera(5, 5, 5) ;

    Object* sphere = new Sphere(Color(250, 10, 10), 0.8,
                                Color(240, 20, 20), 0.4,
                                Color(230, 30, 30), 0.2,
                                0.35, 1.0) ;
    rt->add_object(sphere) ;

    rt->show() ;

    delete sphere ;
    delete rt ;

    return 0;
}
