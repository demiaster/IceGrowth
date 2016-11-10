#ifndef MAP_H
#define MAP_H

#include <memory>
#include <vector>
#include <numeric>
#include <cstdarg>

template <typename T, std::size_t N>
class Map
{
    public:
        //get as many dimension for the map as wanted
        //store them somewhere
        inline Map(const std::array<std::size_t, N>& dimensions...) :
            m_sizes(dimensions),
            m_data(new T[std::accumulate(m_sizes.begin(), m_sizes.end(),
                                               1, std::multiplies<std::size_t>())]) {}

        inline void set(const std::array<std::size_t, N>& coordinates, T element)
        {
            m_data[index(coordinates)] = element;
        }
        inline T get(const std::array<std::size_t, N>& coordinates) const
        {
            return m_data[index(coordinates)];
        }



    private:
        std::array<std::size_t, N> m_sizes;

        std::size_t index(const std::array<std::size_t, N>& coordinates) const
        {
            // {W, H, D}
            // {X, Y, Z} inputs
            // X*H*D+Y*D+Z

            // sum accumulator
            std::size_t accum = 0;
            for (std::size_t i = 0; i < N; ++i) {
                // multiplier accumulator
                std::size_t maccum = coordinates[i];
                for (std::size_t j = i + 1; j < N; j++) {
                    maccum *= m_sizes[j];
                }
                accum += maccum;
            }
            return accum;
        }

    protected:
        std::unique_ptr<T[]> m_data;

};

#endif // MAP_H
