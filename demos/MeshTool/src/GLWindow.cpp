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
#include "ngl/NCCABinMesh.h"


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
  std::cout<<_parent->size().width()<<" height "<<_parent->size().height()<<std::endl;
  // Now set the initial GLWindow attributes to default values
  // Roate is false
  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace=0;
  m_spinYFace=0;
  m_origX=0;
  m_origY=0;

}

GLWindow::~GLWindow()
{

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
   ngl::Vector From(0,0,1);
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

   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST); // for removal of hidden surfaces
   glEnable(GL_NORMALIZE); // normalize vectors for proper shading
   ngl::Light *l = new ngl::Light(ngl::Vector(0,2,0),ngl::Colour(1,1,1),ngl::Colour(1,1,1),ngl::LIGHTLOCAL);
   l->Enable();
   //m_mesh = new ngl::Obj("models/troll.obj");//,"textures/helix_base.png");
   //m_mesh->CreateVBO(GL_STATIC_DRAW);
   ngl::Material m(ngl::POLISHEDSILVER);
   m.Use();
   glEnable(GL_TEXTURE_2D);
   std::cout<<"doing Save\n";
   //m_mesh->SaveNCCABinaryMesh("models/troll.bin");
   //delete m_mesh;
   std::cout<<"Now re-load"<<std::endl;
   m_bin = new ngl::NCCABinMesh("models/troll.bin","textures/2k_colourmap.tiff");
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
  //m_mesh->DrawBBox();
  //m_mesh->DrawVBO();
  m_bin->DrawBBox();
  m_bin->DrawVBO();
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

void GLWindow::ProcessKeys(
                           QKeyEvent *_event
                          )
{
  const static ngl::Real INC=0.1;
  bool update=false;
  switch (_event->key())
  {
    case Qt::Key_Up    : { m_cam->Move(0.0,INC,0.0);  update=true; break; }
    case Qt::Key_Down  : { m_cam->Move(0.0,-INC,0.0); update=true; break; }
    case Qt::Key_Left  : { m_cam->Move(-INC,0.0,0.0); update=true; break; }
    case Qt::Key_Right : { m_cam->Move(INC,0.0,0.0);  update=true; break; }
    case Qt::Key_I     : { m_cam->Move(0.0,0.0,INC);  update=true; break; }
    case Qt::Key_O     : { m_cam->Move(0.0,0.0,-INC); update=true; break; }

  }
  if(update == true)
  {
    ngl::ShaderManager *shader=ngl::ShaderManager::Instance();
    shader->SetShaderParamFromMatrix("gl3xTest","ViewMatrix",m_cam->GetModelView());
  }
}


void GLWindow::resizeEvent(
                                QResizeEvent *_event
                               )
{
  std::cout<<"resize event called\n";
  std::cout<<_event->size().width()<<" "<<_event->size().height()<<"\n";

}
