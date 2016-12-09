#include "icegrid.h"

#include "image.h"
#include <iostream>
#include <sstream>

#define MIN_TEMP -100.0
#define MAX_TEMP 0.0

namespace model
{
    IceGrid::IceGrid(const std::size_t _width,
                     const std::size_t _height) :
                     Grid(std::array<std::size_t, 2>{{_width, _height}}),
                     m_image(_width, _height)
    {
        m_width = _width;
        m_height = _height;
        m_image.clearScreen(0, 0, 0);
        m_counter = 0;
    }

    void IceGrid::freeze(std::size_t _x, std::size_t _y, PERCENTAGE percentage)
    {
        set({{_x, _y}}, percentage);
        int green = 255 * percentage;
        m_image.setPixel(_x, _y, 0, green, 0);
        std::stringstream ss;
        ss << "icegrid-" << m_counter << ".png";
        m_image.save(ss.str().c_str());
        ++m_counter;
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

    void IceGrid::reset(PERCENTAGE _defval)
    {
        for (size_t i = 0; i < m_width; ++i)
        {
            for (size_t j = 0; j < m_height; ++j)
            {
                set({{i, j}}, _defval);
            }
        }
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
