#include "heatgrid.h"
#include <iostream>
#include <sstream>


#define MAX_TEMP 1
#define MIN_TEMP -100
namespace model
{

    HeatGrid::HeatGrid(const std::size_t _width,
             const std::size_t _height) :
                   m_first(std::array<std::size_t, 2>{{_width, _height}}),
                   m_second(std::array<std::size_t, 2>{{_width, _height}}),
                   m_actual(&m_first),
                   m_temp(&m_second),
                   m_width(_width),
                   m_height(_height),
                   m_image(_width, _height)
    {
        m_counter = 0;
        m_image.clearScreen(0, 0, 0);
    }

    void HeatGrid::setTemperature(std::size_t _x,
                                  std::size_t _y,
                                  NUMBER _temp)
    {
        m_actual->set({{_x, _y}}, _temp);
        int blue = 255 - (_temp - MIN_TEMP)/(MAX_TEMP - MIN_TEMP) * 255;
        m_image.setPixel(_x, _y, 0, 0, blue);
        std::stringstream ss;
        ss << "heatgrid-" << m_counter << ".png";
        m_image.save(ss.str().c_str());
        ++m_counter;
        return;
    }


    /// The following section is from :-
    /// Fabien Dournac (2003). MPI Parallelization for numerically solving the 3D Heat equation [online]. [Accessed 2016].
    /// Available from: "https://dournac.org/info/parallel_heat3d".

    void HeatGrid::diffuse(const NUMBER _k0, const NUMBER _dt)
    {
        //TODO: evaluate also boundary cells
        //TODO: evaluate also a parallel implementation
        const NUMBER hx  = 1.0 / (NUMBER)m_width;
        const NUMBER hy  = 1.0 / (NUMBER)m_height;
        const NUMBER diagx = - 2.0 + hx * hx / (2 * _k0 * _dt);
        const NUMBER diagy = - 2.0 + hy * hy / (2 * _k0  *_dt);
        const NUMBER weightx = _k0 * _dt / (hx * hx);
        const NUMBER weighty = _k0 * _dt / (hy * hy);

        // Perform an explicit update on the points within the domain
        //#pragma omp parallel for
        for(std::size_t i = 1; i < m_width - 1; ++i)
        {
            for(std::size_t j = 1; j < m_height - 1; ++j)
            {

                m_temp->set({{i, j}},
                             weightx * (m_actual->get({{i - 1, j}}) +
                                        m_actual->get({{i + 1, j}}) +
                                        m_actual->get({{i, j}}) * diagx) +
                             weighty * (m_actual->get({{i, j - 1}}) +
                                        m_actual->get({{i, j + 1}}) +
                                        m_actual->get({{i, j}}) * diagy));
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

    NUMBER HeatGrid::getTemperature(const std::size_t _x,
                                    const std::size_t _y) const
    {
        return m_actual->get({{_x, _y}});
    }

    void HeatGrid::reset(const NUMBER _temp)
    {
        for (size_t i = 0; i < m_width; ++i)
        {
            for (size_t j = 0; j < m_height; ++j)
            {
                m_actual->set({{i, j}}, _temp);
                m_temp->set({{i, j}}, _temp);
            }
        }
    }
}
