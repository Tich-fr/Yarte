/* PURPOSE : Ray tracing framework

PREREQUISITES : matrix.h, affine.h, color.h
*/

#include <X11/Xlib.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

#include "matrix.h"

// Light pos
#define Lx               6.0
#define Ly               6.0
#define Lz               1.0

// Camera params
#define Near             1.0
#define Far              25.0

#define THETA            45.0
#define ASPECT           1.6

// Height
#define H                512

static object_t object[N_OBJECTS] ;
int nobjects = 0 ;

int debug = 1;

int find_min_hit_time(double t0[N_OBJECTS]) {

    double min_t = DBL_MAX ;
    int position = -1 ;

    for(int i = 0 ; i < nobjects ; i++) {
        if (t0[i] != -1.0) {
            if (t0[i] < min_t) {
                min_t = t0[i] ;
                position = i ;
            }
        }
    }
    return position ;
}

dmatrix_t *ray_direction(camera_t *Camera, window_t *Window, double height, double width, double i, double j) {

    int k ; 
    dmatrix_t *d ;

    d = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(d,3,1) ;

    for (k = 1 ; k <= 3 ; k++) { 
        d->m[k][1] = -1.0*Near*Camera->n.m[k][1] + width*(2.0*i/Window->width - 1.0)*Camera->u.m[k][1] + height*(2.0*j/Window->height - 1.0)*Camera->v.m[k][1] ;
    }

    dmatrix_t* ret = to_homogeneous(d,0.0);
    delete_dmatrix(d);
    return ret; 
}

int shadowed(dmatrix_t *e, dmatrix_t *d) {

    int h, k ;
    double t0[N_OBJECTS] ;

    for (k = 0 ; k < nobjects ; k++) {
        t0[k] = (object[k].intersection)(dmat_mult(&object[k].Minv,e),dmat_normalize(dmat_mult(&object[k].Minv,d))) ;
    }
    h = find_min_hit_time(t0) ;
    return h != -1 ;
}

color_t shade(light_t *light, object_t *object, dmatrix_t *e, dmatrix_t *d, color_t color, color_t background, int level) {

    // find all the intersections
    double tt[nobjects];
    for (int i = 0; i < nobjects; i++) {
        tt[i] = object[i].intersection(dmat_mult(&(object[i].Minv), e), dmat_mult(&(object[i].Minv), d));
    }

    // identify the closest intersection point
    int ind = find_min_hit_time(tt);
    if (ind == -1) // no intersections with any object
        return background;

    // Determine color and intensity of light along the ray from intersection
    object_t *obj = &object[ind];
    dmatrix_t *intersect = intersection_coordinates(dmat_mult(&obj->Minv, e), dmat_mult(&obj->Minv, d), tt[ind]);

    dmatrix_t *S = vector_to_light_source(intersect, &light->position);
    // if it's shadowed just take the ambiant light
    // use epsilon to aoid shadow rounding errors
    if (shadowed(dmat_add(intersect, dmat_scalar_mult(S, EPSILON)), S)) {
        color = obj->ambient_color;
        color.r *= obj->ambient_coeff;
        color.g *= obj->ambient_coeff;
        color.b *= obj->ambient_coeff;

        delete_dmatrix(intersect);
        delete_dmatrix(S);

        return color;
    }

    // else continue the ray (for now the first object is always opaque)
    dmatrix_t *V = vector_to_center_of_projection(intersect, e);
    dmatrix_t *N = obj->normal(intersect);
    dmatrix_t *R = vector_to_specular_reflection(N, S);

    double NS = ddot_product(N, S);
    NS = NS < 0 ? 0 : NS;
    double VR = ddot_product(V, R);
    VR = VR < 0 ? 0 : VR;

    color.r  = obj->diffuse_coeff * obj->diffuse_color.r * NS;
    color.r += obj->specular_coeff * obj->specular_color.r * VR;
    color.r *= light->intensity.r;
    color.r += obj->ambient_coeff * obj->ambient_color.r;

    color.g  = obj->diffuse_coeff * obj->diffuse_color.g * NS;
    color.g += obj->specular_coeff * obj->specular_color.g * VR;
    color.g *= light->intensity.g;
    color.g += obj->ambient_coeff * obj->ambient_color.g;

    color.b  = obj->diffuse_coeff * obj->diffuse_color.b * NS;
    color.b += obj->specular_coeff * obj->specular_color.b * VR;
    color.b *= light->intensity.b;
    color.b += obj->ambient_coeff * obj->ambient_color.b;

    // free temporary matrices
    delete_dmatrix(intersect);
    delete_dmatrix(S);
    delete_dmatrix(V);
    delete_dmatrix(N);
    delete_dmatrix(R);

    return color ;
}

