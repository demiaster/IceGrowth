TARGET = IceGrowth
CONFIG -= app_bundle
DEPENDPATH += .
INCLUDEPATH += ./include
QMAKE_CC = clang
QMAKE_CXX = clang++


linux:QMAKE_CXXFLAGS+=$$system(Magick++-config --cppflags )
linux:LIBS+=$$system(Magick++-config --ldflags --libs )
linux:LIBS+= -lGLEW -lglfw
CONFIG+=c++11
#DEFINES += DEBUG
#DEFINES += TRACE

# Input
SOURCES += src/main.cpp \
           src/image.cpp \
           src/heatgrid.cpp \
           src/hexnavigator.cpp \
           src/icegrid.cpp \
           src/icegenerator.cpp \
           src/framebuffer.cpp \
           src/squarenavigator.cpp
HEADERS+= include/image.h \
    include/point.h \
    include/grid.h \
    include/heatgrid.h \
    include/hexnavigator.h \
    include/icegrid.h \
    include/icegenerator.h \
    include/framebuffer.h \
    include/freezable.h \
    include/navigator.h \
    include/randomdist.h \
    include/squarenavigator.h

macx:QMAKE_CXXFLAGS+=-DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/local/include/ImageMagick-6
macx:LIBS+= -L/usr/local/lib -lMagick++-6.Q16 -lMagickWand-6.Q16 -lMagickCore-6.Q16

OBJECTS_DIR=obj
