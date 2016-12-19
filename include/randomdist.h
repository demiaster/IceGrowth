#ifndef COMMON_RANDOMDIST_H
#define COMMON_RANDOMDIST_H

#define GETTER(type, variable) \
    inline type get_ ## variable  () { \
        return m_ ## variable  (m_eng); \
    }

#include <random>
namespace common
{
    class RandomDist
    {
    public:
        inline RandomDist(const std::size_t _width,
                          const std::size_t _height) :
                                            m_eng(m_rd()),
                                            m_distr(-1, 1),
                                            m_offdistr(0, 2 * (_width + _height) - 4),
                                            m_pdistrib(0, 1.0) {;}

        GETTER(std::size_t, distr)

        GETTER(std::size_t, offdistr)

        GETTER(float, pdistrib)

    private:
        std::random_device m_rd; // obtain a random number from hardware
        std::mt19937 m_eng; // seed the generator
        std::uniform_int_distribution<> m_distr;
        std::uniform_int_distribution<> m_offdistr;
        std::uniform_real_distribution<> m_pdistrib;

    };
}

#endif //COMMON_RANDOMDIST_H
