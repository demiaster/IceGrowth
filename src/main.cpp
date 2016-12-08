#include "point.h"
#include "image.h"
#include <cstdlib>
#include <iostream>

// random shits
#include <random>
#include <algorithm>
#include <sstream>

//constexpr int WIDTH = 1920;
//constexpr int HEIGHT = 1080;
//constexpr int DEPTH = 3;
void dla_pattern();

int main()
{
    dla_pattern();

    return EXIT_SUCCESS;
}

void dla_pattern()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-1, 1); // define the range
    std::uniform_int_distribution<> offdistr(0, 2 * (W + H) - 4);

    view::Image image(W, H);
    image.clearScreen(0, 0, 0);

    //set seed
    image.setPixel(W / 2, H / 2, 255, 255, 255);

    for( int i = 0; i < 10000000; ++i)
    {
        std::size_t offset = offdistr(eng);

        model::Point random_walker = (offset < W) ?             model::Point{offset, 0} :
                              (W <= offset && offset < W + H) ?         model::Point{W - 1, offset - W} :
                              (W + H <= offset && offset < 2 * W + H) ? model::Point{offset - W - H, H - 1} :
                                                                        model::Point{0, offset - W - W - H};

        image.setPixel(random_walker.x, random_walker.y, 255, 0, 0);
        int j = 0;
        while(true)
        {

            random_walker.x = random_walker.x + distr(eng);
            random_walker.y = random_walker.y + distr(eng);

            //only check upper bounds because of
            //Point unsigned int x, y coordinates
            if(random_walker.x >= W || random_walker.y >= H)
            {
                break;
            }
            else if(image.hit(random_walker.x, random_walker.y, 255, 255, 255))
            {
                //std::cout << "x, y (" << random_walker.x << ", " << random_walker.y << ")\n";
                image.setPixel(random_walker.x,
                               random_walker.y,
                               255, 255, 255);
                break;
            }
            ++j;
            image.setPixel(random_walker.x, random_walker.y, 255 - (j % 255), 0, 0);
        }
    }
    image.save("dla.png");
    return;
}
