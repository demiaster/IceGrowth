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
            Point point;
            NUMBER accumulator;
            int q = 0;
            for(std::size_t i = 1; i < m_width - 1; ++i)
            {
                for(std::size_t j = 1; j < m_height - 1; ++j)
                {
                    q++;
//                    std::cout << "q = " << q << std::endl;
                    accumulator = 0;
                    point.x = i;
                    point.y = j;
                    navigator->onAxis(point, [weighty,
                                              diagy,
                                              &accumulator,
                                              this](Point left,
                                                         Point center,
                                                         Point right)
                    {
//                        std::cout<< "left " << this->m_actual->get({{left.x, left.y}}) << std::endl;
//                        std::cout<< "right " << this->m_actual->get({{right.x, right.y}}) << std::endl;
//                        std::cout<< "center " << this->m_actual->get({{center.x, center.y}}) << std::endl;
                        accumulator += weighty * (this->m_actual->get({{left.x, left.y}}) +
                                                  this->m_actual->get({{right.x, right.y}}) +
                                                  this->m_actual->get({{center.x, center.y}}) * diagy);
                    });
//                    std::cout << "accumulator " << accumulator << std::endl;
                    m_temp->set({{i, j}}, accumulator);
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
