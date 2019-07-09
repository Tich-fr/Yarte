#include "camera.h"

#define Ex               10.0
#define Ey               10.0
#define Ez               5.0

#define Gx               0.0
#define Gy               0.0
#define Gz               -1.0

#define UPx              0.0
#define UPy              0.0
#define UPz              1.0

Camera::Camera() : up(4,1), pos(4,1), gaze(4,1), u(4,1), v(4,1), n(4,1) {

    // TODO : do not use fixed values
    pos(0,0) = Ex ;
    pos(1,0) = Ey ;
    pos(2,0) = Ez ;
    pos(3,0) = 1.0 ;

    gaze(0,0) = Gx ;
    gaze(1,0) = Gy ;
    gaze(2,0) = Gz ;
    gaze(3,0) = 1.0 ;

    up(0,0) = UPx ;
    up(1,0) = UPy ;
    up(2,0) = UPz ;
    up(3,0) = 1.0 ;

    n = (pos - gaze).normalized() ;
    u = up.cross(n).normalized() ;
    v = n.cross(u).normalized() ;
}

Camera::~Camera() {}
