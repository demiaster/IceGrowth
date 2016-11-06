#ifndef LINEYIELDER_H
#define LINEYIELDER_H
#include "point.h"

#define POW(X) ((X)*(X))

class LineYielder
{
public:
    inline LineYielder(const Point& _pinit, const Point& _pend) :
        m_center(_pinit),
        m_radius(std::sqrt(POW(_pend.x - _pinit.x) + POW(_pend.y - _pinit.y))),
        m_angle(std::atan2(_pend.y - _pinit.y, _pend.x - _pinit.x)) {;}

    inline Point nextLine(const float _delta)
    {
        m_angle = m_angle + _delta;
        unsigned int x = m_radius * std::cos(m_angle) + m_center.x;
        unsigned int y = m_radius * std::sin(m_angle) + m_center.y;
        return Point{x, y};
    }

    inline ~LineYielder() {;}


private:
    const Point& m_center;
    float m_radius;
    float m_angle;
};

#endif // LINEYIELDER_H
