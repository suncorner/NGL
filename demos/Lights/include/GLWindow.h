#ifndef __GL_WINDOW_H__
#define __GL_WINDOW_H__


#include "ngl/Camera.h"
#include "ngl/Colour.h"
#include "ngl/Light.h"
#include "ngl/TransformStack.h"
// must be included after our stuff becuase GLEW needs to be first
#include <QtOpenGL>

class GLWindow : public QGLWidget
{
Q_OBJECT        // must include this if you use Qt signals/slots
public :
  /// \brief Constructor for GLWindow
  /// @param [in] parent the parent window to create the GL context in
  GLWindow(
           QWidget *_parent
          );
  ~GLWindow();

private :

  // used to store the x rotation mouse value
  int m_spinXFace;
  // used to store the y rotation mouse value
  int m_spinYFace;
  // flag to indicate if the mouse button is pressed when dragging
  bool m_rotate;
  // the previous x mouse value
  int m_origX;
  // the previous y mouse value
  int m_origY;
  // Our Camera
  ngl::Camera *m_cam;
  // an array of lights
  ngl::Light *m_lightArray[8];
  ngl::Real m_teapotRotation;
  int m_rotationTimer;
  int m_lightChangeTimer;
  ngl::TransformStack m_transformStack;


protected:

  /// \brief  The following methods must be implimented in the sub class
  /// this is called when the window is created
  /// \note these are part of the Qt API so can't be changed to the coding standard
  /// so it can't be called initializeGL )
  void initializeGL();

  /// \brief this is called whenever the window is re-sized
  /// @param[in] _w the width of the resized window
  /// @param[in] _h the height of the resized window
  /// \note these are part of the Qt API so can't be changed to the coding standard
  /// so it can't be called resizeGL )
  void resizeGL(
                const int _w,
                const int _h
               );
  // \brief this is the main gl drawing routine which is called whenever the window needs to
  // be re-drawn
  void paintGL();

private :
  /// \brief this method is called every time a mouse is moved
  /// @param _event the Qt Event structure
  /// \note these are part of the Qt API so can't be changed to the coding standard
  /// so it can't be called MouseMoveEvent )

  void mouseMoveEvent (
                       QMouseEvent * _event
                      );
  /// \brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  /// \note these are part of the Qt API so can't be changed to the coding standard
  /// so it can't be called MousePressEvent )

  void mousePressEvent (
                        QMouseEvent *_event
                       );

  // \brief this method is called everytime the mouse button is released
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  /// \note these are part of the Qt API so can't be changed to the coding standard
  /// so it can't be called MousePressEvent )
  void mouseReleaseEvent (
                          QMouseEvent *_event
                         );

  void CreateLights();

  void timerEvent(
                  QTimerEvent *_event
                 );


};

#endif
