#include "image.h"
#include <exception>
#include <iostream>

namespace view
{

    void Image::setPixel(const std::size_t _x,
                  const std::size_t _y,
                  const unsigned char _r,
                  const unsigned char _g,
                  const unsigned char _b,
                  const unsigned char _a)
    {
        set({{_x, _y, 0}}, _r);
        set({{_x, _y, 1}}, _g);
        set({{_x, _y, 2}}, _b);
        set({{_x, _y, 3}}, _a);

        return;
    }

    bool Image::save(const std::string _fname)
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

    void Image::clearScreen(const unsigned char _r,
                            const unsigned char _g,
                            const unsigned char _b,
                            const unsigned char _a)
    {
        for (unsigned int i = 0; i < m_width; ++i)
        {
            for (unsigned int j = 0; j < m_height; ++j)
            {
                setPixel(i, j, _r, _g, _b, _a);
            }
        }

        return;
    }
}
