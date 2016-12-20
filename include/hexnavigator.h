#ifndef MODEL_HEXNAVIGATOR_H
#define MODEL_HEXNAVIGATOR_H

#include "navigator.h"
#include "randomdist.h"
namespace model
{
    class HexNavigator : public Navigator
    {
    public:
        HexNavigator(const std::size_t _width,
                     const std::size_t _height);
        model::Point setOnBorder() override;
        void walk(model::Point& _walker) override;
        //void diffuseOnAxis() override;
        bool isFreezable(const float _probability);
    private:
        //common::RandomDist& m_randomdist;
        common::IntDistribution m_borderdist, m_neighboursdist;

        // pari
        //TODO: make this variable static again
        DiffPoint m_point_even[6] =
                        {{0, -1},
                          {1, -1},
                          {1, 0},
                          {0, 1},
                          {-1, 0},
                          {-1, -1}};
        // dispari
        //TODO: make this variable static again
        DiffPoint m_point_odd[6] =
                        {{0, -1},
                          {1, 0},
                          {1, 1},
                          {0, 1},
                          {-1, 1},
                          {-1, 0}};
    };
}
#endif //MODEL_HEXNAVIGATOR_H
