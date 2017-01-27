#ifndef MODEL_HEATGRID_H
#define MODEL_HEATGRID_H
/// @file heatgrid.h
/// @brief this class is the heatgrid class and holds the temperatures

#include <iostream>

#include "grid.h"
#include "common.h"
#include "point.h"

namespace model
{
///-----------------------------------------------------------------------------
/// @class Grid "include/heatgrid.h"
/// @author Marta Feriani
/// @brief a base class for for a heatgrid representation, it holds temperatures
/// and provides methods to set, get or diffuse heat on a grid
///-----------------------------------------------------------------------------
class HeatGrid
{
public:

    ///------------------------------------------------------------------------
    /// @brief constructor passing in the size of the grid
    /// have to be stored
    /// @param [in] _width width of the grid
    /// @param [in] _height height of the grid
    /// -----------------------------------------------------------------------
    HeatGrid(const std::size_t _width,
             const std::size_t _height);

    ///------------------------------------------------------------------------
    /// @brief gets the temperature for a given cell position
    /// @param [in] _x position in the width
    /// @param [in] _y position in the height
    /// @return temperature for the cell
    /// -----------------------------------------------------------------------
    NUMBER getTemperature(const std::size_t _x,
                          const std::size_t _y) const;

    ///------------------------------------------------------------------------
    /// @brief getter for coldest temperature on the grid
    /// @return coldest temperature
    /// -----------------------------------------------------------------------
    inline NUMBER getMinTemp(){ return m_minTemp;}

    ///mutators
    ///------------------------------------------------------------------------
    /// @brief set given temperature to the given position
    /// @param [in] _x position in the width
    /// @param [in] _y position in the height
    /// @param [in] _temp temperature to assign
    /// -----------------------------------------------------------------------
    void setTemperature(const std::size_t _x,
                        const std::size_t _y,
                        const NUMBER _temp);

    ///------------------------------------------------------------------------
    /// @brief cycles grid temperatures and saves the coldest one
    /// -----------------------------------------------------------------------
    void setMinTemp();

    ///------------------------------------------------------------------------
    /// @brief set the coldest temperature for the grid to a given value
    /// @param [in] _temp temperature to be assigned
    /// -----------------------------------------------------------------------
    inline void setMinTemp(const NUMBER _temp){m_minTemp = _temp;}

    ///------------------------------------------------------------------------
    /// @brief reset all the temperatures on the grid to the given one
    /// @param [in] _temp temperature to be assigned
    /// -----------------------------------------------------------------------
    void reset(const NUMBER _temp);

    /// The following section is from :-
    /// Fabien Dournac (2003).
    /// MPI Parallelization for numerically solving the 3D Heat equation[online]
    /// [Accessed 2016].
    /// Available from: "https://dournac.org/info/parallel_heat3d".

    ///------------------------------------------------------------------------
    /// @brief diffuses cold around by solving the heat equation
    /// @param [in] _k k heat diffusion constant
    /// @param [in] _dt delta time (interval) to discretise the diffusion
    /// @param [in] _navigator hex/square navigator that retrieves the neighbour
    /// position of the current one and applies the given lambda function
    /// -----------------------------------------------------------------------
    template <typename NAVIGATOR>
    void diffuse(const NUMBER _k0, const NUMBER _dt, NAVIGATOR _navigator)
    {

        const NUMBER hy = 1.0 / (NUMBER)m_height;
        const NUMBER weighty = _k0 * _dt / (hy * hy);

        Point point;
        NUMBER accumulator;
        std::size_t ncount;
        for(std::size_t i = 0; i < m_width; ++i)
        {
            for(std::size_t j = 0; j < m_height; ++j)
            {
                accumulator = 0;
                ncount = 0;
                point.x = i;
                point.y = j;

                NUMBER cvalue = this->m_actual->get({{point.x, point.y}});
                _navigator->onNeighbours(point,
                                         [cvalue, weighty,
                                         &point, &ncount,
                                         &accumulator, this] (Point neighbour)
                {
                    accumulator += this->m_actual->get({{neighbour.x, neighbour.y}}) - cvalue;
                    ++ncount;
                });
                accumulator = ncount ? accumulator/ncount : accumulator;
                this->m_temp->set({{point.x, point.y}}, weighty * accumulator + cvalue);
            }
        }

        //switching pointers
        if(m_actual == &m_first)
        {
            m_actual = &m_second;
            m_temp = &m_first;
        }
        else
        {
            m_actual = &m_first;
            m_temp = &m_second;
        }
        return;
    }

#if defined(DEBUG)
    inline void inspect() const
    {
        m_actual->inspect();
    }
#else
    inline void inspect() {}
#endif

private:

    ///------------------------------------------------------------------------
    /// @brief grid to store temperatures
    /// -----------------------------------------------------------------------
    Grid<NUMBER, 2> m_first;

    ///------------------------------------------------------------------------
    /// @brief grid to store temperatures
    /// -----------------------------------------------------------------------
    Grid<NUMBER, 2> m_second;

    //pointer to two different Grid objects of the class itself
    //so that I can switch the pointers without having to reallocate data
    ///------------------------------------------------------------------------
    /// @brief pointer to the grid containing the current temperatures
    /// -----------------------------------------------------------------------
    Grid<NUMBER, 2>* m_actual;

    ///------------------------------------------------------------------------
    /// @brief pointer to the grid containing the outdated temperature
    /// -----------------------------------------------------------------------
    Grid<NUMBER, 2>* m_temp;

    /// -----------------------------------------------------------------------
    /// @brief width width of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_width;

    /// -----------------------------------------------------------------------
    /// @brief height height of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_height;

    /// -----------------------------------------------------------------------
    /// @brief coldest temperature on the grid
    /// -----------------------------------------------------------------------
    NUMBER m_minTemp;
};
} //end namespace model

#endif // MODEL_HEATGRID_H
