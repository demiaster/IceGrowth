#ifndef MODEL_ICEGRID_H
#define MODEL_ICEGRID_H

#include "grid.h"
#include "heatgrid.h"
#include "common.h"
#include "navigator.h"
#include <iostream>

namespace model
{


    class IceGrid : public Grid<PERCENTAGE, 2>
    {
    public:
        IceGrid(const std::size_t _width,
                const std::size_t _height);
        void freeze(std::size_t x, std::size_t y, PERCENTAGE _percentage);
        template <typename NAVIGATOR>
        PERCENTAGE hit(std::size_t _x, std::size_t _y, NAVIGATOR navigator) const
        {
            //voglio evitare di ghiacciare più volte una casella già ghiacchiata
            //se una casella è già ghiacciata, la sua temperatura è < 0
            //di conseguenza sulla icegrid la sua probabilità di ghiacciamento
            //usata in realtà per calcolare se una vicina non ghiacciata debba ghiacciare
            //è diversa da 0
            //in conclusione: se la casella su cui sono ha una prob !=0, allora è già ghiacciata
            if(this->get({{_x, _y}}))
                return 0;

            Point p = {_x, _y};
            int neighbours = 0;
            PERCENTAGE accum = 0;
            //such lambda, much wow
            navigator->onNeighbours(p, [this, &accum, &neighbours](Point point)
            {
                ++neighbours;
                accum += this->get({{point.x, point.y}});
//                std::cout << "result of this->get" << this->get({{point.x, point.y}}) << std::endl;
//                std::cout<< "point position " << point.x << " " << point.y <<std::endl;
//                std::cout<< "neighbour count" << neighbours << std::endl;
//                std::cout<< "accum count" << accum<< std::endl;
//                std::cout<< "return value count" << accum / neighbours << std::endl;
            });
//            return neighbours > 0 ?
//                        accum / neighbours : 0;
            return accum > 0 ? 1 :0;
        }

        void merge(HeatGrid* _heatGrid);
    private:
        std::size_t m_width, m_height;
    };
}
#endif // MODEL_ICEGRID_H
