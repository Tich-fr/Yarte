#include <iostream>

#include "environment.h"
#include "raytracer.h"
#include "object.h"
#include "color.h"

int main(int argc, char* argv[]) {

    Raytracer* rt = new Raytracer(new XEnvironment(512, 512)) ;

    Object* sphere = new Sphere(Color(200, 10, 10), 0.8,
                                Color(190, 20, 20), 0.4,
                                Color(180, 30, 30), 0.2,
                                0.35, 1.0) ;

    // TODO improve exceptions management
    //try {

        rt->add_object(sphere) ;
        rt->show() ;
        
        //} catch (const char* msg) {

        //std::cerr << msg << std::endl ;

        //}

    delete sphere ;
    delete rt ;

    return 0;
}
