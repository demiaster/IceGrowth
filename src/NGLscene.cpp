#include <QMouseEvent>
#include <QGuiApplication>
#include "NGLscene.h"

namespace view
{
    void NGLScene::mouseMoveEvent(QMouseEvent* _event)
    {
        // note the method buttons() is the button state when event was called
        // that is different from button() which is used to check which button was
        // pressed when the mousePress/Release event is generated
        if(m_win.rotate && _event->buttons() == Qt::LeftButton)
        {
            int diffx = _event->x() - m_win.origX;
            int diffy = _event->y() - m_win.origY;
            m_win.spinXFace += static_cast<int>(0.5f * diffy);
            m_win.spinYFace += static_cast<int>(0.5f * diffx);
            m_win.origX = _event->x();
            m_win.origY = _event->y();
            update();
        }
        // right mouse translate code
        else if(m_win.translate && _event->buttons() == Qt::RightButton)
        {
            int diffX      = static_cast<int>(_event->x() - m_win.origXPos);
            int diffY      = static_cast<int>(_event->y() - m_win.origYPos);
            m_win.origXPos = _event->x();
            m_win.origYPos = _event->y();
            m_modelPos.m_x += INCREMENT * diffX;
            m_modelPos.m_y -= INCREMENT * diffY;
            update();
        }
    }

    void NGLScene::mousePressEvent(QMouseEvent* _event)
    {
        // that method is called when the mouse button is pressed in this case we
        // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
        if(_event->button() == Qt::LeftButton)
        {
            m_win.origX  = _event->x();
            m_win.origY  = _event->y();
            m_win.rotate = true;
        }
        // right mouse translate mode
        else if(_event->button() == Qt::RightButton)
        {
            m_win.origXPos  = _event->x();
            m_win.origYPos  = _event->y();
            m_win.translate = true;
        }
    }

    void NGLScene::mouseReleaseEvent(QMouseEvent* _event)
    {
        // that event is called when the mouse button is released
        // we then set Rotate to false
        if(_event->button() == Qt::LeftButton)
        {
            m_win.rotate = false;
        }
        // right mouse translate mode
        if(_event->button() == Qt::RightButton)
        {
            m_win.translate = false;
        }
    }

    void NGLScene::wheelEvent(QWheelEvent* _event)
    {

        // check the diff of the wheel position (0 means no change)
        if(_event->delta() > 0)
        {
            m_modelPos.m_z += ZOOM;
        }
        else if(_event->delta() < 0)
        {
            m_modelPos.m_z -= ZOOM;
        }
        update();
    }

    void NGLScene::keyPressEvent(QKeyEvent *_event)
    {
        // this method is called every time the main window recives a key event.
        // we then switch on the key value and set the camera in the GLWindow
        switch(_event->key())
        {
            // escape key to quite
            case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
                // turn on wirframe rendering
            case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
                // turn off wire frame
            case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
                // show full screen
            case Qt::Key_F : showFullScreen(); break;
                // show windowed
            case Qt::Key_N : showNormal(); break;
            default : break;
        }
        // finally update the GLWindow and re-draw
        //if (isExposed())
        update();
    }
}
