#include "color.h"

Color::Color(unsigned int rd, unsigned int gr, unsigned int bl)
    : r((double)rd/255.0), g((double)gr/255.0), b((double)bl/255.0) {}

Color::Color(const Color& c) : r(c.r), g(c.g), b(c.b) {}

Color::~Color() {}

Color Color::operator+ (const Color& c) {

    Color res(r + c.r, g + c.g, b + c.b) ;
    res.limit_sup() ;

    return res ;
}

Color Color::operator* (const float& f) {

    Color res(r*f, g*g, b*f) ;
    res.limit_sup() ;

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

unsigned int Color::red() const {
    return r * 255 ;
}


unsigned int Color::green() const {
    return g * 255 ;
}

unsigned int Color::blue() const {
    return b * 255 ;
}

void Color::limit_sup() {

    r = r>1.0 ? 1.0 : r;
    g = g>1.0 ? 1.0 : g;
    b = b>1.0 ? 1.0 : b;
}
