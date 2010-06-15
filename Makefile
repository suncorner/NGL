#############################################################################
# Makefile for building: libngl.1.0.0.dylib
# Generated by qmake (2.01a) (Qt 4.6.2) on: Tue May 18 21:22:43 2010
# Project:  NGL.pro
# Template: lib
# Command: /usr/bin/qmake -spec /usr/local/Qt4.6/mkspecs/macx-g++ -macx -o Makefile NGL.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DNGL_DEBUG -DDARWIN -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -gdwarf-2 -Wall -W -fPIC $(DEFINES)
CXXFLAGS      = -pipe -msse -msse2 -msse3 -pthread -arch x86_64 -fPIC -g -gdwarf-2 -Wall -W -fPIC $(DEFINES)
INCPATH       = -I/usr/local/Qt4.6/mkspecs/macx-g++ -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/Library/Frameworks/QtOpenGL.framework/Versions/4/Headers -I/usr/include/QtOpenGL -I/usr/include -I/usr/local/boost -Iinclude/ngl -Isrc/ngl -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/System/Library/Frameworks/AGL.framework/Headers -I. -F/Library/Frameworks
LINK          = g++
LFLAGS        = -dynamiclib
LIBS          = $(SUBLIBS) -F/Library/Frameworks -L/Library/Frameworks -L/System/Library/Frameworks/OpenGL.framework/Libraries -Wl,-framework,Cocoa -L/usr/local/lib -framework QtOpenGL -framework QtGui -framework QtCore -framework OpenGL -framework AGL 
AR            = ar cq
RANLIB        = ranlib -s
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
export MACOSX_DEPLOYMENT_TARGET = 10.4

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = src/Vector.cpp \
		src/VBOPrimitives.cpp \
		src/Util.cpp \
		src/Texture.cpp \
		src/SpotLight.cpp \
		src/ShaderManager.cpp \
		src/Transformation.cpp \
		src/RibExport.cpp \
		src/Quaternion.cpp \
		src/PathCamera.cpp \
		src/Obj.cpp \
		src/Matrix.cpp \
		src/TransformStack.cpp \
		src/Material.cpp \
		src/Light.cpp \
		src/NGLInit.cpp \
		src/Colour.cpp \
		src/Clip.cpp \
		src/Camera.cpp \
		src/NCCABinMesh.cpp \
		src/BezierPatch.cpp \
		src/BezierCurve.cpp \
		src/BBox.cpp \
		src/AbstractMesh.cpp \
		src/HoudiniGeo.cpp \
		src/Random.cpp 
OBJECTS       = obj/Vector.o \
		obj/VBOPrimitives.o \
		obj/Util.o \
		obj/Texture.o \
		obj/SpotLight.o \
		obj/ShaderManager.o \
		obj/Transformation.o \
		obj/RibExport.o \
		obj/Quaternion.o \
		obj/PathCamera.o \
		obj/Obj.o \
		obj/Matrix.o \
		obj/TransformStack.o \
		obj/Material.o \
		obj/Light.o \
		obj/NGLInit.o \
		obj/Colour.o \
		obj/Clip.o \
		obj/Camera.o \
		obj/NCCABinMesh.o \
		obj/BezierPatch.o \
		obj/BezierCurve.o \
		obj/BBox.o \
		obj/AbstractMesh.o \
		obj/HoudiniGeo.o \
		obj/Random.o
