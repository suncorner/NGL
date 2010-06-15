#include "GLWindow.h"
#include <iostream>
#include "ngl/Camera.h"
#include "ngl/Colour.h"
#include "ngl/Light.h"
#include "ngl/Matrix.h"
#include "ngl/Transformation.h"
#include "ngl/TransformStack.h"
#include "ngl/Material.h"
#include "ngl/NGLInit.h"
#include "ngl/Obj.h"
#include "ngl/VBOPrimitives.h"
#include "ngl/ShaderManager.h"



//----------------------------------------------------------------------------------------------------------------------
GLWindow::GLWindow(
                   QWidget *_parent
                  ) :
                    QGLWidget(_parent)
{

  // set this widget to have the initial keyboard focus
  setFocus();
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
  // Now set the initial GLWindow attributes to default values
  // Roate is false
  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace=0;
  m_spinYFace=0;
}

// This virtual function is called once before the first call to paintGL() or resizeGL(),
//and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags, defining display lists, etc.

//----------------------------------------------------------------------------------------------------------------------
void GLWindow::initializeGL()
{

  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
   glEnable(GL_DEPTH_TEST);
   // Now we will create a basic Camera from the graphics library
   // This is a static camera so it only needs to be set once
   // First create Values for the camera position
   ngl::Vector From(0,3,3);
   ngl::Vector To(0,0,0);
   ngl::Vector Up(0,1,0);
   ngl::NGLInit *Init = ngl::NGLInit::Instance();
   Init->InitGlew();
   Init->InitVBOandImageLib();
   m_cam= new ngl::Camera(From,To,Up,ngl::PERSPECTIVE);
   // set the shape using FOV 45 Aspect Ratio based on Width and Height
   // The final two are near and far clipping planes of 0.5 and 10
   m_cam->SetShape(100,(float)720.0/576.0,0.5,10,ngl::PERSPECTIVE);
   // now to load the shader and set the values
   // grab an instance of shader manager
   ngl::ShaderManager *shader=ngl::ShaderManager::Instance();
   // load a frag and vert shaders
   shader->LoadShader("gl3xTest","shaders/Vertex.vs","shaders/Fragment.fs");
   // set this as the active shader
   shader->UseShader("gl3xTest");
   // now pass the modelView and projection values to the shader
   shader->SetShaderParamFromMatrix("gl3xTest","ViewMatrix",m_cam->GetModelView());
   shader->SetShaderParamFromMatrix("gl3xTest","projectionMatrix",m_cam->GetProjection());
   // the shader will use the currently active material and light0 so set them
   ngl::Material m(ngl::GOLD);
   m.Use();
   ngl::Light *L1 = new ngl::Light(ngl::Vector(5,12,0,1),ngl::Colour(1,1,1,1),ngl::LIGHTLOCAL);
   L1->Enable();

}

//----------------------------------------------------------------------------------------------------------------------
//This virtual function is called whenever the widget has been resized.
// The new size is passed in width and height.
void GLWindow::resizeGL(
                        int _w,
                        int _h
                       )
{
  glViewport(0,0,_w,_h);
  m_cam->SetShape(100,(float)_w/_h,0.5,10,ngl::PERSPECTIVE);
  ngl::ShaderManager *shader=ngl::ShaderManager::Instance();
  shader->SetShaderParamFromMatrix("gl3xTest","projectionMatrix",m_cam->GetProjection());
}

//----------------------------------------------------------------------------------------------------------------------
//This virtual function is called whenever the widget needs to be painted.
// this is our main drawing routine
void GLWindow::paintGL()
{
  // grab an instance of the shader manager
  ngl::ShaderManager *shader=ngl::ShaderManager::Instance();
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Rotation based on the mouse position for our global
  // transform
  ngl::Transformation trans;
  trans.SetRotation(m_spinXFace,m_spinYFace,0);
  // set this in the TX stack
  m_transformStack.SetGlobal(trans);
  // now set this value in the shader for the current ModelMatrix
  shader->SetShaderParamFromMatrix("gl3xTest","ModelMatrix",m_transformStack.GetCurrAndGlobal().GetTransposeMatrix());
  // get the VBO instance and draw the built in teapot
  ngl::VBOPrimitives *prim=ngl::VBOPrimitives::Instance();
  prim->DrawVBO("teapot");
  // liberal use of { is encourage after each Push
  m_transformStack.PushTransform();
  {
    m_transformStack.GetCurrentTransform().SetScale(1.5,1.5,1.5);
    m_transformStack.GetCurrentTransform().SetRotation(0,90,15);
    m_transformStack.GetCurrentTransform().SetPosition(ngl::Vector(1.5,0.0,0.0));
    shader->SetShaderParamFromMatrix("gl3xTest","ModelMatrix",m_transformStack.GetCurrAndGlobal().GetTransposeMatrix());
    // now draw the teapot
    prim->DrawVBO("teapot");
  } // and before a pop
  m_transformStack.PopTransform();

  m_transformStack.PushTransform();
  {
    // set the transformation
    m_transformStack.GetCurrentTransform().SetScale(1.5,1.5,1.5);
    m_transformStack.GetCurrentTransform().SetRotation(35,180,15);
    m_transformStack.GetCurrentTransform().SetPosition(-1.5,0.0,0.0);
    // load it to the shader
    shader->SetShaderParamFromMatrix("gl3xTest","ModelMatrix",m_transformStack.GetCurrAndGlobal().GetTransposeMatrix());
    // now draw the teapot
    prim->DrawVBO("teapot");
  }
  m_transformStack.PopTransform();
}

//----------------------------------------------------------------------------------------------------------------------
void GLWindow::mouseMoveEvent (
                               QMouseEvent * _event
                              )
{
  // note the method buttons() is the button state when event was called
  // this is different from button() which is used to check which button was
  // pressed when the mousePress/Release event is generated
  if(m_rotate && _event->buttons() == Qt::LeftButton)
  {
    m_spinYFace = ( m_spinYFace + (_event->x() - m_origX) ) % 360 ;
    m_spinXFace = ( m_spinXFace + (_event->y() - m_origY) ) % 360 ;
    m_origX = _event->x();
    m_origY = _event->y();
  }
  // re-draw GL
  updateGL();
}


//----------------------------------------------------------------------------------------------------------------------
void GLWindow::mousePressEvent (
                                QMouseEvent * _event
                               )
{
  // this method is called when the mouse button is pressed in this case we
  // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
  if(_event->button() == Qt::LeftButton)
  {
    m_origX = _event->x();
    m_origY = _event->y();
    m_rotate =true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void GLWindow::mouseReleaseEvent (
                                  QMouseEvent * _event
                                 )
{
  // this event is called when the mouse button is released
  // we then set Rotate to false
  if (_event->button() == Qt::LeftButton)
  {
    m_rotate=false;
  }
}

