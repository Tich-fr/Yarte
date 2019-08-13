#include <iostream>

#include "environment.h"
#include "raytracer.h"
#include "object.h"
#include "color.h"

int main(int argc, char* argv[]) {

    Raytracer* rt = new Raytracer(new XEnvironment(512*1.6, 512)) ;

    Object* o1 = new IPlane(Color(100, 100, 50), 1.5, 1.0, 0.6, 0.5) ;
    Object* o2 = new Sphere(Color(125, 200, 125), 1.8, 1.0, 0.6, 0.0) ;
    Object* o3 = new Sphere(Color(200, 125, 125), 1.8, 1.0, 0.6, 0.99) ;
    Object* o4 = new Sphere(Color(125, 125, 200), 1.8, 1.0, 0.6, 0.25) ;

    o1->translate( 0, 0, -1) ;
    o2->translate( 3.5, 0, 0) ;
    o3->translate( 4.5, 2, 0) ;
    o4->translate( 4.5,-2, 0) ;

    rt->add_object(o1) ;
    rt->add_object(o2) ;
    rt->add_object(o3) ;
    rt->add_object(o4) ;

    rt->show() ;

    delete o1 ;
    delete o2 ;
    delete o3 ;
    delete o4 ;
    delete rt ;

    return 0;
}
