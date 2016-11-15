#include "Image.h"
#include <exception>
#include <iostream>

namespace view {

void Image::setPixel(std::size_t _x,
              std::size_t _y,
              unsigned char _r,
              unsigned char _g,
              unsigned char _b)
{
    set({_x, _y, 0}, _r);
    set({_x, _y, 1}, _g);
    set({_x, _y, 2}, _b);

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

bool Image::hit(const std::size_t _x, const std::size_t _y,
                const unsigned char _r,
                const unsigned char _g,
                const unsigned char _b) const
{
    for (int i = -1; i <= 1; ++i)
    {
        //std::cout << "i: " <<  i << "\n";
        for (int j = -1; j <= 1; ++j)
        {
            std::size_t nx = _x + i;
            std::size_t ny = _y + j;
            //std::cout << "X: " <<  nx << "\n";
            if (nx < W && ny < H ) {
                if (get({nx, ny, 0}) == _r &&
                    get({nx, ny, 1}) == _g &&
                    get({nx, ny, 2}) == _b)
                {
                    std::cout << "X: " <<  nx << "Y: " <<  ny <<"\n";
                    return true;
                }
            }
        }
    }
    return false;
}

}
