#ifndef MODEL_ICEGRID_H
#define MODEL_ICEGRID_H
/// @file icegrid.h
/// @brief this class contains the ice state for the simulation

#include <iostream>

#include "common.h"
#include "grid.h"
#include "heatgrid.h"
#include "navigator.h"

namespace model
{

///----------------------------------------------------------------------------
/// @class IceGrid "include/icegrid.h"
/// @author Marta Feriani
/// @brief inherits from base class Grid, implements methods to set
/// new ice percentage
///----------------------------------------------------------------------------
class IceGrid : public Grid<PERCENTAGE, 2>
{
public:

    ///------------------------------------------------------------------------
    /// @brief constructor passing in the size of the grid
    /// @param [in] _width width of the grid
    /// @param [in] _height height of the grid
    /// -----------------------------------------------------------------------
    IceGrid(const std::size_t _width,
            const std::size_t _height);

    ///------------------------------------------------------------------------
    /// @brief sets the ice percentage for a given cell position
    /// @param [in] _x position in the width
    /// @param [in] _y position in the height
    /// @param [in] _percentage ice percentage to be assigned
    /// -----------------------------------------------------------------------
    void freeze(std::size_t _x, std::size_t _y, PERCENTAGE _percentage);

    ///------------------------------------------------------------------------
    /// @brief updates the ice percentage on the icegrid according to the
    /// new temperatures field
    /// @param [in] _heatGrid reference to temperature field
    /// -----------------------------------------------------------------------
    void merge(HeatGrid* _heatGrid);
private:

    /// -----------------------------------------------------------------------
    /// @brief width of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_width;

    /// -----------------------------------------------------------------------
    /// @brief height of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_height;
};
} // end namespace model
#endif // MODEL_ICEGRID_H
