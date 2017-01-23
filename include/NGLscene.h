#ifndef NGLSCENE_H
#define NGLSCENE_H

#include <ngl/Camera.h>
#include <QOpenGLWindow>
#include "windowparam.h"
#include "image.h"
#include "point.h"

namespace view
{
    class NGLscene : public QOpenGLWindow
    {Q_OBJECT
    public:
        NGLscene(std::size_t _width, std::size_t _height);
        ~NGLscene();
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int _w, int _h) override;
        void buildMesh(std::size_t _width, std::size_t _height, std::shared_ptr<view::Image> _image);
        void NGLupdate();
        void feed(std::size_t _width, std::size_t _height, std::shared_ptr<view::Image> _image);

    public slots:
        void setImage();

    private:

        std::size_t m_width;
        std::size_t m_height;
        std::shared_ptr<view::Image> m_image;
        //window stuff
        WinParams m_win;

        //ngl drawing and visualizing stuff
        ngl::Mat4 m_view;
        ngl::Camera m_cam;
        ngl::Mat4 m_projection;
        std::unique_ptr<ngl::AbstractVAO> m_vao;
        size_t m_nVerts;

        //mouse stuff
        ngl::Vec3 m_modelPos;
        ngl::Mat4 m_mouseGlobalTX;

        void timerEvent(QTimerEvent *) override;
        void keyPressEvent(QKeyEvent *_event) override;
        void mouseMoveEvent(QMouseEvent * _event) override;
        void mousePressEvent(QMouseEvent *_event) override;
        void mouseReleaseEvent(QMouseEvent *_event) override;
        void wheelEvent(QWheelEvent *_event) override;
    };
}
#endif //NGLSCENE_H
