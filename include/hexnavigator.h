#ifndef MODEL_HEXNAVIGATOR_H
#define MODEL_HEXNAVIGATOR_H

#include "navigator.h"
#include "randomdist.h"
namespace model
{
    class HexNavigator : public Navigator, common::RandomDist
    {
    public:
        HexNavigator(const std::size_t _width, const std::size_t _height);
        model::Point setOnBorder() override;
        void walk(model::Point& _walker) override;
        //void diffuseOnAxis() override;
        bool isFreezable(const float _probability); 
    };
}
#endif //MODEL_HEXNAVIGATOR_H
