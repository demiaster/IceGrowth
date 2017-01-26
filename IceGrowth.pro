TARGET = IceGrowth
OBJECTS_DIR = obj
CONFIG -= app_bundle
CONFIG += console

DEPENDPATH += .
INCLUDEPATH += ./include
MOC_DIR=moc
DESTDIR=./

QMAKE_CC = clang
QMAKE_CXX = clang++
QT += gui opengl core


linux:QMAKE_CXXFLAGS += $$system(Magick++-config --cppflags )
linux:LIBS += $$system(Magick++-config --ldflags --libs )
linux:LIBS += -lGLEW -lglfw

macx:QMAKE_CXXFLAGS += -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/local/include/ImageMagick-6
macx:LIBS += -L/usr/local/lib -lMagick++-6.Q16 -lMagickWand-6.Q16 -lMagickCore-6.Q16

CONFIG += c++11
DEFINES += GRAPHICSDEBUG
#DEFINES += DEBUG
#DEFINES += TRACE
#DEFINES += LOG
DEFINES += DLA_DEBUG
DEFINES += DLA_TRACE

# Input
SOURCES += src/main.cpp \
           src/image.cpp \
           src/heatgrid.cpp \
           src/hexnavigator.cpp \
           src/icegrid.cpp \
           src/icegenerator.cpp \
           src/framebuffer.cpp \
           src/NGLscene.cpp \
           src/NGLsceneMouseControls.cpp \
           src/squarenavigator.cpp

HEADERS += include/common.h \
           include/image.h \
           include/point.h \
           include/grid.h \
           include/heatgrid.h \
           include/hexnavigator.h \
           include/icegrid.h \
           include/icegenerator.h \
           include/framebuffer.h \
           include/freezable.h \
           include/navigator.h \
           include/NGLscene.h \
           include/randomdist.h \
           include/squarenavigator.h \
           include/windowparam.h
OTHER_FILES += shaders/*.glsl \

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
        cache()
        DEFINES +=QT5BUILD
}

# finding NGL things
!equals(PWD, $${OUT_PWD}){
        copydata.commands = echo "creating destination dirs" ;
        copydata.commands += mkdir -p $$OUT_PWD/shaders ;
        copydata.commands += echo "copying files" ;
        copydata.commands += $(COPY_DIR) $$PWD/shaders/* $$OUT_PWD/shaders/ ;
        first.depends = $(first) copydata
        export(first.depends)
        export(copydata.commands)
        QMAKE_EXTRA_TARGETS += first copydata
}

NGLPATH  = $$(NGLDIR)

isEmpty(NGLPATH){ # note brace must be here
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}
