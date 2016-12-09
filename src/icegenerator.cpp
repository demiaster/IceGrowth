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
#define DIFFUSE_K 0.34
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
    }

    void IceGenerator::setup()
    {
        // reset the heatgrid to a custom temperature
        m_heatGrid.reset(RESET_TEMPERATURE);
        //TODO: implement this
        m_iceGrid.reset((RESET_TEMPERATURE <= 0) ? 1.0 : 0.0);
        // set the initial seed of the iceGrid + set the temperature of the seed inside the heatgrid
        m_iceGrid.freeze(m_width / 2, m_height / 2, 1.0);
        m_heatGrid.setTemperature(m_width / 2, m_height / 2, HITTEMPERATURE);
        m_image.setPixel(m_width / 2, m_height / 2, 255, 255, 255);
        m_image.clearScreen(0, 0, 0);
        return;
    }

    model::Point IceGenerator::update()
    {
        m_heatGrid.diffuse(DIFFUSE_K, DIFFUSE_TIME);
        m_iceGrid.merge(m_heatGrid);
        model::Point new_frozen = this->dla_pattern();

        return new_frozen;
    }
    void IceGenerator::represent(model::Point _new_frozen)
    {
        //TODO: represent an iceGrid inside an image a framebuffer or a mesh
        m_image.setPixel(_new_frozen.x, _new_frozen.x, 255, 255, 255);
        m_image.save("dla_controller_navigator.png");
        return;
    }

    model::Point IceGenerator::dla_pattern()
    {
        model::Navigator navigator (m_width, m_height);

        for( int i = 0; i < 100; ++i)
        {
            //create new random walker
            model::Point random_walker = navigator.setOnBorder();
            //m_image.setPixel(random_walker.x, random_walker.y, 255, 0, 0);

            int j = 0;
            while(true)
            {
               if(navigator.walk(random_walker))
               {
                    std::cout << "x, y (" << random_walker.x << ", " << random_walker.y << ")\n";
                    PERCENTAGE probability = m_iceGrid.hit(random_walker.x, random_walker.y);
                    if(navigator.isFreezable(probability))
                    {
//                        //checking if neighbour are frozen
//                        for(auto i = -1; i <= 1; ++i)
//                        {
//                            for(auto j = -1; j <= 1; ++j)
//                            {
//                                //checking also validity of boundaries
//                                if((random_walker.x + i) <= m_width &&
//                                   (random_walker.y + j) <= m_height)// &&
//                                   (m_iceGrid.get({{random_walker.x + i, random_walker.y + j}}) > 0.5))
                                {
                                      m_iceGrid.freeze(random_walker.x, random_walker.y, probability);
                                        m_image.setPixel(random_walker.x,
                                                         random_walker.y,
                                                         255, 255, 255);
                                      std::cout<<"hit for: "<<random_walker.x<< ' ' <<random_walker.y<<std::endl;
                                      //return random_walker;
                                      break;
                                }
//                            }
//                        }
                     }
               }
//               else
//               {
//                   random_walker = navigator.setOnBorder();
//               }

              //only check upper bounds because of
               //Point unsigned int x, y coordinates
               //porta dentro la walk questo controllo nella walk
//               if(random_walker.x >= m_width || random_walker.y >= m_height)
//               {
//                   break;
//               }


//                    PERCENTAGE probability = m_iceGrid.hit(random_walker.x, random_walker.y);

//               else if(m_image.hit(random_walker.x, random_walker.y, 255, 255, 255))
//               {
//                   //ONLY TO TEST AGAIN NORMAL BEHAVIOUR
//                   //std::cout << "x, y (" << random_walker.x << ", " << random_walker.y << ")\n";
//                   m_image.setPixel(random_walker.x,
//                                  random_walker.y,
//                                  255, 255, 255);
//                   break;
//               }
               //TODO: figure out why this breaks everything
//               if(navigator.isFreezable(probability))
//               {
//                   //checking if neighbour are frozen
//                   for(auto i = -1; i <= 1; ++i)
//                   {
//                       for(auto j = -1; j <= 1; ++j)
//                       {
//                           //checking also validity of boundaries
//                           if((random_walker.x + i) <= m_width &&
//                              (random_walker.y + j) <= m_height &&
//                              (m_iceGrid.get({{random_walker.x + i, random_walker.y + j}}) > 0.9))

//                                   m_iceGrid.freeze(random_walker.x, random_walker.y, probability);
//                                   m_image.setPixel(random_walker.x,
//                                                    random_walker.y,
//                                                    255, 255, 255);
//                                   std::cout<<"hit for: "<<random_walker.x<< ' ' <<random_walker.y<<std::endl;
//                                   break;
//                       }
//                   }
//               }

//               ++j;
//               //m_image.setPixel(random_walker.x, random_walker.y, 255 - (j % 255), 0, 0);
//            }

            }
            return random_walker;
        }
    }
}
