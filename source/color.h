#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color {
public:
    explicit Color(int rd=0, int gr=0, int bl=0) ;
    explicit Color(double rd, double gr, double bl) ;
    Color(const Color& c) ;
    ~Color() ;

    Color operator+ (const Color& c) const ;
    Color operator* (double value) const ;
    Color operator* (const Color& c) const ;
    Color& operator= (const Color& c) ;

    unsigned int red() const ;
    unsigned int green() const ;
    unsigned int blue() const ;

    friend std::ostream& operator<<(std::ostream& out, const Color& c) ;

private:
    double r, g, b;
};

#endif // COLOR_H
