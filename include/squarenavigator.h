#ifndef MODEL_SQUARENAVIGATOR_H
#define MODEL_SQUARENAVIGATOR_H

#include <random>
#include "point.h"
#include "navigator.h"
#include "randomdist.h"

namespace model
{
    class SquareNavigator : public Navigator
    {
    public:
        SquareNavigator(const std::size_t _width,
                        const std::size_t _height);
        model::Point setOnBorder() override;
        void walk(model::Point& _walker) override;
        //void diffuseOnAxis() override;
        //bool isFreezable(const float _probability);
    private:
        common::IntDistribution m_borderdist, m_neighboursdist;

        //TODO: make this variable static again
        DiffPoint m_point[8] =
                        {{-1, -1},
                          {0, -1},
                          {1, -1},
                          {1, 0},
                          {1, 1},
                          {0, 1},
                          {-1, 1},
                          {-1, 0}};
    };
}

#endif // MODEL_SQUARENAVIGATOR_H
