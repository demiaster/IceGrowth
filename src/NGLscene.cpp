#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLscene.h"
#include <ngl/NGLInit.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/VAOFactory.h>
#include <ngl/Util.h>
#include <iostream>
#include <vector>
#include <array>
#include <math.h>

namespace view
{
    NGLscene::NGLscene()
    {
        // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
        setTitle("VAO Grid");
        std::cout<<m_view<<'\n'<<m_projection<<'\n';
        m_view=ngl::lookAt(ngl::Vec3(0.0f,0.0f,150.0f),
                           ngl::Vec3::zero(),
                           ngl::Vec3::up());

        std::cout<<"view \n"<<m_view<<'\n';
    }


    NGLscene::~NGLscene()
    {
        std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
    }


    void NGLscene::resizeGL(int _w , int _h)
    {
        m_win.width  = static_cast<int>( _w * devicePixelRatio() );
        m_win.height = static_cast<int>( _h * devicePixelRatio() );
        m_projection=ngl::perspective(45.0f,
                                      static_cast<float>(_w)/_h,
                                      0.5f,
                                      200.0f);
        std::cout<<"projection \n"<<m_projection<<'\n';

    }

    struct vertex
    {
        ngl::Vec3 p;
        ngl::Vec3 n;
        ngl::Vec4 c;
    };

    typedef struct Point_s
    {
        float x;
        float y;
    } Point;

