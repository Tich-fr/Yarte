#ifndef COLOR_H
#define COLOR_H

class Color {
public:
    Color(unsigned int rd=0, unsigned int gr=0, unsigned int bl=0);
    Color(const Color& c) ;
    ~Color() ;

    Color operator+ (const Color& c);
    Color operator- (const Color& c);
    Color operator* (const float& value);
    Color& operator= (const Color& c);

    unsigned int red() const ;
    unsigned int green() const ;
    unsigned int blue() const ;

private:
    double r, g, b;

    void limit_sup();
};

#endif // COLOR_H
