#include "hexnavigator.h"
#include "point.h"

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

    model::Point HexNavigator::setOnBorder()
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

    void HexNavigator::walk(model::Point& _walker)
    {
        DiffPoint dp = {0,0};
        DiffPoint[5]& m_point = walker.x % 2 ? m_point_even : m_point_odd;
        do
        {
            std::size_t val = m_neighboursdist.get_distr();
            dp = m_point[val];
        }
        while ((_walker.x + dp.x) >= m_width || (_walker.y + dp.y) >= m_height);
        _walker.x = _walker.x + dp.x;
        _walker.y = _walker.y + dp.y;
    }

    //    void diffuseOnAxis()
    //    {;}

}
