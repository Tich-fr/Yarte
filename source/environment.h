#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <X11/Xlib.h>

typedef unsigned int uint;

class Environment {
 public:
    Environment(uint w, uint h) : width(w), height(h) {}
    virtual ~Environment() {}

    virtual void init() = 0 ;
    virtual void show() = 0 ;
    virtual void quit() = 0 ;

    virtual void setPixel(uint i, uint j, uint r, uint g, uint b) = 0 ;
    virtual void clear() = 0 ;
    
    uint get_width() const {
        return width ;
    }
    uint get_height() const {
        return height ;
    }
    float get_ratio() const {
        return width / height ;
    }

 protected:
    uint width, height ;
};

class XEnvironment : public Environment {
 public:
    XEnvironment(uint w, uint h) ;
    ~XEnvironment() ;

    void init() ;
    void show() ;
    void quit() ;
    void setPixel(uint i, uint j, uint r, uint g, uint b) ;
    void clear() ;

    using Environment::get_width ;
    using Environment::get_height ;
    using Environment::get_ratio ;

 private:
    Display *display ;
    Window window ;
    XEvent event ;
    GC gc ;
    int screen ;
};

#endif // ENVIRONMENT_H
