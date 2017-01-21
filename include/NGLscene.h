#ifndef NGLSCENE_H
#define NGLSCENE_H

#include <ngl/Camera.h>
#include <QOpenGLWindow>
#include "windowparam.h"

namespace view
{
    class NGLscene : public QOpenGLWindow
    {
    public:
        NGLscene();
        ~NGLscene();
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int _w, int _h) override;
    private:
        //window stuff
        WinParams m_win;

        //ngl drawing and visualizing stuff
        ngl::Mat4 m_view;
        ngl::Camera m_cam;
        ngl::Mat4 m_projection;
        std::unique_ptr<ngl::AbstractVAO> m_vao;
        size_t m_nVerts;

        void buildMesh(ngl::Real _width, ngl::Real _height);
        void timerEvent(QTimerEvent *);

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
