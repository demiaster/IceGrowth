#include <QMouseEvent>
#include <QGuiApplication>
#include "NGLscene.h"

namespace view
{


    void NGLscene::keyPressEvent(QKeyEvent *_event)
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
