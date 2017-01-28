#ifndef CONTROLLER_ICEGENERATOR_H
#define CONTROLLER_ICEGENERATOR_H
/// @file icegenerator.h
/// @brief this class is the controller for the whole project

#include <memory>
#include <QThread>
#include "heatgrid.h"
#include "icegrid.h"
#include "image.h"
#include "hexnavigator.h"
#include "squarenavigator.h"
#include "randomdist.h"
#include "NGLscene.h"

namespace controller
{

///----------------------------------------------------------------------------
/// @class Grid "include/icegenerator.h"
/// @author Marta Feriani
/// @brief This class contains the logic of the application. It is in charge of
/// starting the simulation by initialising all the data structures
/// and running the simulation. IceGenerator holds a reference
/// to every instance of the model objects, as well as every member of the view
/// and moves information from one class to the other.
///----------------------------------------------------------------------------
class IceGenerator : public QThread
{ Q_OBJECT
public:

    ///------------------------------------------------------------------------
    /// @brief constructor
    /// -----------------------------------------------------------------------
    IceGenerator();

    ///------------------------------------------------------------------------
    /// @brief starts the simulation
    /// -----------------------------------------------------------------------
    void run();

    ///------------------------------------------------------------------------
    /// @brief setup the initial state for the simulation, get a reference
    /// for the openGL context
    /// @param [in] _width width of the grid
    /// @param [in] _height height of the grid
    /// @param [in] _window openGL context
    /// -----------------------------------------------------------------------
    void setup(const std::size_t _width,
               const std::size_t _height,
               std::shared_ptr<view::NGLscene> _window);

    ///------------------------------------------------------------------------
    /// @brief setup the initial state for the simulation
    /// @param [in] _width width of the grid
    /// @param [in] _height height of the grid
    /// -----------------------------------------------------------------------
    void setup(const std::size_t _width,
               const std::size_t _height);

signals:
    void imageChanged();

private:

    ///------------------------------------------------------------------------
    /// @brief runs the algorithms to simulate the ice growth
    /// -----------------------------------------------------------------------
    void update();

    ///------------------------------------------------------------------------
    /// @brief passes new model state to openGL
    /// -----------------------------------------------------------------------
    void representNGL();

    ///------------------------------------------------------------------------
    /// @brief implements the DLA brownian walk
    /// -----------------------------------------------------------------------
    void dla_pattern();

    /// -----------------------------------------------------------------------
    /// @brief width of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_width;

    /// -----------------------------------------------------------------------
    /// @brief height of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_height;

    /// -----------------------------------------------------------------------
    /// @brief grid of temperatures
    /// -----------------------------------------------------------------------
    std::unique_ptr<model::HeatGrid> m_heatGrid;

    /// -----------------------------------------------------------------------
    /// @brief grid containing ice state for each position
    /// -----------------------------------------------------------------------
    std::unique_ptr<model::IceGrid> m_iceGrid;

    /// -----------------------------------------------------------------------
    /// @brief grid containing the colors to be applied to the ice
    /// -----------------------------------------------------------------------
    std::shared_ptr<view::Image> m_image;

    /// -----------------------------------------------------------------------
    /// @brief openGL context
    /// -----------------------------------------------------------------------
    std::shared_ptr<view::NGLscene> m_window;

    /// -----------------------------------------------------------------------
    /// @brief contains the rules to move on a lattice
    /// -----------------------------------------------------------------------
    std::shared_ptr<model::HexNavigator> m_navigator;
};
} // end namespace controller

#endif // CONTROLLER_ICEGENERATOR_H
