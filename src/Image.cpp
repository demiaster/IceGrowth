#include "Image.h"
#include <exception>
#include <iostream>

void Image::setPixel(std::size_t _x,
              std::size_t _y,
              unsigned char _r,
              unsigned char _g,
              unsigned char _b)
{
    /*unsigned char colorComponents[m_pixelDepth];

    for (auto i : colorComponents)
    {
        int index = getIndex(_x, _y, i);
    }*/

    m_data[getIndex(_x, _y, 0)] = _r;
    m_data[getIndex(_x, _y, 1)] = _g;
    m_data[getIndex(_x, _y, 2)] = _b;

    return;
}

bool Image::save(std::string _fname)
{
    try
    {
        Magick::Image output(m_width,m_height,"RGB",Magick::CharPixel,m_data.get());
        output.depth(32);
        output.write(_fname);
    }
    catch (std::exception& error_)
    {
        std::cout << "Caught exception: " << error_.what() << '\n';
        return false;
    }

    return true;
}

void Image::clearScreen(unsigned char _r,
                 unsigned char _g,
                 unsigned char _b)
{
    for (unsigned int i = 0; i < m_width; ++i)
    {
        for (unsigned int j = 0; j < m_height; ++j)
        {
            setPixel(i, j, _r, _g, _b);
        }
    }

    return;
}
