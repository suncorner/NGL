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
#include "ngl/Util.h"




//----------------------------------------------------------------------------------------------------------------------
GLWindow::GLWindow(
                   QWidget *_parent,
                   const std::string &_vboname

                  ) :
                    QGLWidget(_parent)
{
  std::cout <<"ctor\n";
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
  m_origX=0;
  m_origY=0;
  m_teapotRotation=0.0;
  m_rotationTimer=startTimer(20);
  m_lightChangeTimer=startTimer(1000);
  m_instance=0;

}

GLWindow::~GLWindow()
{
  for(int i=0; i<8; ++i)
  {
     delete m_lightArray[i];
  }
}

// This virtual function is called once before the first call to paintGL() or resizeGL(),
//and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags, defining display lists, etc.

//----------------------------------------------------------------------------------------------------------------------
void GLWindow::initializeGL()
{
  // create the lights
  //CreateLights();
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
   glEnable(GL_DEPTH_TEST);
   // Now we will create a basic Camera from the graphics library
   // This is a static camera so it only needs to be set once
   // First create Values for the camera position
   ngl::Vector From(20,10,3);
   ngl::Vector To(0,0,0);
   ngl::Vector Up(0,1,0);
   //ngl::NGLInit *Init = ngl::NGLInit::Instance();
   //Init->InitGlew();
   //Init->InitVBOandImageLib();
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
   ngl::VBOPrimitives *prim =ngl::VBOPrimitives::Instance();
   prim->CreateVBOSphere(m_vboname,0.8,42);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST); // for removal of hidden surfaces
   glEnable(GL_NORMALIZE); // normalize vectors for proper shading
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
   ngl::Material m(ngl::POLISHEDSILVER);
   m.Use();
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
  this->makeCurrent();
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 // build our transform stack
  ngl::Transformation trans;
  // set the mouse rotation
  trans.SetRotation(m_spinXFace,m_spinYFace,0);
  // set this in the TX stack
  m_transformStack.SetGlobal(trans);

  // grab an instance of the primitives for drawing
  ngl::VBOPrimitives *prim=ngl::VBOPrimitives::Instance();
  // Rotation based on the mouse position for our global
  // transform
  m_transformStack.LoadGlobalAndCurrentMatrixToShader("gl3xTest","ModelMatrix");
/*
  for(int i=0; i<8; ++i)
  {
    // enable the light (this will set the values)
    //m_lightArray[i]->Enable();
    m_transformStack.PushTransform();
    {
      m_transformStack.GetCurrentTransform().SetPosition(m_lightArray[i]->GetPos());
      m_transformStack.LoadGlobalAndCurrentMatrixToShader("gl3xTest","ModelMatrix");
      //prim->DrawVBO("cube");
    }
    m_transformStack.PopTransform();
  }
*/
  m_transformStack.GetCurrentTransform().SetScale(8,8,8);
  m_transformStack.GetCurrentTransform().SetRotation(m_teapotRotation,m_teapotRotation,m_teapotRotation);
  // now set this value in the shader for the current ModelMatrix
  m_transformStack.LoadGlobalAndCurrentMatrixToShader("gl3xTest","ModelMatrix");
  prim->DrawVBO(m_vboname);
  /*else{
  glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glColor3f(0,0,1); glVertex3f(0,0,1);
    glColor3f(1,0,1); glVertex3f(1,0,1);
    glColor3f(1,1,1); glVertex3f(1,1,1);
    glColor3f(0,1,1); glVertex3f(0,1,1);
    glEnd();
  }*/
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

void GLWindow::CreateLights()
{
  // light position
  ngl::Vector pos;
  // light colour
  ngl::Colour col,speccol;
  // loop for the 8 lights and set the position and colour
  for(int i=0; i<8; ++i)
    {
    // get a random light position
      pos.Set(ngl::RandomNum(20),ngl::RandomNum(20),ngl::RandomNum(20));
      // create random colour
      col.Set(ngl::RandomPosNum(100)/200.0,ngl::RandomPosNum(100)/200.0,ngl::RandomPosNum(100)/200.0);
      speccol.Set(ngl::RandomPosNum(100)/200.0,ngl::RandomPosNum(100)/200.0,ngl::RandomPosNum(100)/200.0);
      // create an instance of the light and put it in the array
      m_lightArray[i] = new ngl::Light(pos,col,speccol,ngl::LIGHTLOCAL);
      }
}

void GLWindow::timerEvent(
                          QTimerEvent *_event
                         )
{
  if(_event->timerId() == m_rotationTimer)
  {
    ++m_teapotRotation;
    // re-draw GL
    updateGL();
  }
/*
  else if(_event->timerId() == m_lightChangeTimer)
  {
    ngl::Vector pos;
    ngl::Colour col;
    ngl::Colour speccol;

    for(int i=0; i<8; ++i)
    {
      pos.Set(ngl::RandomNum(20),ngl::RandomNum(20),ngl::RandomNum(20));
      // create random colour
      col.Set(ngl::RandomPosNum(100)/200.0,ngl::RandomPosNum(100)/200.0,ngl::RandomPosNum(100)/200.0);
      speccol.Set(ngl::RandomPosNum(100)/200.0,ngl::RandomPosNum(100)/200.0,ngl::RandomPosNum(100)/200.0);
      m_lightArray[i]->SetPosition(pos);
      m_lightArray[i]->SetColour(col);
      m_lightArray[i]->SetSpecColour(speccol);
    }
    // re-draw GL
    updateGL();

  }
*/
}

