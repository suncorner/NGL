/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Tue May 11 22:16:25 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *s_centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *s_FrameSplitter;
    QFrame *s_glFrame;
    QGroupBox *s_controlGB;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(801, 455);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setBaseSize(QSize(0, 0));
        s_centralWidget = new QWidget(MainWindow);
        s_centralWidget->setObjectName(QString::fromUtf8("s_centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(s_centralWidget->sizePolicy().hasHeightForWidth());
        s_centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(s_centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        s_FrameSplitter = new QSplitter(s_centralWidget);
        s_FrameSplitter->setObjectName(QString::fromUtf8("s_FrameSplitter"));
        s_FrameSplitter->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(s_FrameSplitter->sizePolicy().hasHeightForWidth());
        s_FrameSplitter->setSizePolicy(sizePolicy1);
        s_FrameSplitter->setMinimumSize(QSize(0, 0));
        s_FrameSplitter->setLineWidth(9);
        s_FrameSplitter->setOrientation(Qt::Horizontal);
        s_FrameSplitter->setHandleWidth(7);
        s_glFrame = new QFrame(s_FrameSplitter);
        s_glFrame->setObjectName(QString::fromUtf8("s_glFrame"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(s_glFrame->sizePolicy().hasHeightForWidth());
        s_glFrame->setSizePolicy(sizePolicy2);
        s_glFrame->setMinimumSize(QSize(0, 0));
        s_glFrame->setBaseSize(QSize(0, 0));
        s_glFrame->setFrameShape(QFrame::StyledPanel);
        s_glFrame->setFrameShadow(QFrame::Raised);
        s_FrameSplitter->addWidget(s_glFrame);
        s_controlGB = new QGroupBox(s_FrameSplitter);
        s_controlGB->setObjectName(QString::fromUtf8("s_controlGB"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(s_controlGB->sizePolicy().hasHeightForWidth());
        s_controlGB->setSizePolicy(sizePolicy3);
        s_controlGB->setMinimumSize(QSize(0, 0));
        s_FrameSplitter->addWidget(s_controlGB);

        horizontalLayout->addWidget(s_FrameSplitter);

        MainWindow->setCentralWidget(s_centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 801, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "NCCA Mesh Editor", 0, QApplication::UnicodeUTF8));
        s_controlGB->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
