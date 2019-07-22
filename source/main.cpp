#include <iostream>

#include "environment.h"
#include "raytracer.h"
#include "object.h"
#include "color.h"

int main(int argc, char* argv[]) {

    Raytracer* rt = new Raytracer(new XEnvironment(512*1.6, 512)) ;

    Object* o1 = new IPlane(Color(255, 60, 60), 0.8,
                            Color(190, 20, 20), 0.4,
                            Color(173, 42, 42), 0.2,
                            0.35, 1.0) ;
    Object* o2 = new Sphere(Color(60, 255, 60), 0.8,
                            Color(30, 190, 30), 0.4,
                            Color(42, 173, 42), 0.2,
                            0.35, 1.0) ;

    o1->translate( 0, 0, -1) ;
    o2->translate( 0, 0,  1) ;

    rt->add_object(o1) ;
    rt->add_object(o2) ;

    rt->show() ;

    delete o1 ;
    delete o2 ;
    delete rt ;

    return 0;
}
