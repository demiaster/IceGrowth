#ifndef MODEL_FREEZABLE_H
#define MODEL_FREEZABLE_H

#include "randomdist.h"

namespace model
{
    class Freezable : public common::RandomDist
    {
    public:
        inline Freezable(const std::size_t _width,
                         const std::size_t _height) :
                                    common::RandomDist(_width, _height) {;}
        inline bool isFreezable(const float _probability)
        {
            if(_probability > pdistrib(eng))
            {
                return true;
            }
            return false;
        }
    };
}

#endif //MODEL_FREEZABLE_H
