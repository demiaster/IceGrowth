#ifndef MODEL_NAVIGATOR_H
#define MODEL_NAVIGATOR_H

#include "point.h"
namespace model
{
    class Navigator
    {
    public:
        virtual model::Point setOnBorder() = 0;
        virtual void walk(model::Point& _walker) = 0;
        //virtual void diffuseOnAxis() = 0;
    protected:
        std::size_t m_width, m_height;
    };
}

#endif //MODEL_NAVIGATOR_H
