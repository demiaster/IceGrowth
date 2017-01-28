#ifndef NGLSCENE_H
#define NGLSCENE_H
/// @file NGLscene.h
/// @brief this class handles the openGL context

#include <ngl/Camera.h>
#include <QOpenGLWindow>

#include "windowparam.h"
#include "image.h"
#include "point.h"

namespace view
{

///----------------------------------------------------------------------------
/// @file NGLscene.h
/// @brief this class inherits from the Qt OpenGLWindow and allows us to use
/// NGL to draw OpenGL
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/9/13
/// Revision History :
/// This is an initial version used for the new NGL6 / Qt 5 demos
/// @class NGLScene
/// @brief our main glwindow widget for NGL applications all drawing elements
/// are put in this file
///----------------------------------------------------------------------------
class NGLscene : public QOpenGLWindow
{Q_OBJECT
public:

    ///------------------------------------------------------------------------
    /// @brief ctor for our NGL drawing class
    /// @param [in] parent the parent window to the class
    /// @param [in] _width width of the grid
    /// @param [in] _height height of the grid
    ///------------------------------------------------------------------------
    NGLscene(std::size_t _width, std::size_t _height);

    ///------------------------------------------------------------------------
    /// @brief dtor must close down ngl and release OpenGL resources
    ///------------------------------------------------------------------------
    ~NGLscene();

    ///------------------------------------------------------------------------
    /// @brief the initialize class is called once when the window is created
    /// and we have a valid GL context use this to setup any default GL stuff
    ///------------------------------------------------------------------------
    void initializeGL() override;

    ///------------------------------------------------------------------------
    /// @brief this is called everytime we want to draw the scene
    ///------------------------------------------------------------------------
    void paintGL() override;

    ///------------------------------------------------------------------------
    /// @brief this is called everytime we want to draw the scene
    ///------------------------------------------------------------------------
    void resizeGL(int _w, int _h) override;

    ///------------------------------------------------------------------------
    /// @brief build the hexagonal lattice on which the ice will be represented
    /// @param [in] _width number of hexagons in the width for the mesh
    /// @param [in] _height number of hexagons in the height for the mesh
    ///------------------------------------------------------------------------
    void buildMesh(std::size_t _width, std::size_t _height,
                   std::shared_ptr<view::Image> _image);

    ///------------------------------------------------------------------------
    /// @brief gets the new color grid for the mesh
    /// @param [in] _width width of the grid
    /// @param [in] _height height of the grid
    ///------------------------------------------------------------------------
    void feed(std::size_t _width, std::size_t _height,
              std::shared_ptr<view::Image> _image);

public slots:
    void setImage();

private:

    /// -----------------------------------------------------------------------
    /// @brief width of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_width;

    /// -----------------------------------------------------------------------
    /// @brief height of the grid
    /// -----------------------------------------------------------------------
    std::size_t m_height;

    /// -----------------------------------------------------------------------
    /// @brief colors grid
    /// -----------------------------------------------------------------------
    std::shared_ptr<view::Image> m_image;

    //window stuff
    /// -----------------------------------------------------------------------
    /// @brief used to store the x rotation mouse value
    /// -----------------------------------------------------------------------
    WinParams m_win;

    /// -----------------------------------------------------------------------
    /// @brief camera transform matrix
    /// -----------------------------------------------------------------------
    ngl::Mat4 m_view;

    ///------------------------------------------------------------------------
    /// @brief camera
    ///------------------------------------------------------------------------
    ngl::Camera m_cam;

    /// -----------------------------------------------------------------------
    /// @brief camera projection matrix
    /// -----------------------------------------------------------------------
    ngl::Mat4 m_projection;

    /// -----------------------------------------------------------------------
    ///@brief VAO for the mesh
    /// -----------------------------------------------------------------------
    std::unique_ptr<ngl::AbstractVAO> m_vao;

    /// -----------------------------------------------------------------------
    ///@brief number of vertices
    /// -----------------------------------------------------------------------
    size_t m_nVerts;

    //mouse stuff
    ///------------------------------------------------------------------------
    /// @brief the model position for mouse movement
    ///------------------------------------------------------------------------
    ngl::Vec3 m_modelPos;

    ///------------------------------------------------------------------------
    /// @brief used to store the global mouse transforms
    ///------------------------------------------------------------------------
    ngl::Mat4 m_mouseGlobalTX;

    /// -----------------------------------------------------------------------
    ///@brief timer to repaint the scene
    /// -----------------------------------------------------------------------
    void timerEvent(QTimerEvent *) override;

    /// -----------------------------------------------------------------------
    /// @brief Qt Event called when a key is pressed
    /// @param [in] _event the Qt event to query for size etc
    /// -----------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *_event) override;

    /// -----------------------------------------------------------------------
    /// @brief this method is called every time a mouse is moved
    /// @param _event the Qt Event structure
    /// -----------------------------------------------------------------------
    void mouseMoveEvent(QMouseEvent * _event) override;

    /// -----------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is pressed
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    /// -----------------------------------------------------------------------
    void mousePressEvent(QMouseEvent *_event) override;

    //// -----------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is released
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    /// -----------------------------------------------------------------------
    void mouseReleaseEvent(QMouseEvent *_event) override;

    /// -----------------------------------------------------------------------
    /// @brief this method is called everytime the mouse wheel is moved
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    /// -----------------------------------------------------------------------
    void wheelEvent(QWheelEvent *_event) override;
};
} //end namespace view
#endif //NGLSCENE_H
