#include "heatgrid.h"
///----------------------------------------------------------------------------
/// @file heatgrid.cpp
/// @brief implementation files for HeatGrid class
///----------------------------------------------------------------------------

#include <iostream>

#define NOICE_TEMP 1.0
namespace model
{

    HeatGrid::HeatGrid(const std::size_t _width,
             const std::size_t _height) :
                   m_first(std::array<std::size_t, 2>{{_width, _height}}),
                   m_second(std::array<std::size_t, 2>{{_width, _height}}),
                   m_actual(&m_first),
                   m_temp(&m_second),
                   m_width(_width),
                   m_height(_height),
                   m_minTemp(0){;}

    void HeatGrid::setTemperature(std::size_t _x,
                                  std::size_t _y,
                                  NUMBER _temp)
    {
        m_actual->set({{_x, _y}}, _temp);
        return;
    }

    void HeatGrid::setMinTemp()
    {
        NUMBER tempTemp;
        NUMBER minTemp = 2000;
        for (std::size_t i = 0; i < m_width; ++i)
        {
            for (std::size_t j = 0; j < m_height; ++j)
            {
                tempTemp = getTemperature(i, j);
                if (tempTemp < minTemp) //cell is frozen
                {
                    minTemp = tempTemp;
#ifdef LOG
                    std::cout << "tempTemp " << tempTemp << std::endl;
                    std::cout << "minTemp prov " << minTemp << std::endl;
#endif
                }
            }
        }
        setMinTemp(minTemp);
    }

    NUMBER HeatGrid::getTemperature(const std::size_t _x,
                                    const std::size_t _y) const
    {
        return m_actual->get({{_x, _y}});
    }

    void HeatGrid::reset(const NUMBER _temp)
    {

        m_actual->reset(_temp);
        m_temp->reset(_temp);
    }
}
