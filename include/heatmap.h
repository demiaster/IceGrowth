#ifndef HEATMAP_H
#define HEATMAP_H

#include "map.h"
#define NUMBER float
class HeatMap
{
public:
    inline HeatMap(const std::size_t width,
                   const std::size_t height) :
                   m_first({width, height}),
                   m_second({width, height}),
                   m_actual(&m_first),
                   m_temp(&m_second),
                   m_width(width),
                   m_height(height) {;}

    void setTemperature(const std::size_t _x,
                        const std::size_t _y,
                        const NUMBER temp);

    void diffuse(const NUMBER _k0, const NUMBER _dt);

private:

    //actual maps, allocated without using new operator
    Map<NUMBER, 2> m_first;
    Map<NUMBER, 2> m_second;

    //pointer to two different Map objects
    //of the class itself
    //so that I can switch the pointers
    //without having to reallocate data
    Map<NUMBER, 2>* m_actual;
    Map<NUMBER, 2>* m_temp;

    std::size_t m_width, m_height;
};

#endif // HEATMAP_H
