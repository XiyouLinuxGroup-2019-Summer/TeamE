/********************************************************************************
** Form generated from reading UI file 'mywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWINDOW_H
#define UI_MYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myWindow)
    {
        if (myWindow->objectName().isEmpty())
            myWindow->setObjectName(QString::fromUtf8("myWindow"));
        myWindow->resize(400, 300);
        menuBar = new QMenuBar(myWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        myWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        myWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(myWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        myWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(myWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        myWindow->setStatusBar(statusBar);

        retranslateUi(myWindow);

        QMetaObject::connectSlotsByName(myWindow);
    } // setupUi

    void retranslateUi(QMainWindow *myWindow)
    {
        myWindow->setWindowTitle(QApplication::translate("myWindow", "myWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myWindow: public Ui_myWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWINDOW_H
