#include "squarenavigator.h"

#include "point.h"

namespace model
{
    SquareNavigator::SquareNavigator(const std::size_t _width,
                                     const std::size_t _height,
                                     common::RandomDist& _randomdist) :
                                     m_randomdist(_randomdist)
    {
        m_width = _width;
        m_height = _height;
    }

    model::Point SquareNavigator::setOnBorder()
    {
        //mapping all the point on the frame of the image
        //to use a contiguous indexing system

        //calculating a random index on the frame of the image
        std::size_t offset = m_randomdist.get_offdistr();

        //converting from that index to the actual x, y values for the random walker
        model::Point walker = (offset < m_width) ? model::Point{offset, 0} :
                  (m_width <= offset && offset < m_width + m_height) ? model::Point{m_width - 1, offset - m_width} :
                  (m_width + m_height <= offset && offset < 2 * m_width + m_height) ?
                                                                           model::Point{offset - m_width - m_height, m_height - 1} :
                                                                           model::Point{0, offset - m_width - m_width - m_height};
        return walker;

    }

    void SquareNavigator::walk(model::Point& _walker)
    {
        long int dx, dy;
        do
        {
            dx = m_randomdist.get_distr();
            dy = m_randomdist.get_distr();
        }
        while ((_walker.x + dx) >= m_width || (_walker.y + dy) >= m_height);
        _walker.x = _walker.x + dx;
        _walker.y = _walker.y + dy;
    }

//    void diffuseOnAxis()
//    {;}

}
