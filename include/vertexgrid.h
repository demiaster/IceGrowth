#define VERTEXGRID_H 1
#ifndef VERTEXGRID_H
#define VERTEXGRID_H

#include "grid.h"
#include "point.h"

namespace view
{
    class VertexGrid : public model::Grid<model::Vertex, 2>
    {
        public:
            //sostituire con una variabile fatta bene
            VertexGrid(const std::size_t _width * 21,
                       const std::size_t _height);
        private:
            std::size_t m_width, m_height;
    };
}
#endif //VERTEXGRID_H
