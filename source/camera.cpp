#include "camera.h"

// pos
constexpr double Ex = 10.0 ;
constexpr double Ey = 10.0 ;
constexpr double Ez = 5.0 ;

// gaze
constexpr double Gx = -2.0 ;
constexpr double Gy = -2.0 ;
constexpr double Gz = -1.0 ;

// up
constexpr double UPx = 0.0 ;
constexpr double UPy = 0.0 ;
constexpr double UPz = 1.0 ;

// TODO : do not use fixed values
Camera::Camera() : up(3,1), pos(3,1), gaze(3,1), u(3,1), v(3,1), n(3,1) {

    pos(0,0) = Ex ;
    pos(1,0) = Ey ;
    pos(2,0) = Ez ;

    gaze(0,0) = Gx ;
    gaze(1,0) = Gy ;
    gaze(2,0) = Gz ;

    up(0,0) = UPx ;
    up(1,0) = UPy ;
    up(2,0) = UPz ;

    n = (pos - gaze).normalized() ;
    u = up.cross(n).normalized() ;
    v = n.cross(u).normalized() ;

    up.homogenize() ;
    pos.homogenize() ;
    gaze.homogenize() ;
    u.homogenize() ;
    v.homogenize() ;
    n.homogenize() ;

}

Camera::~Camera() {}
