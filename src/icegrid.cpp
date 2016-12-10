#include "icegrid.h"

#define MIN_TEMP -100.0
#define MAX_TEMP 0.0

namespace model
{
    IceGrid::IceGrid(const std::size_t _width,
                     const std::size_t _height) :
                     Grid(std::array<std::size_t, 2>{{_width, _height}})
    {
        m_width = _width;
        m_height = _height;
    }

    void IceGrid::freeze(std::size_t x, std::size_t y, PERCENTAGE percentage)
    {
        set({{x, y}}, percentage);
    }

    PERCENTAGE IceGrid::hit(std::size_t x, std::size_t y) const
    {
        int neighbours = 0;
        PERCENTAGE accum = 0;
        for (int i = -1; i <= 1; ++i)
        {
            //std::cout << "i: " <<  i << "\n";
            for (int j = -1; j <= 1; ++j)
            {
                std::size_t nx = x + i;
                std::size_t ny = y + j;
                //std::cout << "X: " <<  nx << "\n";
                if (nx < m_width && ny < m_height ) {
                    ++neighbours;
                    accum += get({{nx, ny}});
                }
            }
        }
        return neighbours > 0 ?
                    accum / neighbours : 0;
    }

    void IceGrid::merge(HeatGrid &heatGrid)
    {
        for (std::size_t i = 0; i < m_width; ++i)
        {
            for (std::size_t j = 0; j < m_height; ++j)
            {
                NUMBER temp = heatGrid.getTemperature(i, j);
                this->set({{i, j}}, temp - MIN_TEMP / (MAX_TEMP - MIN_TEMP));
            }
        }
    }
}
