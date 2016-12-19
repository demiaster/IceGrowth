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
                     const std::size_t _height,
                     const common::RandomDist _randomdist);
        model::Point setOnBorder() override;
        void walk(model::Point& _walker) override;
        //void diffuseOnAxis() override;
        bool isFreezable(const float _probability);
    private:
        common::RandomDist& m_randomdist;
    };
}
#endif //MODEL_HEXNAVIGATOR_H
