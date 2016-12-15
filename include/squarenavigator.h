#ifndef MODEL_SQUARENAVIGATOR_H
#define MODEL_SQUARENAVIGATOR_H

#include <random>
#include "point.h"
#include "navigator.h"
#include "randomdist.h"

namespace model
{
    class SquareNavigator : public Navigator, public common::RandomDist
    {
    public:
        SquareNavigator(const std::size_t _width, const std::size_t _height);
        model::Point setOnBorder() override;
        void walk(model::Point& _walker) override;
        //void diffuseOnAxis() override;
        //bool isFreezable(const float _probability);
    };
}

#endif // MODEL_SQUARENAVIGATOR_H
