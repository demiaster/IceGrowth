#ifndef COLOR_H
#define COLOR_H

namespace view
{
union Color
{
    struct
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
    unsigned char array[4];
};
} // end namespace view

#endif // COLOR_H