DIST          = /usr/local/Qt4.6/mkspecs/common/unix.conf \
		/usr/local/Qt4.6/mkspecs/common/mac.conf \
		/usr/local/Qt4.6/mkspecs/common/mac-g++.conf \
		/usr/local/Qt4.6/mkspecs/qconfig.pri \
		/usr/local/Qt4.6/mkspecs/features/qt_functions.prf \
		/usr/local/Qt4.6/mkspecs/features/qt_config.prf \
		/usr/local/Qt4.6/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt4.6/mkspecs/features/default_pre.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/dwarf2.prf \
		/usr/local/Qt4.6/mkspecs/features/debug.prf \
		/usr/local/Qt4.6/mkspecs/features/default_post.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt4.6/mkspecs/features/warn_on.prf \
		/usr/local/Qt4.6/mkspecs/features/qt.prf \
		/usr/local/Qt4.6/mkspecs/features/unix/opengl.prf \
		/usr/local/Qt4.6/mkspecs/features/unix/thread.prf \
		/usr/local/Qt4.6/mkspecs/features/moc.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/rez.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt4.6/mkspecs/features/resources.prf \
		/usr/local/Qt4.6/mkspecs/features/uic.prf \
		/usr/local/Qt4.6/mkspecs/features/yacc.prf \
		/usr/local/Qt4.6/mkspecs/features/lex.prf \
		/usr/local/Qt4.6/mkspecs/features/include_source_dir.prf \
		NGL.pro
QMAKE_TARGET  = ngl
DESTDIR       = lib/
TARGET        = libngl.1.0.0.dylib
TARGETA       = lib/libngl.a
TARGETD       = libngl.1.0.0.dylib
TARGET0       = libngl.dylib
TARGET1       = libngl.1.dylib
TARGET2       = libngl.1.0.dylib

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-g \
		-gdwarf-2 \
		-Wall \
		-W


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile  lib/$(TARGET)

lib/$(TARGET):  $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	@$(CHK_DIR_EXISTS) lib/ || $(MKDIR) lib/ 
	-$(DEL_FILE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	-ln -s $(TARGET) $(TARGET0)
	-ln -s $(TARGET) $(TARGET1)
	-ln -s $(TARGET) $(TARGET2)
	-$(DEL_FILE) lib/$(TARGET)
	-$(DEL_FILE) lib/$(TARGET0)
	-$(DEL_FILE) lib/$(TARGET1)
	-$(DEL_FILE) lib/$(TARGET2)
	-$(MOVE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2) lib/



staticlib: $(TARGETA)

$(TARGETA):  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGETA) 
	$(AR) $(TARGETA) $(OBJECTS)
	$(RANLIB) $(TARGETA)

Makefile: NGL.pro  /usr/local/Qt4.6/mkspecs/macx-g++/qmake.conf /usr/local/Qt4.6/mkspecs/common/unix.conf \
		/usr/local/Qt4.6/mkspecs/common/mac.conf \
		/usr/local/Qt4.6/mkspecs/common/mac-g++.conf \
		/usr/local/Qt4.6/mkspecs/qconfig.pri \
		/usr/local/Qt4.6/mkspecs/features/qt_functions.prf \
		/usr/local/Qt4.6/mkspecs/features/qt_config.prf \
		/usr/local/Qt4.6/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt4.6/mkspecs/features/default_pre.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/dwarf2.prf \
		/usr/local/Qt4.6/mkspecs/features/debug.prf \
		/usr/local/Qt4.6/mkspecs/features/default_post.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt4.6/mkspecs/features/warn_on.prf \
		/usr/local/Qt4.6/mkspecs/features/qt.prf \
		/usr/local/Qt4.6/mkspecs/features/unix/opengl.prf \
		/usr/local/Qt4.6/mkspecs/features/unix/thread.prf \
		/usr/local/Qt4.6/mkspecs/features/moc.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/rez.prf \
		/usr/local/Qt4.6/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt4.6/mkspecs/features/resources.prf \
		/usr/local/Qt4.6/mkspecs/features/uic.prf \
		/usr/local/Qt4.6/mkspecs/features/yacc.prf \
		/usr/local/Qt4.6/mkspecs/features/lex.prf \
		/usr/local/Qt4.6/mkspecs/features/include_source_dir.prf \
		/Library/Frameworks/QtOpenGL.framework/QtOpenGL.prl \
		/Library/Frameworks/QtGui.framework/QtGui.prl \
		/Library/Frameworks/QtCore.framework/QtCore.prl
	$(QMAKE) -spec /usr/local/Qt4.6/mkspecs/macx-g++ -macx -o Makefile NGL.pro
