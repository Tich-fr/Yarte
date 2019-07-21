#include <iostream>

#include "environment.h"
#include "raytracer.h"
#include "object.h"
#include "color.h"

int main(int argc, char* argv[]) {

    Raytracer* rt = new Raytracer(new XEnvironment(512*1.6, 512)) ;

    Object* o1 = new IPlane(Color(200, 10, 10), 0.8,
                            Color(190, 20, 20), 0.4,
                            Color(180, 30, 30), 0.2,
                            0.35, 1.0) ;
    Object* o2 = new Sphere(Color(20, 200, 20), 0.8,
                            Color(30, 190, 30), 0.4,
                            Color(40, 180, 40), 0.2,
                            0.35, 1.0) ;
    Object* o3 = new Cone(Color(20, 200, 200), 0.8,
                            Color(30, 190, 190), 0.4,
                            Color(40, 180, 180), 0.2,
                            0.35, 1.0) ;

    o2->translate(2, 2, 2) ;
    o3->translate(-2, 2, 2) ;

    rt->add_object(o1) ;
    rt->add_object(o2) ;
    rt->add_object(o3) ;

    rt->show() ;

    delete o1 ;
    delete o2 ;
    delete rt ;

    return 0;
}
