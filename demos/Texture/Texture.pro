# -------------------------------------------------
# Project created by QtCreator 2009-11-05T22:11:46
# -------------------------------------------------
QT += opengl
QT -= core \
    gui

TARGET =Texture
DESTDIR=./
# this is where we want to put the intermediate build files ( .o)
OBJECTS_DIR=./obj/
MOC_DIR=./moc/
SOURCES += src/main.cpp \
           src/MainWindow.cpp \
           src/GLWindow.cpp
INCLUDEPATH+=./include
HEADERS += include/MainWindow.h \
           include/GLWindow.h
OTHER_FILES+= shaders/Fragment.fs \
              shaders/Vertex.vs
CONFIG += console
CONFIG -= app_bundle
DEFINES+=USING_QT_CREATOR

QMAKE_CXXFLAGS+= -msse -msse2 -msse3
macx:QMAKE_CXXFLAGS+= -arch x86_64
macx:INCLUDEPATH+=/usr/local/boost/
linux-g++:QMAKE_CXXFLAGS +=  -march=native
# define the _DEBUG flag for the graphics lib
DEFINES +=NGL_DEBUG

# shell out and run sdl-config for the libs
unix:LIBS += `sdl-config --libs`
# and the same for the C++ flags
unix:QMAKE_CXXFLAGS += `sdl-config --cflags`

# do the same for image magick

# add some static libs  SDL_ttf put mixer here if your using sound
LIBS += -L/usr/local/lib
LIBS += -lSDL_ttf
# add the ngl lib
LIBS +=  -L/$(HOME)/ngl/lib -l ngl

# now if we are under unix and not on a Mac (i.e. linux) define GLEW
linux-g++ {
    DEFINES += LINUX
    LIBS+= -lGLEW
}

# if we are on a mac define DARWIN
macx:DEFINES += DARWIN

# this is where to look for includes
INCLUDEPATH += $$(HOME)/ngl/include/

win32: {
        DEFINES+=USING_GLEW

        INCLUDEPATH+=-I c:\boost_1_40_0
        INCLUDEPATH+=-I c:/SDL-1.2.14/include
        INCLUDEPATH+=-I c:/SDL-1.2.14/include/SDL
        INCLUDEPATH+=-I c:/SDL_ttf-2.0.9/include
        INCLUDEPATH+= -I C:/glew/include
        LIBS+= -L C:/GraphicsLib/lib
        LIBS+= -L C:/glew/bin
        LIBS+= -lmingw32
        LIBS+= -lglew32
}

