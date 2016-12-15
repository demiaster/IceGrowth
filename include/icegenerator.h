#ifndef CONTROLLER_ICEGENERATOR_H
#define CONTROLLER_ICEGENERATOR_H

#include <memory>
#include "heatgrid.h"
#include "icegrid.h"
#include "image.h"
#include "framebuffer.h"
#include "freezable.h"

namespace controller
{
    class IceGenerator
    {
    public:
        IceGenerator(const std::size_t _width,
                     const std::size_t _height,
                     frm::Framebuffer* _framebuffer);
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
        std::unique_ptr<model::HeatGrid> m_heatGrid;
        std::unique_ptr<model::IceGrid> m_iceGrid;
        std::unique_ptr<view::Image> m_image;
        std::unique_ptr<frm::Framebuffer> m_framebuffer;
        model::Freezable m_freezeprob;

    };
}

#endif // CONTROLLER_ICEGENERATOR_H
