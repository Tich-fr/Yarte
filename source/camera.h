#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"

class Camera {
 public:
    Camera() ;
    ~Camera() ;
    
    //TODO : make private and getters/setters ..
    Matrix up ;
    Matrix pos ;
    Matrix gaze ;
    Matrix u, v, n ;
};

#endif // CAMERA_H
