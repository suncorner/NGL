# -------------------------------------------------
# Project created by QtCreator 2009-11-05T12:31:57
# -------------------------------------------------
# this library doesn't need core Qt functionality so we remove it

# We will use the built in Qt lib template
TEMPLATE = lib
QT += opengl
QT += core
QT += gui
# set the base directory of our project so Qt knows where to find them
# we can use shell vars but need to use $$
BASE_DIR = $$(HOME)/ngl
# This is the output target we want to create
TARGET = $$BASE_DIR/lib/ngl
# this is where we want to put the intermediate build files ( ../obj)
OBJECTS_DIR = $$BASE_DIR/obj
QMAKE_LFLAGS-= -headerpad_max_install_names
QMAKE_LFLAGS_SHLIB -= -single_module
QMAKE_LFLAGS_VERSION=
QMAKE_LFLAGS_COMPAT_VERSION=
QMAKE_LFLAGS_SONAME=


# define the NGL_DEBUG flag for the graphics lib
DEFINES += NGL_DEBUG

INCLUDEPATH +=/usr/local/boost
#set some flags for sse etc
QMAKE_CXXFLAGS+= -msse -msse2 -msse3 -pthread
# on my mac I can only compile as i386 at present
macx:QMAKE_CXXFLAGS+= -arch x86_64 -fPIC
macx:LIBS+= -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework OpenGL
macx:LIBS+=  -Wl,-framework,Cocoa
# on linux we can use the native flag and it will pick up the correct version
linux-g++:QMAKE_CXXFLAGS+=  -march=native

# The windows configuration is very frustrating however I seem to have it working now
# You will need to install the following
# SDL using the mingw version see http://www.libsdl.org/download-1.2.php
# you will need the version SDL-devel-1.2.14-mingw32.tar.gz and place it into C:\
# The path below is C:\SDL-1.2.14 but change it to reflect where you install it
# You will also need to install SDL_ttf (devel version )
# and image Magic but this will be replaced soon
# again get the MinGW version from here
# http://www.imagemagick.org/script/binary-releases.php
# and finally boost
# once you have done this set the PATH environment variable to look in
# c:\GraphicsLib\lib to find the DLL
win32: {
        message(OK you fool your using windows you better check the GraphicsLib.pro file)
        message(The paths in this file will need to be set for your machine)
        message(good luck has taken me 2 Days to get it working)

        INCLUDEPATH += C:/SDL-1.2.14/include
        INCLUDEPATH += C:/SDL-1.2.14/include/SDL
        LIBS += -L C:/SDL-1.2.14/lib
        LIBS += -lmingw32
        LIBS += -lSDL
        LIBS += -lstdc++
        DEFINES += WIN32
        INCLUDEPATH += C:/glew/include
        LIBS += -L C:/glew/bin
        LIBS += -lglew32
        INCLUDEPATH += C:/boost_1_40_0
        INCLUDEPATH += C:/SDL_ttf-2.0.9/include
        LIBS += -L C:/SDL_ttf-2.0.9/lib
        LIBS += -L/lib/w32api
        DESTDIR = c:/
        # under windows we only use DEVIL for images so add them here
        DEFINES += USE_DEVIL
        LIBS += -L c:/devil/lib
        LIBS += -lDevIL
        LIBS += -lILU
        LIBS += -lILUT
        INCLUDEPATH += c:/devil/include
}

# if we are on a mac define DARWIN
macx:DEFINES += DARWIN

# this is where to look for includes
INCLUDEPATH += $$BASE_DIR/include/ngl
INCLUDEPATH += $$BASE_DIR/src/ngl

# do the same for image magick
LIBS += -L/usr/local/lib

# set the SRC_DIR so we can find the project files
SRC_DIR = $$BASE_DIR/src
# the unix flag works for both Mac and Linux if we want linux only
# we need to use the linux-g++ flag
linux-g++ {
          DEFINES += LINUX
          LIBS+=-lGLEW
}
# and the include files
INC_DIR = $$BASE_DIR/include/ngl
DEPENDPATH= $$INC_DIR

SOURCES += $$SRC_DIR/Vector.cpp \
    $$SRC_DIR/VBOPrimitives.cpp \
    $$SRC_DIR/Util.cpp \
    $$SRC_DIR/Texture.cpp \
    $$SRC_DIR/SpotLight.cpp \
    $$SRC_DIR/ShaderManager.cpp \
    $$SRC_DIR/Transformation.cpp \
    $$SRC_DIR/RibExport.cpp \
    $$SRC_DIR/Quaternion.cpp \
    $$SRC_DIR/PathCamera.cpp \
    $$SRC_DIR/Obj.cpp \
    $$SRC_DIR/Matrix.cpp \
    $$SRC_DIR/TransformStack.cpp \
    $$SRC_DIR/Material.cpp \
    $$SRC_DIR/Light.cpp \
    $$SRC_DIR/NGLInit.cpp \
    $$SRC_DIR/Colour.cpp \
    $$SRC_DIR/Clip.cpp \
    $$SRC_DIR/Camera.cpp \
    $$SRC_DIR/NCCABinMesh.cpp \
    $$SRC_DIR/BezierPatch.cpp \
    $$SRC_DIR/BezierCurve.cpp \
    $$SRC_DIR/BBox.cpp \
    $$SRC_DIR/AbstractMesh.cpp \
    $$SRC_DIR/HoudiniGeo.cpp \
    $$SRC_DIR/Random.cpp

HEADERS += $$INC_DIR/Vector.h \
    $$INC_DIR/VBOPrimitives.h \
    $$INC_DIR/Singleton.h \
    $$INC_DIR/Util.h \
    $$INC_DIR/Types.h \
    $$INC_DIR/Texture.h \
    $$INC_DIR/SpotLight.h \
    $$INC_DIR/ShaderManager.h \
    $$INC_DIR/RibExport.h \
    $$INC_DIR/Transformation.h \
    $$INC_DIR/Quaternion.h \
    $$INC_DIR/PathCamera.h \
    $$INC_DIR/Obj.h \
    $$INC_DIR/NGLassert.h \
    $$INC_DIR/Matrix.h \
    $$INC_DIR/TransformStack.h \
    $$INC_DIR/Material.h \
    $$INC_DIR/Light.h \
    $$INC_DIR/NGLInit.h \
    $$INC_DIR/Colour.h \
    $$INC_DIR/Clip.h \
    $$INC_DIR/Camera.h \
    $$INC_DIR/BezierPatch.h \
    $$INC_DIR/BezierCurve.h \
    $$INC_DIR/NCCABinMesh.h \
    $$INC_DIR/BBox.h \
    $$INC_DIR/AbstractMesh.h \
    $$INC_DIR/HoudiniGeo.h \
    $$INC_DIR/Random.h
OTHER_FILES+=
