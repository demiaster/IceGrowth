#include "hexnavigator.h"
#include "point.h"

namespace model
{
    HexNavigator::HexNavigator(const std::size_t _width,
                               const std::size_t _height) :
                                         common::RandomDist(_width, _height)
    {
        m_width = _width;
        m_height = _height;
    }

    model::Point HexNavigator::setOnBorder()
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

    void HexNavigator::walk(model::Point& _walker)
    {

    }

    //    void diffuseOnAxis()
    //    {;}

    bool HexNavigator::isFreezable(const float _probability)
    {
        if(_probability > pdistrib(eng))
        {
            return true;
        }
        return false;
    }
}