/usr/local/Qt4.6/mkspecs/common/unix.conf:
/usr/local/Qt4.6/mkspecs/common/mac.conf:
/usr/local/Qt4.6/mkspecs/common/mac-g++.conf:
/usr/local/Qt4.6/mkspecs/qconfig.pri:
/usr/local/Qt4.6/mkspecs/features/qt_functions.prf:
/usr/local/Qt4.6/mkspecs/features/qt_config.prf:
/usr/local/Qt4.6/mkspecs/features/exclusive_builds.prf:
/usr/local/Qt4.6/mkspecs/features/default_pre.prf:
/usr/local/Qt4.6/mkspecs/features/mac/default_pre.prf:
/usr/local/Qt4.6/mkspecs/features/mac/dwarf2.prf:
/usr/local/Qt4.6/mkspecs/features/debug.prf:
/usr/local/Qt4.6/mkspecs/features/default_post.prf:
/usr/local/Qt4.6/mkspecs/features/mac/default_post.prf:
/usr/local/Qt4.6/mkspecs/features/mac/objective_c.prf:
/usr/local/Qt4.6/mkspecs/features/warn_on.prf:
/usr/local/Qt4.6/mkspecs/features/qt.prf:
/usr/local/Qt4.6/mkspecs/features/unix/opengl.prf:
/usr/local/Qt4.6/mkspecs/features/unix/thread.prf:
/usr/local/Qt4.6/mkspecs/features/moc.prf:
/usr/local/Qt4.6/mkspecs/features/mac/rez.prf:
/usr/local/Qt4.6/mkspecs/features/mac/sdk.prf:
/usr/local/Qt4.6/mkspecs/features/resources.prf:
/usr/local/Qt4.6/mkspecs/features/uic.prf:
/usr/local/Qt4.6/mkspecs/features/yacc.prf:
/usr/local/Qt4.6/mkspecs/features/lex.prf:
/usr/local/Qt4.6/mkspecs/features/include_source_dir.prf:
/Library/Frameworks/QtOpenGL.framework/QtOpenGL.prl:
/Library/Frameworks/QtGui.framework/QtGui.prl:
/Library/Frameworks/QtCore.framework/QtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/Qt4.6/mkspecs/macx-g++ -macx -o Makefile NGL.pro

dist: 
	@$(CHK_DIR_EXISTS) obj/ngl1.0.0 || $(MKDIR) obj/ngl1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/ngl1.0.0/ && $(COPY_FILE) --parents include/ngl/Vector.h include/ngl/VBOPrimitives.h include/ngl/Singleton.h include/ngl/Util.h include/ngl/Types.h include/ngl/Texture.h include/ngl/SpotLight.h include/ngl/ShaderManager.h include/ngl/RibExport.h include/ngl/Transformation.h include/ngl/Quaternion.h include/ngl/PathCamera.h include/ngl/Obj.h include/ngl/NGLassert.h include/ngl/Matrix.h include/ngl/TransformStack.h include/ngl/Material.h include/ngl/Light.h include/ngl/NGLInit.h include/ngl/Colour.h include/ngl/Clip.h include/ngl/Camera.h include/ngl/BezierPatch.h include/ngl/BezierCurve.h include/ngl/NCCABinMesh.h include/ngl/BBox.h include/ngl/AbstractMesh.h include/ngl/HoudiniGeo.h include/ngl/Random.h obj/ngl1.0.0/ && $(COPY_FILE) --parents src/Vector.cpp src/VBOPrimitives.cpp src/Util.cpp src/Texture.cpp src/SpotLight.cpp src/ShaderManager.cpp src/Transformation.cpp src/RibExport.cpp src/Quaternion.cpp src/PathCamera.cpp src/Obj.cpp src/Matrix.cpp src/TransformStack.cpp src/Material.cpp src/Light.cpp src/NGLInit.cpp src/Colour.cpp src/Clip.cpp src/Camera.cpp src/NCCABinMesh.cpp src/BezierPatch.cpp src/BezierCurve.cpp src/BBox.cpp src/AbstractMesh.cpp src/HoudiniGeo.cpp src/Random.cpp obj/ngl1.0.0/ && (cd `dirname obj/ngl1.0.0` && $(TAR) ngl1.0.0.tar ngl1.0.0 && $(COMPRESS) ngl1.0.0.tar) && $(MOVE) `dirname obj/ngl1.0.0`/ngl1.0.0.tar.gz . && $(DEL_FILE) -r obj/ngl1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) lib/$(TARGET) 
	-$(DEL_FILE) lib/$(TARGET0) lib/$(TARGET1) lib/$(TARGET2) $(TARGETA)
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

