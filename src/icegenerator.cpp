#include "icegenerator.h"
#include "point.h"

#include "Image.h"

// random shits
#include <random>
#include <algorithm>
#include <sstream>

#define HITTEMPERATURE -100
#define DIFFUSE_K 0.2
#define DIFFUSE_TIME 1.0
#define RESET_TEMPERATURE 1.0

namespace controller {
    //setup IceGenerator controller

    void IceGenerator::setup() {
        // reset the heatgrid to a custom temperature
        m_heatGrid.reset(RESET_TEMPERATURE);
        // set the initial seed of the iceGrid + set the temperature of the seed inside the heatgrdi
        m_iceGrid.freeze(m_width / 2, m_height / 2, 1.0);
        m_heatGrid.setTemperature(m_width / 2, m_height / 2, HITTEMPERATURE);

        return;
    }

    void IceGenerator::update() {
        m_heatGrid.diffuse(DIFFUSE_K, DIFFUSE_TIME);
        m_iceGrid.merge(m_heatGrid);
        //DLA here
        this->dla_pattern();

        return;
    }
    void IceGenerator::represent() {
        //TODO: represent an iceGrid inside an image a framebuffer or a mesh

        return;
    }

    void IceGenerator::dla_pattern() {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distr(-1, 1); // define the range
        std::uniform_int_distribution<> offdistr(0, 2 * (m_width + m_height) - 4);
        std::uniform_real_distribution<> pdistrib(0, 1.0);

        std::size_t offset = offdistr(eng);

            model::Point random_walker = (offset < m_width) ?             model::Point{offset, 0} :
                                  (m_width <= offset && offset < m_width + m_height) ?         model::Point{W - 1, offset - m_width} :
                                  (m_width + m_height <= offset && offset < 2 * m_width + m_height) ? model::Point{offset - m_width - m_height, m_height - 1} :
                                                                            model::Point{0, offset - m_width - m_width - m_height};

            int j = 0;
            while(true)
            {

                random_walker.x = random_walker.x + distr(eng);
                random_walker.y = random_walker.y + distr(eng);

                //only check upper bounds because of
                //Point unsigned int x, y coordinates
                if(random_walker.x >= m_width || random_walker.y >= m_height)
                {
                    break;
                }
                PERCENTAGE probability = m_iceGrid.hit(random_walker.x, random_walker.y);
                if(probability > pdistrib(eng))
                {
                    m_iceGrid.freeze(random_walker.x, random_walker.y, probability);

                    break;
                }
                ++j;
            }
        return;
    }
}
