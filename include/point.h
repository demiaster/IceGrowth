#ifndef MODEL_POINT_H
#define MODEL_POINT_H

#include <cstddef>
#include <ngl/Util.h>

#include "common.h"

namespace model
{
/// -----------------------------------------------------------------------
///@brief new type for points
/// -----------------------------------------------------------------------
typedef struct Point_s
{
    std::size_t x;
    std::size_t y;
} Point;

/// -----------------------------------------------------------------------
///@brief new type for displacements that have to be summed to points coord
/// -----------------------------------------------------------------------
typedef struct DiffPoint_s
{
    int x;
    int y;
} DiffPoint;

/// -----------------------------------------------------------------------
///@brief new type for mesh points
/// -----------------------------------------------------------------------
typedef struct MeshPoint_s
{
    NUMBER x;
    NUMBER y;
} MeshPoint;

/// -----------------------------------------------------------------------
///@brief vertices that will be used when preparing the vbo
/// -----------------------------------------------------------------------
typedef struct Vertex_s
{
    ngl::Vec3 p;
    ngl::Vec3 n;
    ngl::Vec4 c;
} Vertex;
} // end namespace model

#endif // MODEL_POINT_H
