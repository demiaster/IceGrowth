#ifndef MODEL_ICEGRID_H
#define MODEL_ICEGRID_H

#include "grid.h"
#include "heatgrid.h"
#define PERCENTAGE double

namespace model
{
    class IceGrid : public Grid<PERCENTAGE, 2> {
    public:
        inline IceGrid(const std::size_t width,
                       const std::size_t height) :
                       Grid({width, height}),
                       m_width(width),
                       m_height(height) {;}
        void freeze(std::size_t x, std::size_t y, PERCENTAGE percentage);

        PERCENTAGE hit(std::size_t x, std::size_t y) const;

        // TODO: implement this method
        void merge(HeatGrid& heatGrid);
    private:
        std::size_t m_width, m_height;
    };
}
#endif // MODEL_ICEGRID_H
