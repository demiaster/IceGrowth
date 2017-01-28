#include "squarenavigator.h"

#include "point.h"

namespace model
{
    SquareNavigator::SquareNavigator(const std::size_t _width,
                                     const std::size_t _height) :
                                     m_borderdist(0, 2 * (_width + _height)
                                                  - 4 /* remove double vertexes */
                                                  - 1 /* remove last element because we start from zero */),
                                     m_neighboursdist(0, 7)
    {
        m_width = _width;
        m_height = _height;
    }

    Point SquareNavigator::setOnBorder()
    {
        //mapping all the point on the frame of the image
        //to use a contiguous indexing system

        //calculating a random index on the frame of the image
        std::size_t offset = m_borderdist.get_distr();

        //converting from that index to the actual x, y values for the random walker
        Point walker = (offset < m_width) ? model::Point{offset, 0} :
                  (m_width <= offset && offset < m_width + m_height) ? Point{m_width - 1, offset - m_width} :
                  (m_width + m_height <= offset && offset < 2 * m_width + m_height) ?
                                                                           Point{offset - m_width - m_height, m_height - 1} :
                                                                           Point{0, offset - m_width - m_width - m_height};
        return walker;

    }

    void SquareNavigator::walk(Point& _walker)
    {
        DiffPoint dp = {0,0};
        do
        {
            std::size_t val = m_neighboursdist.get_distr();
            dp = m_neighbour[val];
        }
        while ((_walker.x + dp.x) >= m_width || (_walker.y + dp.y) >= m_height);
        _walker.x = _walker.x + dp.x;
        _walker.y = _walker.y + dp.y;
    }
}
