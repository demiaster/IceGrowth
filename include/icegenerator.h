#ifndef CONTROLLER_ICEGENERATOR_H
#define CONTROLLER_ICEGENERATOR_H

#include "heatgrid.h"
#include "icegrid.h"
#include "image.h"
#include "point.h"

namespace controller
{
    class IceGenerator
    {
    public:
        IceGenerator(const std::size_t _width,
                            const std::size_t _height);
        inline void mainloop()
        {
            while (true)
            {
                model::Point frozen = update();
                represent(frozen);
            }
        }

        void setup();
    private:
        model::Point update();
        void represent(model::Point _new_frozen);
        model::Point dla_pattern();

        std::size_t m_width, m_height;
        model::HeatGrid m_heatGrid;
        model::IceGrid m_iceGrid;
        view::Image m_image;

    };
}

#endif // CONTROLLER_ICEGENERATOR_H
