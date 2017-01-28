#ifndef MODEL_GRID_H
#define MODEL_GRID_H
/// @file grid.h
/// @brief this class is the base grid class
/// for all the other ones in this project

#include <memory>
#include <array>
#include <numeric>
#include <cstdarg>
#include <functional>
#ifdef DEBUG
#include <iostream>
#endif

namespace model
{

///----------------------------------------------------------------------------
/// @class Grid "include/grid.h"
/// @author Marta Feriani
/// @brief a base class for for a generic grid representation
///----------------------------------------------------------------------------
template <typename T, std::size_t N>
class Grid
{
public:

    ///------------------------------------------------------------------------
    /// @brief constructor passing in an array
    /// containing how many items per dimensions
    /// have to be stored
    /// @param [in] dimensions it stores how many objects per dimension
    /// -----------------------------------------------------------------------
    inline Grid(const std::array<std::size_t, N>& _dimensions) :
        m_sizes(_dimensions),
        m_data(new T[std::accumulate(m_sizes.begin(), m_sizes.end(),
                                     1, std::multiplies<std::size_t>())]) {}

    ///------------------------------------------------------------------------
    /// @brief get content for the specified coordinates position
    /// @param[in] _coordinates array of coordinates
    /// @return content at specified position
    ///------------------------------------------------------------------------
    inline T get(const std::array<std::size_t, N>& _coordinates) const
    {
        return m_data[index(_coordinates)];
    }

    /// mutators
    /// -----------------------------------------------------------------------
    /// @brief assign given object to the specified coordinates position
    /// @param [in] _coordinates coordinates for the position
    /// @param [in] _element object to be assigned
    /// -----------------------------------------------------------------------
    inline void set(const std::array<std::size_t, N>& _coordinates, T _element)
    {
        m_data[index(_coordinates)] = _element;
    }

    ///------------------------------------------------------------------------
    /// @brief assign given object to every position in the grid
    /// @param [in] _element object to be assigned
    /// -----------------------------------------------------------------------
    inline void reset(const T _element)
    {
        std::size_t len = std::accumulate(m_sizes.begin(), m_sizes.end(),
                                          1, std::multiplies<std::size_t>());
        for (size_t i = 0; i < len; ++i)
        {
            m_data[i] = _element;
        }
    }
#ifdef DEBUG
    inline void inspect() const
    {
        if (N == 2)
        {
            std::cout << "grid internal: \n";
            std::cout << "x: "<< m_sizes[0]<< "y: " << m_sizes[1] << std::endl;
            std::cout << "  ";
            for (std::size_t j = 0; j < m_sizes[1]; ++j) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
            for (std::size_t i = 0; i < m_sizes[0]; ++i) {
                std::cout << i << " ";
                for (std::size_t j = 0; j < m_sizes[1]; ++j) {
                    std::cout << get({{i, j}}) << ' ';
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
#else
    inline void inspect() const
    {

    }
#endif

private:

    ///------------------------------------------------------------------------
    ///@brief holds the number of elements per dimension
    /// -----------------------------------------------------------------------
    std::array<std::size_t, N> m_sizes;

    /// -----------------------------------------------------------------------
    /// @brief converts input coordinates value to index of m_data
    /// @param [in] _coordinates coordinates for the position
    /// @return the index of m_data corresponding the coordinates
    /// -----------------------------------------------------------------------
    inline std::size_t index(const std::array<std::size_t, N>& coordinates) const
    {
        // {W, H, D}
        // {X, Y, Z} inputs
        // X*H*D+Y*D+Z

        // sum accumulator
        std::size_t accum = 0;
        for (std::size_t i = 0; i < N; ++i)
        {
            // multiplier accumulator
            std::size_t maccum = coordinates[i];
            for (std::size_t j = i + 1; j < N; j++)
            {
                maccum *= m_sizes[j];
            }
            accum += maccum;
        }
        return accum;
    }

protected:

    /// -----------------------------------------------------------------------
    ///@brief holds all the element of the grid
    /// -----------------------------------------------------------------------
    std::unique_ptr<T[]> m_data;

};
} //end namespace model

#endif // MODEL_GRID_H
