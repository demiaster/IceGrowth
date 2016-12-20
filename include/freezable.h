#ifndef MODEL_FREEZABLE_H
#define MODEL_FREEZABLE_H

#include "randomdist.h"

namespace model
{
    class Freezable
    {
    public:
        inline Freezable(const std::size_t _width,
                         const std::size_t _height) :
                         m_floatdist(0.0, 1.0) {;}

        inline bool isFreezable(const float _probability)
        {
            return _probability > m_floatdist.get_distr();
        }
    private:
        common::FloatDistribution m_floatdist;
    };
}

#endif //MODEL_FREEZABLE_H