int main() {

    Display *d ;
    Window w ;
    XEvent e ;

    int i, j, s ;

    camera_t Camera ;
    window_t Window ;
    light_t light ;
    dmatrix_t MS1, MS2, MS3, MS4, MC1, MC2, MP, light_position ;
    color_t pixel, background, light_intensity, light_color, ambient_color, diffuse_color, specular_color ;
    double height, width, aspect, ambient_coeff, diffuse_coeff, specular_coeff, f, reflectivity ;

    /* Set the background color */
    background = color_init(25.0,5.0,210.0) ;

    /* Set up light position, intensity, and color */
    dmat_alloc(&light_position,4,1) ;

    light_position.m[X][1] = Lx ;
    light_position.m[Y][1] = Ly ;
    light_position.m[Z][1] = Lz ;
    light_position.m[4][1] = 1.0 ;

    light_intensity = color_init(1.0,1.0,1.0) ;
    light_color = color_init(255.0,255.0,255.0) ; 
    light = *build_light(&light,&light_position,light_color,light_intensity) ;

    /* Build display window and synthetic camera */
    Window = *build_window(&Window,H,ASPECT) ;
    Camera = *build_camera(&Camera,&Window) ;

    /* Build a sphere */
    MS1  = *translate(0.0,0.0,0.0) ; // Id
    
    specular_color = color_init(255.0,255.0,255.0) ;
    diffuse_color = color_init(0.0,0.0,255.0) ;
    ambient_color = color_init(0.0,0.0,255.0) ;

    specular_coeff = 0.5 ;
    diffuse_coeff = 0.4 ;
    ambient_coeff = 0.2 ;

    f = 10.0 ;
    reflectivity = 0.0 ;

    build_object(SPHERE,&MS1,ambient_color,diffuse_color,specular_color,ambient_coeff,diffuse_coeff,specular_coeff,f,reflectivity) ;

    // build a ground
    MP = *translate(0.0, 0.0, -1.0) ;
    diffuse_color = color_init(10.0,130.0,20.0) ;
    ambient_color = color_init(20.0,15.0,10.0) ;
    build_object(INFINITE_PLANE,&MP,ambient_color,diffuse_color,specular_color,ambient_coeff,diffuse_coeff,specular_coeff,f,reflectivity) ;

    /*
    // build other spheres and cones
    MS2 = *translate(3.0, 3.0, 1.0) ;
    diffuse_color = color_init(255.0,0.0,0.0) ;
    ambient_color = color_init(255.0,0.0,0.0) ;
    build_object(SPHERE, &MS2, ambient_color, diffuse_color, specular_color, ambient_coeff, diffuse_coeff, specular_coeff, f, reflectivity) ;

    MS3 = *translate(1.0, 3.0, 1.0) ;
    diffuse_color = color_init(255.0,0.0,255.0) ;
    ambient_color = color_init(255.0,0.0,255.0) ;
    build_object(SPHERE, &MS3, ambient_color, diffuse_color, specular_color, ambient_coeff, diffuse_coeff, specular_coeff, f, reflectivity) ;

    MS4 = *translate(3.0, 1.0, 0.0) ;
    diffuse_color = color_init(255.0,255.0,0.0) ;
    ambient_color = color_init(255.0,255.0,0.0) ;
    build_object(SPHERE, &MS4, ambient_color, diffuse_color, specular_color, ambient_coeff, diffuse_coeff, specular_coeff, f, reflectivity) ;

    MC1 = *translate(3.0, 5.0, 0.5) ;
    diffuse_color = color_init(0.0,255.0,255.0) ;
    ambient_color = color_init(0.0,255.0,255.0) ;
    build_object(CONE, &MC1, ambient_color, diffuse_color, specular_color, ambient_coeff, diffuse_coeff, specular_coeff, f, reflectivity) ;

    */
    MC2 = *translate(5.0, 2.0, 0.5) ;
    diffuse_color = color_init(0.0,255.0,0.0) ;
    ambient_color = color_init(0.0,255.0,0.0) ;
    build_object(CONE, &MC2, ambient_color, diffuse_color, specular_color, ambient_coeff, diffuse_coeff, specular_coeff, f, reflectivity) ;
    // prepare X and the main loop
    aspect = ASPECT ;
    height = Near*tan(M_PI/180.0 * THETA/2.0) ;
    width = height*aspect ;

    dmatrix_t *direction ;

    d = InitX(d,&w,&s,&Window) ;
    XNextEvent(d, &e) ;

    // because Expose event does not always occur on startup, idk why
    int first_time = 1;

    // main loop
    while (1) {
        if (first_time) {
            for (i = 0 ; i < Window.width ; i++) {
                for (j = 0  ; j < Window.height ; j++) {
                    direction = ray_direction(&Camera,&Window,height,width,(double)i,(double)j) ;
                    pixel = shade(&light,object,&Camera.E,direction,pixel,background,3) ;
                    SetCurrentColorX(d,&(DefaultGC(d,s)),(int)pixel.r,(int)pixel.g,(int)pixel.b) ;
                    SetPixelX(d,w,s,i,Window.height - (j + 1)) ;
                    delete_dmatrix(direction) ;
                }
            }

            first_time = 0;
        }

        XNextEvent(d,&e) ;
        if (e.type == KeyPress)
            break ;
        if (e.type == ClientMessage)
            break ;
    }
    QuitX(d,w) ;

    return 0;
}
