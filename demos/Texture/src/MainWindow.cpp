#include "MainWindow.h"
#include "GLWindow.h"

MainWindow::MainWindow(
                       QWidget *_parent
                      ):
                        QMainWindow(_parent)
{
    this->resize(QSize(1024,720));
    m_gl = new GLWindow(this);
    this->setWindowTitle(QString("ngl obj and texture demo"));
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(
                               QKeyEvent *_event
                              )
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
  case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
  default : break;
  }
  // finally update the GLWindow and re-draw
  m_gl->ProcessKeys(_event);
  m_gl->updateGL();
}

void MainWindow::resizeEvent ( QResizeEvent * _event )
{
  m_gl->resize(_event->size());
}

