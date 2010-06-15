#include "MainWindow.h"
#include "GLWindow.h"
#include <ngl/NGLInit.h>
#include <ngl/ShaderManager.h>

MainWindow::MainWindow(
                       QWidget *_parent
                      ):
                        QMainWindow(_parent)
{
    this->resize(QSize(1024,720));
    ngl::NGLInit *Init = ngl::NGLInit::Instance();
    Init->InitGlew();
    //Init->InitVBOandImageLib();

    m_mdiArea = new QMdiArea;
    m_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(m_mdiArea);
    this->setWindowTitle(QString("ngl Light demo"));

    GLWindow *child = new GLWindow(this,"cone0");
    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1->setWidget(child);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->setWindowTitle("light cone 0");
    subWindow1->resize(200,200);    
    m_mdiArea->addSubWindow(subWindow1);
    subWindow1->show();

    QMdiSubWindow *subWindow2 = new QMdiSubWindow;
    GLWindow *child2 = new GLWindow(this,"cone1");
    child2->m_instance=99;
    subWindow2->setWidget(child2);
    subWindow2->setAttribute(Qt::WA_DeleteOnClose);
    subWindow2->setWindowTitle("light cone2");
    subWindow2->resize(200,200);

    m_mdiArea->addSubWindow(subWindow2);


    QMdiSubWindow *subWindow3 = new QMdiSubWindow;
    GLWindow *child3 = new GLWindow(this,"cone3");
    subWindow3->setWidget(child3);
    subWindow3->setAttribute(Qt::WA_DeleteOnClose);
    subWindow3->setWindowTitle("light cone3");
    subWindow3->resize(200,200);

    m_mdiArea->addSubWindow(subWindow3);

    QMdiSubWindow *subWindow4 = new QMdiSubWindow;
    GLWindow *child4 = new GLWindow(this,"cone4");

    subWindow4->setWidget(child4);
    subWindow4->setAttribute(Qt::WA_DeleteOnClose);
    subWindow4->setWindowTitle("light cone4");
    subWindow4->resize(200,200);

    m_mdiArea->addSubWindow(subWindow4);




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
}

void MainWindow::resizeEvent ( QResizeEvent * _event )
{
}