obj/Vector.o: src/Vector.cpp include/ngl/Vector.h \
		include/ngl/Types.h \
		include/ngl/NGLassert.h \
		include/ngl/Matrix.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Vector.o src/Vector.cpp

obj/VBOPrimitives.o: src/VBOPrimitives.cpp include/ngl/VBOPrimitives.h \
		include/ngl/Singleton.h \
		include/ngl/Types.h \
		include/ngl/Vector.h \
		include/ngl/Util.h \
		include/ngl/Texture.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/VBOPrimitives.o src/VBOPrimitives.cpp

obj/Util.o: src/Util.cpp include/ngl/Vector.h \
		include/ngl/Types.h \
		include/ngl/VBOPrimitives.h \
		include/ngl/Singleton.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Util.o src/Util.cpp

obj/Texture.o: src/Texture.cpp include/ngl/Texture.h \
		include/ngl/Types.h \
		include/ngl/NGLassert.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Texture.o src/Texture.cpp

obj/SpotLight.o: src/SpotLight.cpp include/ngl/SpotLight.h \
		include/ngl/Vector.h \
		include/ngl/Types.h \
		include/ngl/Light.h \
		include/ngl/VBOPrimitives.h \
		include/ngl/Singleton.h \
		include/ngl/Colour.h \
		include/ngl/Material.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/SpotLight.o src/SpotLight.cpp

obj/ShaderManager.o: src/ShaderManager.cpp include/ngl/ShaderManager.h \
		include/ngl/Types.h \
		include/ngl/Singleton.h \
		include/ngl/Matrix.h \
		include/ngl/Vector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/ShaderManager.o src/ShaderManager.cpp

obj/Transformation.o: src/Transformation.cpp include/ngl/Transformation.h \
		include/ngl/Vector.h \
		include/ngl/Types.h \
		include/ngl/Matrix.h \
		include/ngl/NGLassert.h \
		include/ngl/ShaderManager.h \
		include/ngl/Singleton.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Transformation.o src/Transformation.cpp

obj/RibExport.o: src/RibExport.cpp include/ngl/RibExport.h \
		include/ngl/Types.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/RibExport.o src/RibExport.cpp

obj/Quaternion.o: src/Quaternion.cpp include/ngl/Matrix.h \
		include/ngl/Types.h \
		include/ngl/Vector.h \
		include/ngl/Quaternion.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Quaternion.o src/Quaternion.cpp

obj/PathCamera.o: src/PathCamera.cpp include/ngl/PathCamera.h \
		include/ngl/Camera.h \
		include/ngl/Types.h \
		include/ngl/Vector.h \
		include/ngl/Matrix.h \
		include/ngl/RibExport.h \
		include/ngl/BezierCurve.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/PathCamera.o src/PathCamera.cpp

obj/Obj.o: src/Obj.cpp include/ngl/Obj.h \
		include/ngl/Types.h \
		include/ngl/Texture.h \
		include/ngl/Vector.h \
		include/ngl/AbstractMesh.h \
		include/ngl/BBox.h \
		include/ngl/RibExport.h \
		include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Obj.o src/Obj.cpp

obj/Matrix.o: src/Matrix.cpp include/ngl/Matrix.h \
		include/ngl/Types.h \
		include/ngl/Quaternion.h \
		include/ngl/Vector.h \
		include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Matrix.o src/Matrix.cpp

