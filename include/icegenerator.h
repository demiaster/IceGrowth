#ifndef CONTROLLER_ICEGENERATOR_H
#define CONTROLLER_ICEGENERATOR_H

#include "heatgrid.h"
#include "icegrid.h"
#include "image.h"

namespace controller
{
    class IceGenerator
    {
    public:
        IceGenerator(const std::size_t _width,
                            const std::size_t _height);
        inline void run()
        {
                update();
                represent();
        }

        void setup();
    private:
        void update();
        void represent();

        void dla_pattern();

        std::size_t m_width, m_height;
        model::HeatGrid m_heatGrid;
        model::IceGrid m_iceGrid;
        view::Image m_image;

    };
}

#endif // CONTROLLER_ICEGENERATOR_H
