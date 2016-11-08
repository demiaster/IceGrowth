/*#include "map.h"
#include <numeric>

MAP_T
MAP_C::Map(const std::array<std::size_t, N>& sizes)
{
    m_sizes = sizes;
    m_data.reset(new T[std::accumulate(m_sizes.begin(), m_sizes.end(),
                                       1, std::multiplies<std::size_t>())]);
}

MAP_T void MAP_C::set(const std::array<std::size_t, N>& coordinates, const T elem) {
    m_data[index(coordinates)] = elem;
}


MAP_T T MAP_C::get(const std::array<std::size_t, N>& coordinates) const {
    return m_data[index(coordinates)];
}

MAP_T
std::size_t MAP_C::index(const std::array<std::size_t, N>& coordinates) const {
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
*/
