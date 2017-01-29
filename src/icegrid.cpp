#include "icegrid.h"
///----------------------------------------------------------------------------
/// @file icegrid.cpp
/// @brief implementation files for IceGrid class
///----------------------------------------------------------------------------

#define NOICE_TEMP 1.0

namespace model
{
    IceGrid::IceGrid(const std::size_t _width,
                     const std::size_t _height) :
                     Grid(std::array<std::size_t, 2>{{_width, _height}})
    {
        m_width = _width;
        m_height = _height;
    }

    void IceGrid::freeze(std::size_t _x, std::size_t _y, PERCENTAGE _percentage)
    {
        set({{_x, _y}}, _percentage);
    }

    void IceGrid::merge(HeatGrid* _heatGrid)
    {
        _heatGrid->setMinTemp();
        NUMBER minTemp = _heatGrid->getMinTemp();
        NUMBER temp;
        for (std::size_t i = 0; i < m_width; ++i)
        {
            for (std::size_t j = 0; j < m_height; ++j)
            {
                temp = _heatGrid->getTemperature(i, j);
                if (temp > NOICE_TEMP) temp = NOICE_TEMP;
                this->set({{i, j}}, 1 - (temp - minTemp)/(NOICE_TEMP - minTemp));
            }
        }
    }
}
