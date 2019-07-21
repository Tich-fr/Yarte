#ifndef COLOR_H
#define COLOR_H

class Color {
    public:
        Color(unsigned int r=0, unsigned int g=0, unsigned int b=0);
        Color(const Color& c) ;

        Color operator+ (const Color& c);
        Color operator- (const Color& c);
        Color operator* (const float& value);
        Color& operator= (const Color& c);

        unsigned int r, g, b;
    private:
        void limit();
};

#endif // COLOR_H