obj/TransformStack.o: src/TransformStack.cpp include/ngl/Transformation.h \
		include/ngl/Vector.h \
		include/ngl/Types.h \
		include/ngl/Matrix.h \
		include/ngl/NGLassert.h \
		include/ngl/TransformStack.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/TransformStack.o src/TransformStack.cpp

obj/Material.o: src/Material.cpp include/ngl/Material.h \
		include/ngl/Types.h \
		include/ngl/Colour.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Material.o src/Material.cpp

obj/Light.o: src/Light.cpp include/ngl/Light.h \
		include/ngl/Types.h \
		include/ngl/VBOPrimitives.h \
		include/ngl/Singleton.h \
		include/ngl/Vector.h \
		include/ngl/Colour.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Light.o src/Light.cpp

obj/NGLInit.o: src/NGLInit.cpp include/ngl/NGLInit.h \
		include/ngl/Types.h \
		include/ngl/Singleton.h \
		include/ngl/VBOPrimitives.h \
		include/ngl/Vector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/NGLInit.o src/NGLInit.cpp

obj/Colour.o: src/Colour.cpp include/ngl/Colour.h \
		include/ngl/Types.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Colour.o src/Colour.cpp

obj/Clip.o: src/Clip.cpp include/ngl/Clip.h \
		include/ngl/Types.h \
		include/ngl/Vector.h \
		include/ngl/Obj.h \
		include/ngl/Texture.h \
		include/ngl/AbstractMesh.h \
		include/ngl/BBox.h \
		include/ngl/RibExport.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Clip.o src/Clip.cpp

obj/Camera.o: src/Camera.cpp include/ngl/Camera.h \
		include/ngl/Types.h \
		include/ngl/Vector.h \
		include/ngl/Matrix.h \
		include/ngl/RibExport.h \
		include/ngl/Util.h \
		include/ngl/NGLassert.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Camera.o src/Camera.cpp

obj/NCCABinMesh.o: src/NCCABinMesh.cpp include/ngl/NCCABinMesh.h \
		include/ngl/Types.h \
		include/ngl/Texture.h \
		include/ngl/Vector.h \
		include/ngl/AbstractMesh.h \
		include/ngl/BBox.h \
		include/ngl/RibExport.h \
		include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/NCCABinMesh.o src/NCCABinMesh.cpp

obj/BezierPatch.o: src/BezierPatch.cpp include/ngl/BezierPatch.h \
		include/ngl/Types.h \
		include/ngl/Vector.h \
		include/ngl/BezierCurve.h \
		include/ngl/VBOPrimitives.h \
		include/ngl/Singleton.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/BezierPatch.o src/BezierPatch.cpp

obj/BezierCurve.o: src/BezierCurve.cpp include/ngl/BezierCurve.h \
		include/ngl/Types.h \
		include/ngl/Vector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/BezierCurve.o src/BezierCurve.cpp

obj/BBox.o: src/BBox.cpp include/ngl/BBox.h \
		include/ngl/Types.h \
		include/ngl/Vector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/BBox.o src/BBox.cpp

obj/AbstractMesh.o: src/AbstractMesh.cpp include/ngl/AbstractMesh.h \
		include/ngl/Types.h \
		include/ngl/Texture.h \
		include/ngl/Vector.h \
		include/ngl/BBox.h \
		include/ngl/RibExport.h \
		include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/AbstractMesh.o src/AbstractMesh.cpp

obj/HoudiniGeo.o: src/HoudiniGeo.cpp include/ngl/HoudiniGeo.h \
		include/ngl/Types.h \
		include/ngl/AbstractMesh.h \
		include/ngl/Texture.h \
		include/ngl/Vector.h \
		include/ngl/BBox.h \
		include/ngl/RibExport.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/HoudiniGeo.o src/HoudiniGeo.cpp

obj/Random.o: src/Random.cpp include/ngl/Random.h \
		include/ngl/Types.h \
		include/ngl/Colour.h \
		include/ngl/Vector.h \
		include/ngl/Singleton.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Random.o src/Random.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
