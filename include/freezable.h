#ifndef MODEL_FREEZABLE_H
#define MODEL_FREEZABLE_H

#include "randomdist.h"

namespace model
{
    class Freezable
    {
    public:
        inline Freezable(const std::size_t _width,
                         const std::size_t _height,
                         common::RandomDist& _randomdist) :
                         m_randomdist(_randomdist) {;}

        inline bool isFreezable(const float _probability)
        {
            return _probability > m_randomdist.get_pdistrib();
        }
    private:
        common::RandomDist& m_randomdist;
    };
}

#endif //MODEL_FREEZABLE_H
