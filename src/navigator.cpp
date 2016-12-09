#include "navigator.h"

#include "point.h"

namespace model
{
    Navigator::Navigator(std::size_t _width,
                         std::size_t _height) :
                                         eng(rd()),
                                         distr(-1, 1),
                                         offdistr(0, 2 * (_width + _height) - 4),
                                         pdistrib(0, 1.0)
    {
        m_width = _width;
        m_height = _height;
    }

    model::Point Navigator::setOnBorder()
    {
        //mapping all the point on the frame of the image
        //to use a contiguous indexing system

        //calculating a random index on the frame of the image
        std::size_t offset = offdistr(eng);

        //converting from that index to the actual x, y values for the random walker
        model::Point walker = (offset < m_width) ? model::Point{offset, 0} :
                  (m_width <= offset && offset < m_width + m_height) ? model::Point{m_width - 1, offset - m_width} :
                  (m_width + m_height <= offset && offset < 2 * m_width + m_height) ?
                                                                           model::Point{offset - m_width - m_height, m_height - 1} :
                                                                           model::Point{0, offset - m_width - m_width - m_height};
        return walker;

    }

    bool Navigator::walk(model::Point& _walker)
    {


           long int t = distr(eng);
           _walker.x = _walker.x + t;
           t = distr(eng);
           _walker.y = _walker.y + t;
           if(_walker.x >= m_width || _walker.y >= m_height)
           {
               return false;
           }

           return true;
//           while (!(_walker.x + t < m_width))
//           {
//                    t = distr(eng);
//           }
//           _walker.x = _walker.x + t;

//           while (!(_walker.y + t < m_height))
//           {
//                t = distr(eng);
//           }
//           _walker.y = _walker.y + t;

    }

    bool Navigator::isFreezable(double _probability)
    {
        if (_probability > pdistrib(eng))
        {
            return true;
        }
        return false;

    }

}