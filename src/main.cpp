#include "point.h"
#include "image.h"
#include <cstdlib>
#include <iostream>

// random shits
#include <random>
#include <algorithm>
#include <sstream>

#include "icegenerator.h"

static const size_t W = 401;
static const size_t H = 401;

int main()
{
    std::unique_ptr<frm::Framebuffer> framebuffer(new frm::Framebuffer());
    framebuffer->init(W, H, NULL);
    framebuffer->bind();
    framebuffer->poll();
    framebuffer->title("IceGrowth");
    controller::IceGenerator controller(W, H, framebuffer.get());
    controller.setup();
    while(!framebuffer->shouldClose())
    {
        controller.run();
    }
    return EXIT_SUCCESS;
}
