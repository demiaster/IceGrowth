#ifndef MODEL_NAVIGATOR_H
#define MODEL_NAVIGATOR_H
/// @file navigator.h
/// @brief this class is the navigator for every kind of lattice

#include "point.h"
namespace model
{

///----------------------------------------------------------------------------
/// @class Navigator "include/navigator.h"
/// @author Marta Feriani
/// @brief base class navigator defines methods to move on the lattice
/// based on the shape of the cells that compose the mesh.
///----------------------------------------------------------------------------
class Navigator
{
public:

    ///------------------------------------------------------------------------
    /// @brief selects a random position on the frame of the grid for the
    /// random walker to be positioned to
    /// @return point representing the new position
    /// -----------------------------------------------------------------------
    virtual Point setOnBorder() = 0;

    ///------------------------------------------------------------------------
    /// @brief selects a random adjacent position for the given one
    /// @param [inout] random walker position
    /// -----------------------------------------------------------------------
    virtual void walk(Point& _walker) = 0;

    ///------------------------------------------------------------------------
    /// @brief implements the reactive pattern. The callback function given
    /// as input is applied to every neighbouring position of the given one
    /// @param [in] _point input position
    /// @param [in] _operation function, lambda or whatever
    /// that answers to the call operator "()"
    /// -----------------------------------------------------------------------
    template <typename OPERATION>
    void onNeighbours(Point& _point, OPERATION _operation);

protected:

    /// -----------------------------------------------------------------------
    /// @brief width of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_width;

    /// -----------------------------------------------------------------------
    /// @brief height of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_height;
};
} //end namespace model

#endif //MODEL_NAVIGATOR_H
