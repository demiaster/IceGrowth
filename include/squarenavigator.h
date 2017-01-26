#ifndef MODEL_SQUARENAVIGATOR_H
#define MODEL_SQUARENAVIGATOR_H

#include <random>
#include <tuple>
#include <array>
#include "point.h"
#include "navigator.h"
#include "randomdist.h"

#define TUPLE std::tuple<DiffPoint, DiffPoint>

namespace model
{
    class SquareNavigator : public Navigator
    {
    public:
        SquareNavigator(const std::size_t _width,
                        const std::size_t _height);
        model::Point setOnBorder() override;
        void walk(model::Point& _walker) override;

        template <typename OPERATION>
        inline void onNeighbours(model::Point& _point, OPERATION operation) {
          for (std::size_t i = 0; i < 8; i++) {
            model::Point newPoint = _point;

            newPoint.x += m_neighbour[i].x;
            newPoint.y += m_neighbour[i].y;

            if (0 <= newPoint.x && newPoint.x < m_width &&
                0 <= newPoint.y && newPoint.y < m_height) {
                operation(newPoint);
            }
          }
        }

        template <typename OPERATION>
        void onAxis(model::Point& _point, OPERATION operation)
        {
          for (std::size_t i = 0; i < 2; i++)
          {
            model::Point left = _point,
                         right = _point;
            left.x  += std::get<0>(m_axis[i]).x;
            left.y  += std::get<0>(m_axis[i]).y;
            right.x += std::get<1>(m_axis[i]).x;
            right.y += std::get<1>(m_axis[i]).y;

            if (0 <= left.x && left.x < m_width &&
                0 <= left.y && left.y < m_height &&
                0 <= right.x && right.x < m_width &&
                0 <= right.y && right.y < m_height) {
                operation(left, _point, right);
            }
          }
        }
    private:
        common::IntDistribution m_borderdist, m_neighboursdist;

        //TODO: make this variable static again
        DiffPoint m_neighbour[8] =
                        {{-1, -1},
                          {0, -1},
                          {1, -1},
                          {1, 0},
                          {1, 1},
                          {0, 1},
                          {-1, 1},
                          {-1, 0}};

        std::array<TUPLE, 2> m_axis =
                                    {{TUPLE({-1, 0}, {1, 0}),
                                      TUPLE({0, -1}, {0, 1})}};
    };
}

#endif // MODEL_SQUARENAVIGATOR_H
