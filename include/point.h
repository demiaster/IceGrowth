#ifndef MODEL_POINT_H
#define MODEL_POINT_H

#include <cstddef>

namespace model {
    typedef struct Point_s
    {
        std::size_t x;
        std::size_t y;
    } Point;
}

#endif // MODEL_POINT_H
