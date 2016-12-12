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
    controller::IceGenerator controller(W, H);
    controller.setup();
    while(true)
    {
        controller.run();
    }
    return EXIT_SUCCESS;
}
