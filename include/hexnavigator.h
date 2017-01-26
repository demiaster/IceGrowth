#ifndef MODEL_HEXNAVIGATOR_H
#define MODEL_HEXNAVIGATOR_H

#include <tuple>
#include "navigator.h"
#include "randomdist.h"
#include "common.h"

#define TUPLE std::tuple<DiffPoint, DiffPoint>

namespace model
{
    class HexNavigator : public Navigator
    {
    public:
        HexNavigator(const std::size_t _width,
                     const std::size_t _height);
        model::Point setOnBorder() override;
        void walk(model::Point& _walker) override;
        template <typename OPERATION>
        inline void onNeighbours(model::Point& _point, OPERATION operation) {
          DiffPoint (&m_point)[6] = _point.x % 2 ? m_point_even : m_point_odd;

          for (std::size_t i = 0; i < 6; i++) {
            model::Point newPoint = _point;

            newPoint.x += m_point[i].x;
            newPoint.y += m_point[i].y;

            if (0 <= newPoint.x && newPoint.x < m_width &&
                0 <= newPoint.y && newPoint.y < m_height) {
                operation(newPoint);
            }
          }
        }
    private:
        //common::RandomDist& m_randomdist;
        common::IntDistribution m_borderdist, m_neighboursdist;

        // for even column index
        //TODO: make this variable static again
        DiffPoint m_point_even[6] =
                        {{0, -1},
                          {1, -1},
                          {1, 0},
                          {0, 1},
                          {-1, 0},
                          {-1, -1}};
        // for odd column index
        //TODO: make this variable static again
        DiffPoint m_point_odd[6] =
                        {{0, -1},
                          {1, 0},
                          {1, 1},
                          {0, 1},
                          {-1, 1},
                          {-1, 0}};
        std::array<TUPLE, 3> m_axis_even =
                                            {{TUPLE({-1, -1}, {1, 0}),
                                              TUPLE({-1, 0}, {1, -1}),
                                              TUPLE({0, -1}, {0, 1})}};
        std::array<TUPLE, 3> m_axis_odd =
                                            {{TUPLE({-1, 0}, {1, 1}),
                                              TUPLE({-1, 1}, {1, 0}),
                                              TUPLE({0, -1}, {0, 1})}};
    };
}
#endif //MODEL_HEXNAVIGATOR_H
