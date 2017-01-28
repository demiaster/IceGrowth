#include "icegenerator.h"
#include "point.h"
#include "squarenavigator.h"
#include "image.h"

// random shits
#include <random>
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#define HITTEMPERATURE -100
#define DIFFUSE_K 0.34
//#define DIFFUSE_TIME 1.0/(3*100000000)
#define DIFFUSE_TIME 1.0/(1000000)
#define RESET_TEMPERATURE 1.0

namespace controller
{
    //setup IceGenerator controller

    IceGenerator::IceGenerator(){}

    void IceGenerator::run()
    {
        connect(this, SIGNAL(imageChanged()),
                m_window.get(), SLOT(setImage()));
        while(true)
        {
#ifdef GRAPHICSDEBUG
            std::cout << "run\n";
#endif
            update();
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            representNGL();
        }
    }

    void IceGenerator::setup(const std::size_t _width,
                             const std::size_t _height,
                             std::shared_ptr<view::NGLscene> _window)
    {
        m_window = _window;
        setup(_width, _height);
    }

    void IceGenerator::setup(const std::size_t _width,
                             const std::size_t _height)
    {
        m_width = _width;
        m_height = _height;
        m_navigator.reset(new model::HexNavigator(_width, _height));
        m_image.reset(new view::Image (m_width, m_height));
        m_image->setBackgroundColor(255, 0, 0);
        m_image->clearScreen(255, 0, 0);

        //initialising all other grids
        m_iceGrid.reset(new model::IceGrid(m_width, m_height));
        m_heatGrid.reset(new model::HeatGrid(m_width, m_height));

        // reset the heatgrid to a custom temperature
        m_heatGrid->reset(RESET_TEMPERATURE);
        m_heatGrid->inspect();
        m_iceGrid->reset(0);

        // set the initial seed of the iceGrid + set the temperature of the seed inside the heatgrid
        m_iceGrid->freeze(m_width / 2, m_height / 2, 1.0);
        m_heatGrid->setTemperature(m_width / 2, m_height / 2, HITTEMPERATURE);
        m_heatGrid->inspect();
        m_iceGrid->inspect();
        return;
    }

    void IceGenerator::update()
    {
        m_heatGrid->diffuse(DIFFUSE_K, DIFFUSE_TIME, m_navigator);
        //to avoid melting
        m_heatGrid->setMinTemp();
#ifdef LOG
        std::cout<< "minTemp before merge " << m_heatGrid->getMinTemp()<<std::endl;
#endif
        m_heatGrid->inspect();
        m_iceGrid->merge(m_heatGrid.get());

        m_heatGrid->setMinTemp();
#ifdef LOG
        std::cout<< "minTemp after merge " << m_heatGrid->getMinTemp()<<std::endl;
#endif
        this->dla_pattern();
        m_heatGrid->setMinTemp();
#ifdef LOG
        std::cout<< "minTemp after dla " << m_heatGrid->getMinTemp()<<std::endl;
#endif
        m_heatGrid->inspect();
        m_iceGrid->inspect();
        return;
    }

    void IceGenerator::representNGL()
    {
        NUMBER temperature;
        NUMBER minTemp = m_heatGrid->getMinTemp();
        std::size_t ice;

        for (std::size_t i = 0; i < m_width; ++i)
        {
            for (std::size_t j = 0; j < m_height; ++j)
            {
                temperature = m_heatGrid->getTemperature(i, j);
                if (temperature < 0)
                {
                    ice = COLOR - (temperature - minTemp)/(RESET_TEMPERATURE - minTemp) * DIFFCOLOR;
#ifdef LOG
                    std::cout << "Represent ice: " << ice << std::endl;
                    std::cout << "Temp ice: " << temperature << std::endl;
                    std::cout << "Mintemp ice: " << minTemp << std::endl;
#endif
                    //set mesh cell's colour
                    m_image->setPixel(i, j, ice, ice, ice);
                }
                else
                {
                  m_image->resetPixelColor(i, j);
                }
            }
        }
#ifdef HIT
        m_image->save("/tmp/test.png");
#endif
        m_window->feed(m_width, m_height, m_image);
        emit imageChanged();
        return;
    }

    void IceGenerator::dla_pattern()
    {
        model::Point random_walker = m_navigator->setOnBorder();
        bool hit = false;

        while (!hit)
        {
            m_navigator->walk(random_walker);
            m_navigator->onNeighbours(random_walker, [&hit,this](model::Point n) {
                if (this->m_heatGrid->getTemperature(
                    n.x, n.y) < -1.0) {
                    hit = true;
                }
            });

            if (hit) {
                m_heatGrid->setTemperature(random_walker.x, random_walker.y, HITTEMPERATURE);
                break;
            }
        }
        return;
    }
}

