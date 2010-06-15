#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  std::cout<<ui->s_glFrame->size().width()<<" height "<<ui->s_glFrame->size().height()<<std::endl;
  ui->s_glFrame->resize(QSize(600,420));
  m_gl = new GLWindow(ui->s_glFrame);
}

MainWindow::~MainWindow()
{
    delete m_gl;
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
