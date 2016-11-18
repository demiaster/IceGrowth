#ifndef CONTROLLER_ICEGENERATOR_H
#define CONTROLLER_ICEGENERATOR_H

#include "heatgrid.h"
#include "icegrid.h"

namespace controller
{
    class IceGenerator
    {
    public:
        inline IceGenerator(const std::size_t _width,
                            const std::size_t _height) :
            m_width(_width), m_height(_height),
            m_heatGrid(_width, _height), m_iceGrid(_width, _height) {;}
        inline void mainloop()
        {
            void setup();
            while (true)
            {
                update();
                represent();
            }
        }
    private:
        void setup();

        void update();
        void represent();

        void dla_pattern();

        std::size_t m_width, m_height;
        model::HeatGrid m_heatGrid;
        model::IceGrid m_iceGrid;

    };
}

#endif // CONTROLLER_ICEGENERATOR_H
