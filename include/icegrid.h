#ifndef MODEL_ICEGRID_H
#define MODEL_ICEGRID_H

#include "grid.h"
#include "heatgrid.h"
#define PERCENTAGE double

namespace model
{
    class IceGrid : public Grid<PERCENTAGE, 2> {
    public:
        inline IceGrid(const std::size_t _width,
                       const std::size_t _height) :
                       Grid({_width, _height}),
                       m_width(_width),
                       m_height(_height) {;}
        void freeze(std::size_t x, std::size_t y, PERCENTAGE _percentage);

        PERCENTAGE hit(std::size_t _x, std::size_t _y) const;

        // TODO: implement this method
        void merge(HeatGrid& _heatGrid);
    private:
        std::size_t m_width, m_height;
    };
}
#endif // MODEL_ICEGRID_H
