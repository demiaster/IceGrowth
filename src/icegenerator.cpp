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
        model::Navigator navigator (m_width, m_height);
        model::Point random_walker = navigator.setOnBorder();

        while(true)
        {
            navigator.walk(random_walker);
            std::cout << "x, y (" << random_walker.x << ", " << random_walker.y << ")\n";
            //PERCENTAGE probability = m_iceGrid.hit(random_walker.x, random_walker.y);
            if(m_image.hit(random_walker.x, random_walker.y, 255, 255, 255))
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
        }
        return;
    }
}
