#ifndef CONTROLLER_ICEGENERATOR_H
#define CONTROLLER_ICEGENERATOR_H

#include <memory>
#include <QThread>
#include "heatgrid.h"
#include "icegrid.h"
#include "image.h"
#include "framebuffer.h"
#include "freezable.h"
#include "squarenavigator.h"
#include "randomdist.h"
#include "NGLscene.h"

namespace controller
{
    class IceGenerator : public QThread
    { Q_OBJECT
    public:
        //TODO: add shared_ptr here as well
        //IceGenerator(QObject* parent);
        IceGenerator();
//        IceGenerator(const std::size_t _width,
//                     const std::size_t _height,
//                     frm::Framebuffer* _framebuffer);

//        IceGenerator(const std::size_t _width,
//                     const std::size_t _height,
//                     std::shared_ptr<view::NGLscene> _window);

        void run();
        void setup(const std::size_t _width,
                   const std::size_t _height, std::shared_ptr<view::NGLscene> _window);

        void setup(const std::size_t _width,
                   const std::size_t _height);
//    public slots:
//        void runSlot();

    signals:
        void imageChanged();

    private:
        void update();
        void representFrameBuffer();
        void representNGL();

        void dla_pattern();

        std::size_t m_width, m_height;
        std::unique_ptr<model::HeatGrid> m_heatGrid;
        std::unique_ptr<model::IceGrid> m_iceGrid;
        std::shared_ptr<view::Image> m_image;
        std::unique_ptr<frm::Framebuffer> m_framebuffer;
        std::shared_ptr<view::NGLscene> m_window;
        model::Freezable m_freezeprob;
        std::unique_ptr<model::SquareNavigator> m_navigator;
    };
}

#endif // CONTROLLER_ICEGENERATOR_H
