#ifndef NGLSCENE_H
#define NGLSCENE_H

#include <ngl/Camera.h>
#include <QOpenGLWindow>
#include "windowparam.h"

namespace view
{
    class NGLScene : public QOpenGLWindow
    {
    public:
        NGLScene();
        ~NGLScene();
        void initializeGL();
        void paintGL();
        void resizeGL(int _w, int _h);
    private:
        //ngl drawing and visualizing stuff
        ngl::Camera m_cam;
        std::unique_ptr<ngl::AbstractVAO> m_vao;

        //window stuff
        WinParams m_win;

        //mouse stuff
        ngl::Vec3 m_modelPos;
        ngl::Mat4 m_mouseGlobalTX;

        void keyPressEvent(QKeyEvent *_event);
        void mouseMoveEvent(QMouseEvent * _event);
        void mousePressEvent(QMouseEvent *_event);
        void mouseReleaseEvent(QMouseEvent *_event);
        void wheelEvent(QWheelEvent *_event);
    };
}
#endif //NGLSCENE_H
