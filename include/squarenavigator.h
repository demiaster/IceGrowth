#ifndef MODEL_SQUARENAVIGATOR_H
#define MODEL_SQUARENAVIGATOR_H

#include <random>
#include "point.h"
#include "navigator.h"

namespace model
{
    class SquareNavigator : public Navigator
    {
    public:
        SquareNavigator(const std::size_t _width, const std::size_t _height);
        model::Point setOnBorder() override;
        void walk(model::Point& _walker) override;
        //void diffuseOnAxis() override;
        bool isFreezable(const float _probability);

    private:
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng; // seed the generator
        std::uniform_int_distribution<> distr;
        std::uniform_int_distribution<> offdistr;
        std::uniform_real_distribution<> pdistrib;
    };
}

#endif // MODEL_SQUARENAVIGATOR_H
