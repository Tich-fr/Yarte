#include "environment.h"

#include <exception>

XEnvironment::XEnvironment(uint w, uint h) : Environment::Environment(w, h) {}

XEnvironment::~XEnvironment()  {}

void XEnvironment::init() {
    display = XOpenDisplay(NULL) ;
    if (display == NULL) {
        throw std::runtime_error("Unable to contact X11 server.") ;

    int posx = 10 ;
    int posy = 10 ;

    screen = DefaultScreen(display) ;
    gc = DefaultGC(display, screen) ;
    window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                 posx, posy, get_width(), get_height(), 1,
                                 BlackPixel(display, screen),
                                 WhitePixel(display, screen)) ;

    Atom del = XInternAtom(display, "WM_DELETE_WINDOW", 0) ;
    XSetWMProtocols(display, window, &del, 1) ;
    XSelectInput(display, window, ExposureMask | KeyPressMask) ;
    
    XMapWindow(display, window) ;

    XStoreName(display, window, "Yet Another RayTracing Engine") ;

    while(true) {
        XNextEvent(display, &event) ;
        if (event.type == Expose)
            break;
    }
}

void XEnvironment::show() {
    while(true) {
        XNextEvent(display, &event) ;
        if (event.type == KeyPress)
            break ;
    }
}

void XEnvironment::setPixel(uint i, uint j, uint r, uint g, uint b) {
    XSetForeground(display, gc, r << 16 | g << 8 | b) ;
    XDrawPoint(display, window, gc, i, j) ;
}

void XEnvironment::clear() {
    XClearWindow(display, window) ;
}

void XEnvironment::quit() {
    XDestroyWindow(display, window) ;
    XCloseDisplay(display) ;
}
