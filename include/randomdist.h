#ifndef COMMON_RANDOMDIST_H
#define COMMON_RANDOMDIST_H

#include <random>
namespace common
{
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
    RANDOMDIST(FloatDistribution, real, float);
}

#endif //COMMON_RANDOMDIST_H
