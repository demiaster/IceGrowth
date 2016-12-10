#include "icegenerator.h"
#include "point.h"
#include "navigator.h"

#include "image.h"

// random shits
#include <random>
#include <algorithm>
#include <sstream>
#include<iostream>

#define HITTEMPERATURE -100
#define DIFFUSE_K 0.2
#define DIFFUSE_TIME 1.0
#define RESET_TEMPERATURE 1.0

namespace controller
{
    //setup IceGenerator controller

    IceGenerator::IceGenerator(const std::size_t _width,
                    const std::size_t _height) :
        m_heatGrid(_width, _height),
        m_iceGrid(_width, _height),
        m_image(_width, _height)
    {
        m_width = _width;
        m_height = _height;
        setup();
    }

    void IceGenerator::setup()
    {
        // reset the heatgrid to a custom temperature
        m_heatGrid.reset(RESET_TEMPERATURE);
        m_iceGrid.reset(0);
        // set the initial seed of the iceGrid + set the temperature of the seed inside the heatgrid
        m_iceGrid.freeze(m_width / 2, m_height / 2, 1.0);
        m_heatGrid.setTemperature(m_width / 2, m_height / 2, HITTEMPERATURE);
        m_image.clearScreen(0, 0, 0);
        return;
    }

    void IceGenerator::update()
    {
        m_heatGrid.diffuse(DIFFUSE_K, DIFFUSE_TIME);
        m_iceGrid.merge(m_heatGrid);
        this->dla_pattern();

        return;
    }
    void IceGenerator::represent()
    {
        //TODO: represent an iceGrid inside an image a framebuffer or a mesh

        return;
    }

    void IceGenerator::dla_pattern()
    {
        /*
        std::uniform_int_distribution<> distr(-1, 1); // define the range
        std::uniform_int_distribution<> offdistr(0, 2 * (m_width + m_height) - 4);
        std::uniform_real_distribution<> pdistrib(0, 1.0);
        */
        model::Navigator navigator (m_width, m_height);

        //set seed
        m_image.setPixel(m_width / 2, m_height / 2, 255, 255, 255);

        for( int i = 0; i < 1000; ++i)
        {
            //calculating a random index on the frame of the image
            //std::size_t offset = offdistr(eng);

            //converting from that index to the actual x, y values for the random walker
            /*model::Point random_walker = (offset < m_width) ? model::Point{offset, 0} :
                                      (m_width <= offset && offset < m_width + m_height) ? model::Point{m_width - 1, offset - m_width} :
                                      (m_width + m_height <= offset && offset < 2 * m_width + m_height) ?
                                                                                model::Point{offset - m_width - m_height, m_height - 1} :
                                                                                model::Point{0, offset - m_width - m_width - m_height};

            */
            model::Point random_walker = navigator.setOnBorders();
            m_image.setPixel(random_walker.x, random_walker.y, 255, 0, 0);

            int j = 0;
            while(true)
            {
               navigator.walk(random_walker);
               std::cout << "x, y (" << random_walker.x << ", " << random_walker.y << ")\n";

               //random_walker.x = random_walker.x + distr(eng);
               //random_walker.y = random_walker.y + distr(eng);

               //only check upper bounds because of
               //Point unsigned int x, y coordinates
               if(random_walker.x >= m_width || random_walker.y >= m_height)
               {
                   break;
               }
               //PERCENTAGE probability = m_iceGrid.hit(random_walker.x, random_walker.y);
               else if(m_image.hit(random_walker.x, random_walker.y, 255, 255, 255))
               {
                   //ONLY TO TEST AGAIN NORMAL BEHAVIOUR
                   //std::cout << "x, y (" << random_walker.x << ", " << random_walker.y << ")\n";
                   m_image.setPixel(random_walker.x,
                                  random_walker.y,
                                  255, 255, 255);
                   break;
               }
               //TODO: figure out why this breaks everything
               /*if(probability > pdistrib(eng))
               {
                   m_iceGrid.freeze(random_walker.x, random_walker.y, probability);
                   m_image.setPixel(random_walker.x,
                                  random_walker.y,
                                  255, 255, 255);
                   break;
               }
               */
               ++j;
               m_image.setPixel(random_walker.x, random_walker.y, 255 - (j % 255), 0, 0);
            }
        }
        m_image.save("dla_controller_navigator.png");
        return;
    }
}
