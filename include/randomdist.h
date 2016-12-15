#ifndef COMMON_RANDOMDIST_H
#define COMMON_RANDOMDIST_H

#include <random>
namespace common
{
    class RandomDist
    {
    public:
    protected:
        inline RandomDist(const std::size_t _width,
                          const std::size_t _height) :
                                            eng(rd()),
                                            distr(-1, 1),
                                            offdistr(0, 2 * (_width + _height) - 4),
                                            pdistrib(0, 1.0) {;}
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng; // seed the generator
        std::uniform_int_distribution<> distr;
        std::uniform_int_distribution<> offdistr;
        std::uniform_real_distribution<> pdistrib;

    };
}

#endif //COMMON_RANDOMDIST_H
