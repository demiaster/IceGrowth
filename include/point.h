#ifndef MODEL_POINT_H
#define MODEL_POINT_H

#include <cstddef>

namespace model
{
    typedef struct Point_s
    {
        std::size_t x;
        std::size_t y;
    } Point;

    typedef struct DiffPoint_s
    {
        int x;
        int y;
    } DiffPoint;
}

#endif // MODEL_POINT_H
