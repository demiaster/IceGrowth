#ifndef MODEL_HEATGRID_H
#define MODEL_HEATGRID_H

#include "grid.h"

namespace model
{
    using NUMBER = double;
    class HeatGrid
    {
    public:
        HeatGrid(const std::size_t _width,
                 const std::size_t _height);

        void setTemperature(const std::size_t _x,
                            const std::size_t _y,
                            const NUMBER _temp);

        NUMBER getTemperature(const std::size_t _x,
                              const std::size_t _y) const;

        void reset(const NUMBER _temp);

        void diffuse(const NUMBER _k0, const NUMBER _dt);
#if defined(DEBUG)
            inline void inspect() const
            {
                m_actual->inspect();
            }
#else
            inline void inspect() {}
#endif

    private:

        //actual grids, allocated without using new operator
        Grid<NUMBER, 2> m_first;
        Grid<NUMBER, 2> m_second;

        //pointer to two different Grid objects
        //of the class itself
        //so that I can switch the pointers
        //without having to reallocate data
        Grid<NUMBER, 2>* m_actual;
        Grid<NUMBER, 2>* m_temp;

        std::size_t m_width, m_height;
    };
}

#endif // MODEL_HEATGRID_H
