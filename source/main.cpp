#include <iostream>

#include "environment.h"
#include "raytracer.h"
#include "object.h"
#include "color.h"

int main(int argc, char* argv[]) {

    Raytracer* rt = new Raytracer(new XEnvironment(512*1.6, 512)) ;

    Object* o1 = new IPlane(Color(255, 60, 60), 1.5, 1.0, 0.6, 1.0) ;
    Object* o2 = new Sphere(Color(30, 200, 30), 1.8, 1.0, 0.6, 1.0) ;
    Object* o4 = new Sphere(Color(60, 60, 255), 1.8, 1.0, 0.6, 10.0) ;

    o1->translate( 0, 0, -1) ;
    o2->translate( 0, 2,  1) ;
    o4->translate( 0, -2,  1) ;

    rt->add_object(o1) ;
    rt->add_object(o2) ;
    rt->add_object(o4) ;

    rt->show() ;

    delete o1 ;
    delete o2 ;
    delete o4 ;
    delete rt ;

    return 0;
}
