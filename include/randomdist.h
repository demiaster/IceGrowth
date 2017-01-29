#ifndef COMMON_RANDOMDIST_H
#define COMMON_RANDOMDIST_H
/// @file randomdist.h
/// @brief this MACRO generates different classes
/// containing random number distributions

#include <random>

#include "common.h"

namespace common
{
///----------------------------------------------------------------------------
/// @class RandomDist "include/randomdist.h"
/// @author Marta Feriani
/// @brief general MACRO that creates different classes given a name,
/// a distribution type and a number type. Each class will then contain:
/// _methods_
/// ctor: param low, high to specify the range for the random distribution
/// get_distr(): returns a random number
///
/// _attributes_
/// m_rd: random device
/// m_eng: random engine
/// m_distr: random distribution
///----------------------------------------------------------------------------
#define RANDOMDIST(name, distr, type) \
    class name \
{ \
    public: \
    inline name(const type low, const type high) : m_eng(m_rd()), m_distr(low, high) {}; \
    inline type get_distr() { \
    return m_distr(m_eng); \
} \
    private: \
    std::random_device m_rd; \
    std::mt19937 m_eng;  \
    std::uniform_ ## distr ## _distribution<type> m_distr; \
}

RANDOMDIST(IntDistribution, int, std::size_t);
RANDOMDIST(FloatDistribution, real, NUMBER);
} // end namespace common

#endif //COMMON_RANDOMDIST_H
