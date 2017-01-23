#include "point.h"
#include "image.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <thread>

// random shits
//#include <random>
//#include <algorithm>
//#include <sstream>

#include <QtGui/QGuiApplication>

#include "NGLscene.h"
#include "icegenerator.h"

static const size_t W = 401;
static const size_t H = 401;

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    // create an OpenGL format specifier
    QSurfaceFormat format;
    // set the number of samples for multisampling
    // will need to enable glEnable(GL_MULTISAMPLE); once we have a context
    format.setSamples(4);
    #if defined( __APPLE__)
      // at present mac osx Mountain Lion only supports GL3.2
      // the new mavericks will have GL 4.x so can change
      format.setMajorVersion(4);
      format.setMinorVersion(1);
    #else
      // with luck we have the latest GL version so set to this
      format.setMajorVersion(4);
      format.setMinorVersion(1);
    #endif
    // now we are going to set to CoreProfile OpenGL so we can't use and old Immediate mode GL
    format.setProfile(QSurfaceFormat::CoreProfile);
    // now set the depth buffer to 24 bits
    format.setDepthBufferSize(24);
    // now we are going to create our scene window
    std::shared_ptr<view::NGLscene> window;
    window.reset(new view::NGLscene(W, H));
    // and set the OpenGL format
    window->setFormat(format);
    // we can now query the version to see if it worked
    std::cout<<"Profile is "<<format.majorVersion()<<" "<<format.minorVersion()<<"\n";
    // set the window size
    window->resize(1024, 720);
    // and finally show
    window->show();

    controller::IceGenerator controller;
    controller.setup(W, H, window);
    controller.start();

//    std::unique_ptr<frm::Framebuffer> framebuffer(new frm::Framebuffer());
//    framebuffer->init(W, H, NULL);
//    framebuffer->bind();
//    framebuffer->poll();
//    framebuffer->title("IceGrowth");
//    controller::IceGenerator controller(W, H, framebuffer.get());
//    controller.setup();
//    while(!framebuffer->shouldClose())
//    {
//        controller.run();
//    }
    return app.exec();
    //return EXIT_SUCCESS;
}
