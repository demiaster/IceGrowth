#ifndef MODEL_POINT_H
#define MODEL_POINT_H

#include <cstddef>
#include <ngl/Util.h>
#include "common.h"

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

    typedef struct MeshPoint_s
    {
        NUMBER x;
        NUMBER y;
    } MeshPoint;

    typedef struct Vertex_s
    {
        ngl::Vec3 p;
        ngl::Vec3 n;
        ngl::Vec4 c;
    } Vertex;
}

#endif // MODEL_POINT_H