    void NGLscene::buildMesh(ngl::Real _width, ngl::Real _height)
    {
        std::vector<vertex> data;
        vertex vert;
        vertex origin;
        vertex current_center;
        float angle = 60.0;
        float cosine = cos(angle * ngl::PI / 180);
        float sine = sin(angle * ngl::PI / 180);
        float radius = 1.0f;
        //anticlockwise
        std::array<Point, 7> vertices =
                                {{Point{  radius, 0},
                                  Point{  radius * cosine, radius * sine},
                                  Point{- radius * cosine, radius * sine},
                                  Point{- radius, 0},
                                  Point{- radius * cosine, - radius * sine},
                                  Point{  radius * cosine, - radius * sine},
                                  Point{  radius, 0}}};

        //center of the first top left hexagon
        origin.p.m_x = 0.0f;
        origin.p.m_y = 0.0f;

        float deltax = 3 * radius * cosine;
        float deltay_odd = - radius * sine;
        //looping on the y
        for(int k = 0; k < _height; ++k)
        {
            float line_offset = - k * 2 * radius * sine;
            //looping on the x
            for(int j = 0; j < _width; ++j)
            {
                current_center.p.m_x = origin.p.m_x + j * deltax;
                current_center.p.m_y = origin.p.m_y + line_offset + ((j % 2) * deltay_odd);


                //do the hexagon
                for(unsigned i = 0; i < vertices.size() - 1; ++i)
                {
                    data.push_back(current_center);

                    // i-th vertex only needs to be defined the first time,
                    // every other time it had already been defined at i-1-th
                    if(i == 0)
                    {
                        vert.p.m_x = current_center.p.m_x + vertices[i].x;
                        vert.p.m_y = current_center.p.m_y + vertices[i].y;
                    }
                    data.push_back(vert);

                    vert.p.m_x = current_center.p.m_x + vertices[i + 1].x;
                    vert.p.m_y = current_center.p.m_y + vertices[i + 1].y;
                    vert.c.m_r = 255;
                    vert.c.m_g = 0;
                    vert.c.m_b = 0;
                    vert.c.m_a = 0;
                    data.push_back(vert);

                }
            }
        }

        m_nVerts=data.size();

        m_vao.reset(ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_TRIANGLES));
        m_vao->bind();
        m_vao->setData(ngl::AbstractVAO::VertexData(data.size()*sizeof(vertex),
                                                    data[0].p.m_x));
        m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(vertex),0);
        m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(vertex),3);
        m_vao->setVertexAttributePointer(2,4,GL_FLOAT,sizeof(vertex),6);

        m_vao->setNumIndices(data.size());
        m_vao->unbind();

    }

    void NGLscene::timerEvent(QTimerEvent *)
    {
        static float time;
        time+=0.1f;
        m_vao->bind();
        vertex *ptr =static_cast<vertex *>
                ( glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE) );

        //  for(size_t i=0; i<m_vao->numIndices(); ++i)
        //  {
        //    ptr[i].p.m_y=sinf(ptr[i].p.m_x+time);
        //  }
        //  for(size_t i=0; i<m_vao->numIndices(); ++i)
        //  {
        //    ptr[i].p.m_y+=sinf(ptr[i].p.m_z+time);
        //  }

        for(size_t i = 0; i < m_vao->numIndices(); i += 3)
        {
            //calculating the correct normal direction for every 3 vertexes
            ngl::Vec3 normal = ngl::calcNormal(ptr[i + 1].p, ptr[i].p, ptr[i + 2].p);
            ptr[i].n = normal;
            ptr[i + 1].n = normal;
            ptr[i + 2].n = normal;

        }

        glUnmapBuffer(GL_ARRAY_BUFFER);
        m_vao->unbind();
        update();
    }


    constexpr auto gridShader = "gridShader";

    void NGLscene::initializeGL()
    {
        // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
        // be done once we have a valid GL context but before we call any GL commands. If we dont do
        // this everything will crash
        ngl::NGLInit::instance();
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);   // Grey Background
        // enable depth testing for drawing
        glEnable(GL_DEPTH_TEST);
        // enable multisampling for smoother drawing
        glEnable(GL_MULTISAMPLE);


        ngl::ShaderLib *shader = ngl::ShaderLib::instance();
        shader->createShaderProgram(gridShader);

        //just to avoid typos while writing
        constexpr auto gridVertex = "gridVertex";
        constexpr auto gridFragment = "gridFragment";

        //just to learn the pipeline of stuff going on here
        shader->attachShader(gridVertex,ngl::ShaderType::VERTEX);
        shader->attachShader(gridFragment, ngl::ShaderType::FRAGMENT);
        shader->loadShaderSource(gridVertex, "shaders/gridVertex.glsl");
        shader->loadShaderSource(gridFragment, "shaders/gridFragment.glsl");
        shader->compileShader(gridVertex);
        shader->compileShader(gridFragment);

        //add the shaders
        shader->attachShaderToProgram(gridShader, gridVertex);
        shader->attachShaderToProgram(gridShader, gridFragment);
        shader->linkProgramObject(gridShader);

        shader->use(gridShader);
        shader->setUniform("color", 0.0f, 1.0f, 1.0f, 1.0f);

        buildMesh(60.0f,60.0f);
        startTimer(20);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }



    void NGLscene::paintGL()
    {
        // clear the screen and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, m_win.width, m_win.height);
        ngl::ShaderLib *shader = ngl::ShaderLib::instance();
        shader->use(gridShader);
        // Rotation based on the mouse position for our global
        // transform
        ngl::Mat4 rotX;
        ngl::Mat4 rotY;
        ngl::Mat4 m_mouseGlobalTX;
        // create the rotation matrices
        rotX.rotateX(m_win.spinXFace);
        rotY.rotateY(m_win.spinYFace);
        // multiply the rotations
        ngl::Mat4 mouseGlobalTX=rotY*rotX;
        // add the translations
        mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
        mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
        mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

        m_vao->bind();

        shader->use(gridShader);
        shader->setUniform("MVP", mouseGlobalTX * m_view*m_projection);
        shader->setUniform("MV", mouseGlobalTX * m_view);
        ngl::Mat3 normalMatrix = mouseGlobalTX * m_view;
        normalMatrix.inverse();
        shader->setUniform("normalMatrix",normalMatrix);
        m_vao->draw();
        m_vao->unbind();

    }


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
