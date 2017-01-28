#ifndef MODEL_HEXNAVIGATOR_H
#define MODEL_HEXNAVIGATOR_H
/// @file hexnavigator.h
/// @brief this class is the navigator for an hexagonal lattice

#include <tuple>
#include <iostream>

#include "navigator.h"
#include "randomdist.h"
#include "common.h"

#define TUPLE std::tuple<DiffPoint, DiffPoint>

namespace model
{

///----------------------------------------------------------------------------
/// @class Grid "include/hexnavigator.h"
/// @author Marta Feriani
/// @brief hexnavigator inherits from navigator base class and implements
/// methods to handle movement on an hexagonal lattice
///----------------------------------------------------------------------------
class HexNavigator : public Navigator
{
public:

    ///------------------------------------------------------------------------
    /// @brief constructor passing in the size of the grid
    /// @param [in] _width width of the grid
    /// @param [in] _height height of the grid
    /// -----------------------------------------------------------------------
    HexNavigator(const std::size_t _width,
                 const std::size_t _height);

    ///------------------------------------------------------------------------
    /// @brief selects a random position on the frame of the grid for the
    /// random walker to be positioned to
    /// @return point representing the new position
    /// -----------------------------------------------------------------------
    Point setOnBorder() override;

    ///------------------------------------------------------------------------
    /// @brief selects a random adjacent position for the given one
    /// @param [inout] random walker position
    /// -----------------------------------------------------------------------
    void walk(model::Point& _walker) override;

    ///------------------------------------------------------------------------
    /// @brief implements the reactive pattern. The callback function given
    /// as input is applied to every neighbouring position of the given one
    /// @param [in] _point input position
    /// @param [in] _operation function, lambda or whatever
    /// that answers to the call operator "()"
    /// -----------------------------------------------------------------------
    template <typename OPERATION>
    void onNeighbours(model::Point& _point, OPERATION _operation)
    {
        DiffPoint (&m_point)[6] = _point.x % 2 ? m_point_even : m_point_odd;

        for (std::size_t i = 0; i < 6; i++)
        {
            Point newPoint = _point;

            newPoint.x += m_point[i].x;
            newPoint.y += m_point[i].y;

            //throws a warning but better to keep it for in future
            //the .x and .y could be a different type than std::size_t
            if (0 <= newPoint.x && newPoint.x < m_width &&
                    0 <= newPoint.y && newPoint.y < m_height)
            {
                _operation(newPoint);
            }
        }
    }

private:

    ///------------------------------------------------------------------------
    /// @brief integer distribution used to select a random neighbour position
    /// -----------------------------------------------------------------------
    common::IntDistribution m_neighboursdist;

    ///------------------------------------------------------------------------
    /// @brief integer distribution used to select a random edge position
    /// -----------------------------------------------------------------------
    common::IntDistribution m_borderdist;

    ///------------------------------------------------------------------------
    /// @brief holds the neighbouring diffpoints (values for x and y
    /// to be summed to current position to move around). Since it emulates an
    /// hexagonal lattice, there are different neighbouring position depending
    /// on wheter the column index for current position si odd or even.
    /// This one is for even column indices.
    /// -----------------------------------------------------------------------
    DiffPoint m_point_even[6] = {{0, -1},
                                 {1, -1},
                                 {1, 0},
                                 {0, 1},
                                 {-1, 0},
                                 {-1, -1}};

    ///------------------------------------------------------------------------
    /// @brief holds the neighbouring diffpoints (values for x and y
    /// to be summed to current position to move around). Since it emulates an
    /// hexagonal lattice, there are different neighbouring position depending
    /// on wheter the column index for current position si odd or even.
    /// This one is for odd column indices.
    /// -----------------------------------------------------------------------
    DiffPoint m_point_odd[6] = {{0, -1},
                                {1, 0},
                                {1, 1},
                                {0, 1},
                                {-1, 1},
                                {-1, 0}};

    ///------------------------------------------------------------------------
    /// @brief holds hexagonal axis diffpoints (values for x and y
    /// to be summed to current position to move around). Since it emulates an
    /// hexagonal lattice, there are different neighbouring position depending
    /// on wheter the column index for current position si odd or even.
    /// This one is for even column indices.
    /// -----------------------------------------------------------------------
    std::array<TUPLE, 3> m_axis_even = {{TUPLE({-1, -1}, {1, 0}),
                                         TUPLE({-1, 0}, {1, -1}),
                                         TUPLE({0, -1}, {0, 1})}};

    ///------------------------------------------------------------------------
    /// @brief holds hexagonal axis diffpoints (values for x and y
    /// to be summed to current position to move around). Since it emulates an
    /// hexagonal lattice, there are different neighbouring position depending
    /// on wheter the column index for current position si odd or even.
    /// This one is for odd column indices.
    /// -----------------------------------------------------------------------
    std::array<TUPLE, 3> m_axis_odd = {{TUPLE({-1, 0}, {1, 1}),
                                        TUPLE({-1, 1}, {1, 0}),
                                        TUPLE({0, -1}, {0, 1})}};
};
} //end namespace model
#endif //MODEL_HEXNAVIGATOR_H
