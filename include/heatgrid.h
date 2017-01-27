#ifndef MODEL_HEATGRID_H
#define MODEL_HEATGRID_H

#include <iostream>
#include "grid.h"
#include "common.h"
#include "point.h"

namespace model
{
    //using NUMBER = double;
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

        inline NUMBER getMinTemp(){ return m_minTemp;}

        void setMinTemp();
        inline void setMinTemp(const NUMBER _temp){m_minTemp = _temp;}

        void reset(const NUMBER _temp);

//        void diffuse(const NUMBER _k0, const NUMBER _dt);
        /// The following section is from :-
        /// Fabien Dournac (2003). MPI Parallelization for numerically solving the 3D Heat equation [online]. [Accessed 2016].
        /// Available from: "https://dournac.org/info/parallel_heat3d".
        template <typename NAVIGATOR>
        void diffuse(const NUMBER _k0, const NUMBER _dt, NAVIGATOR navigator)
        {
            //TODO: evaluate also boundary cells
            //TODO: evaluate also a parallel implementation
            const NUMBER hy  = 1.0 / (NUMBER)m_height;
            const NUMBER diagy = - 2.0 + hy * hy / (2 * _k0  *_dt);
            const NUMBER weighty = _k0 * _dt / (hy * hy);

            // Perform an explicit update on the points within the domain
            //#pragma omp parallel for
            model::Point point;
            NUMBER accumulator;
            std::size_t ncount;
            for(std::size_t i = 0; i < m_width; ++i)
            {
                for(std::size_t j = 0; j < m_height; ++j)
                {
                    accumulator = 0;
                    ncount = 0;
                    point.x = i;
                    point.y = j;
                    //std::cout << "point.x: " << point.x << std::endl;
                    //std::cout << "point.y: " << point.y << std::endl;
                    NUMBER cvalue = this->m_actual->get({point.x, point.y});
                    //std::cout << "cvalue: " << cvalue << std::endl;
                    navigator->onNeighbours(point, [cvalue, weighty, &point, &ncount, &accumulator, this] (model::Point neighbour) {
                        accumulator += this->m_actual->get({neighbour.x, neighbour.y}) - cvalue;
                        //std::cout << "neighbour.x: " << neighbour.x << std::endl;
                        //std::cout << "neighbour.y: " << neighbour.y << std::endl;
                        //std::cout << "accum: " << accumulator << std::endl;
                        ++ncount;
                    });

                    //std::cout << "ncount: " << ncount << ", accumulator: " << accumulator << std::endl;

                    accumulator = ncount ? accumulator/ncount : accumulator;
                    this->m_temp->set({point.x, point.y}, weighty*accumulator + cvalue);
                }
            }

            //switching pointers
            //std::swap look at it
            if(m_actual == &m_first)
            {
                m_actual = &m_second;
                m_temp = &m_first;
            }
            else
            {
                m_actual = &m_first;
                m_temp = &m_second;
            }

            return;
        }


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
        NUMBER m_minTemp;
    };
}

#endif // MODEL_HEATGRID_H
