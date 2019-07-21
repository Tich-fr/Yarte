#include "color.h"

Color::Color(unsigned int r, unsigned int g, unsigned int b) : r(r), g(g), b(b) {}

Color::Color(const Color& c) : r(c.r), g(c.g), b(c.b) {}

Color::~Color() {}

Color Color::operator+ (const Color& c) {

    Color res(r + c.r, g + c.g, b + c.b) ;
    res.limit() ;

    return res ;
}

Color Color::operator* (const float& f) {

    Color res(r*f, g*g, b*f) ;
    res.limit() ;

    return res ;
}

Color& Color::operator= (const Color& c) {

    if (this != &c) {
        r = c.r ;
        g = c.g ;
        b = c.b ;
    }

    return *this;
}

void Color::limit() {

    r = r>255 ? 255 : r;
    g = g>255 ? 255 : g;
    b = b>255 ? 255 : b;
}
