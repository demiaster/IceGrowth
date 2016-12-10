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
#define DIFFUSE_K 0.002
#define DIFFUSE_TIME 1.0
#define RESET_TEMPERATURE 1.0

namespace controller
{
    //setup IceGenerator controller

    IceGenerator::IceGenerator(const std::size_t _width,
                    const std::size_t _height)
    {
        m_width = _width;
        m_height = _height;
    }

    void IceGenerator::setup()
    {
        m_image.reset(new view::Image (m_width, m_height));
        m_iceGrid.reset(new model::IceGrid(m_width, m_height));
        m_heatGrid.reset(new model::HeatGrid(m_width, m_height));
        // reset the heatgrid to a custom temperature
        m_heatGrid->reset(RESET_TEMPERATURE);
        m_heatGrid->inspect();
        m_iceGrid->reset(0);
        // set the initial seed of the iceGrid + set the temperature of the seed inside the heatgrid
        m_iceGrid->freeze(m_width / 2, m_height / 2, 1.0);
        m_heatGrid->setTemperature(m_width / 2, m_height / 2, -10);
        m_heatGrid->inspect();
        m_iceGrid->inspect();
        m_image->clearScreen(0, 0, 0);
        return;
    }

    void IceGenerator::update()
    {
        m_heatGrid->diffuse(DIFFUSE_K, DIFFUSE_TIME);
        //to avoid melting
        m_iceGrid->freeze(m_width / 2, m_height / 2, 1.0);
        m_heatGrid->setTemperature(m_width / 2, m_height / 2, -10);

        m_heatGrid->inspect();
        m_iceGrid->merge(m_heatGrid.get());
        this->dla_pattern();
        m_heatGrid->inspect();
        m_iceGrid->inspect();
        return;
    }
    void IceGenerator::represent()
    {
        //TODO: represent an iceGrid inside an image a framebuffer or a mesh
        float temperature;
        std::size_t ice;
        for (std::size_t i = 0; i < m_width; ++i)
        {
            for (std::size_t j = 0; j < m_height; ++j)
            {
                temperature = m_heatGrid->getTemperature(i, j);
                if (temperature < 0)
                {
                    ice = 255 - (temperature - HITTEMPERATURE)/(RESET_TEMPERATURE - HITTEMPERATURE) * 255;
                    m_image->setPixel(i, j, 255, 255, 255);
                }
            }
        }
        m_image->save("represent_function.png");
        return;
    }

    void IceGenerator::dla_pattern()
    {
        model::Navigator navigator (m_width, m_height);
        model::Point random_walker = navigator.setOnBorder();

        while(true)
        {
            navigator.walk(random_walker);
            PERCENTAGE probability = m_iceGrid->hit(random_walker.x, random_walker.y);

#ifdef TRACE
            std::cout<<"IceGrid status\n";
            m_iceGrid->inspect();
            std::cout << "DLA Probability: (" << random_walker.x << ", " << random_walker.y << "), " <<
              probability << "\n";
#endif
            if(navigator.isFreezable(probability))
            {
                m_iceGrid->freeze(random_walker.x, random_walker.y, probability);
                m_heatGrid->setTemperature(random_walker.x, random_walker.y, HITTEMPERATURE);
#ifdef DEBUG
                std::cout << "Freeze: (" << random_walker.x << ", " << random_walker.y << ")\n";
#endif
                break;
            }
        }
        return;
    }
}
