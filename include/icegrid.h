#ifndef MODEL_ICEGRID_H
#define MODEL_ICEGRID_H

#include "grid.h"
#include "heatgrid.h"
#include "common.h"
#include "navigator.h"

namespace model
{


    class IceGrid : public Grid<PERCENTAGE, 2>
    {
    public:
        IceGrid(const std::size_t _width,
                const std::size_t _height);
        void freeze(std::size_t x, std::size_t y, PERCENTAGE _percentage);
        template <typename NAVIGATOR>
        PERCENTAGE hit(std::size_t _x, std::size_t _y, NAVIGATOR navigator) const
        {
            Point p = {_x, _y};
            int neighbours = 0;
            PERCENTAGE accum = 0;
            //such lambda, much wow
            navigator->onNeighbours(p, [this, &accum, &neighbours](Point point)
            {
                ++neighbours;
                accum += this->get({{point.x, point.y}});
            });
            return neighbours > 0 ?
                        accum / neighbours : 0;
        }

        void merge(HeatGrid* _heatGrid);
    private:
        std::size_t m_width, m_height;
    };
}
#endif // MODEL_ICEGRID_H
