#include "color.h"

Color::Color(int rd, int gr, int bl)
    : r((double)rd/255.0), g((double)gr/255.0), b((double)bl/255.0) {}

Color::Color(double rd, double gr, double bl)
    : r(rd), g(gr), b(bl) {}

Color::Color(const Color& c) : r(c.r), g(c.g), b(c.b) {}

Color::~Color() {}

Color Color::operator+ (const Color& c) const {

    return Color(r + c.r, g + c.g, b + c.b) ;
}

Color Color::operator* (double f) const {

    return Color(r*f, g*f, b*f) ;
}

Color Color::operator* (const Color& c) const {
        
    return Color(r*c.r, g*c.g, b*c.b) ;
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
    return r > 1.0 ? 255 : r * 255 ;
}


unsigned int Color::green() const {
    return g > 1.0 ? 255 : g * 255 ;
}

unsigned int Color::blue() const {
    return b > 1.0 ? 255 : b * 255 ;
}

std::ostream& operator<<(std::ostream& out, const Color& c) {

    out << "{ " << c.r << " " << c.g << " " << c.b << " }" ;
    return out ;
}
