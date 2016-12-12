#ifndef MODEL_GRID_H
#define MODEL_GRID_H

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
    template <typename T, std::size_t N>
    class Grid
    {
        public:
            //get as many dimension for the Grid as wanted
            //store them somewhere
            inline Grid(const std::array<std::size_t, N>& dimensions) :
                m_sizes(dimensions),
                m_data(new T[std::accumulate(m_sizes.begin(), m_sizes.end(),
                                                   1, std::multiplies<std::size_t>())]) {}

            inline void set(const std::array<std::size_t, N>& coordinates, T element)
            {
                m_data[index(coordinates)] = element;
            }
            inline T get(const std::array<std::size_t, N>& coordinates) const
            /* supercazzola con brematura a destra */
            {
                return m_data[index(coordinates)];
            }

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
            std::array<std::size_t, N> m_sizes;

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
            std::unique_ptr<T[]> m_data;

    };
}

//instantiating template for icegrid.h
//template class model::Grid<double, 2>;

#endif // MODEL_GRID_H
