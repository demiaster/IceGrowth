#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <random>
#include "point.h"

namespace model
{
    class Navigator
    {
    public:
        Navigator(std::size_t _width, std::size_t _height);
        model::Point setOnBorder();
        void walk(model::Point& _walker);
        void diffuseOnAxis();
        bool isFreezable(float _probability);

    private:
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng; // seed the generator
        std::uniform_int_distribution<> distr;
        std::uniform_int_distribution<> offdistr;
        std::uniform_real_distribution<> pdistrib;
        std::size_t m_width, m_height;
    };
}

#endif // NAVIGATOR_H
