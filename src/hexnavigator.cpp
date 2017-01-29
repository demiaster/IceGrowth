#include "hexnavigator.h"
///----------------------------------------------------------------------------
/// @file hexnavigator.cpp
/// @brief implementation files for HexNavigator class
///----------------------------------------------------------------------------

namespace model
{
    HexNavigator::HexNavigator(const std::size_t _width,
                               const std::size_t _height) :
                                m_neighboursdist(0, 5),
                                m_borderdist(0, 2 * (_width + _height)
                                             - 4 /* remove double vertexes */
                                             - 1 /* remove last element because we start from zero */)
    {
        m_width = _width;
        m_height = _height;
    }

    Point HexNavigator::setOnBorder()
    {
        //mapping all the point on the frame of the image
        //to use a contiguous indexing system

        //calculating a random index on the frame of the image
        std::size_t offset = m_borderdist.get_distr();

        //converting from that index to the actual x, y values for the random walker
        Point o_walker = (offset < m_width) ? Point{offset, 0} :
                  (m_width <= offset && offset < m_width + m_height) ? Point{m_width - 1, offset - m_width} :
                  (m_width + m_height <= offset && offset < 2 * m_width + m_height) ?
                                                                           Point{offset - m_width - m_height, m_height - 1} :
                                                                           Point{0, offset - m_width - m_width - m_height};
        return o_walker;
    }

    void HexNavigator::walk(Point& io_walker)
    {
        DiffPoint dp = {0,0};

        DiffPoint (&m_point)[6] = io_walker.x % 2 ? m_point_even : m_point_odd;
        do
        {
            std::size_t val = m_neighboursdist.get_distr();
            dp = m_point[val];
        }
        while ((io_walker.x + dp.x) >= m_width || (io_walker.y + dp.y) >= m_height);
        io_walker.x = io_walker.x + dp.x;
        io_walker.y = io_walker.y + dp.y;
    }

}
