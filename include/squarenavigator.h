#ifndef MODEL_SQUARENAVIGATOR_H
#define MODEL_SQUARENAVIGATOR_H
/// @file squarenavigator.h
/// @brief this class is the navigator for a square lattice

#include <random>
#include <tuple>
#include <array>

#include "point.h"
#include "navigator.h"
#include "randomdist.h"

#define TUPLE std::tuple<DiffPoint, DiffPoint>

namespace model
{

///-----------------------------------------------------------------------------
/// @class Grid "include/squarenavigator.h"
/// @author Marta Feriani
/// @brief squarenavigator inherits from navigator base class and implements
/// methods to handle movement on a square lattice
///----------------------------------------------------------------------------
class SquareNavigator : public Navigator
{
public:

    ///------------------------------------------------------------------------
    /// @brief constructor passing in the size of the grid
    /// @param [in] _width width of the grid
    /// @param [in] _height height of the grid
    /// -----------------------------------------------------------------------
    SquareNavigator(const std::size_t _width,
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
    void walk(Point& _walker) override;

    ///------------------------------------------------------------------------
    /// @brief implements the reactive pattern. The callback function given
    /// as input is applied to every neighbouring position of the given one
    /// @param [in] _point input position
    /// @param [in] _operation function, lambda or whatever
    /// that answers to the call operator "()"
    /// -----------------------------------------------------------------------
    template <typename OPERATION>
    inline void onNeighbours(Point& _point, OPERATION operation)
    {
        for (std::size_t i = 0; i < 8; i++)
        {
            Point newPoint = _point;

            newPoint.x += m_neighbour[i].x;
            newPoint.y += m_neighbour[i].y;

            //throws a warning but better to keep it for in future
            //the .x and .y could be a different type than std::size_t
            if (0 <= newPoint.x && newPoint.x < m_width &&
                    0 <= newPoint.y && newPoint.y < m_height)
            {
                operation(newPoint);
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
    /// to be summed to current position to move around).
    /// -----------------------------------------------------------------------
    DiffPoint m_neighbour[8] = {{-1, -1},
                                {0, -1},
                                {1, -1},
                                {1, 0},
                                {1, 1},
                                {0, 1},
                                {-1, 1},
                                {-1, 0}};

    ///------------------------------------------------------------------------
    /// @brief holds square axis diffpoints (values for x and y
    /// to be summed to current position to move around).
    /// -----------------------------------------------------------------------
    std::array<TUPLE, 2> m_axis = {{TUPLE({-1, 0}, {1, 0}),
                                    TUPLE({0, -1}, {0, 1})}};
};
} //end namespace model

#endif // MODEL_SQUARENAVIGATOR_H
