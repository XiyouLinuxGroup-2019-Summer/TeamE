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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QRadioButton *radioButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myWindow)
    {
        if (myWindow->objectName().isEmpty())
            myWindow->setObjectName(QString::fromUtf8("myWindow"));
        myWindow->setEnabled(true);
        myWindow->resize(878, 527);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        myWindow->setFont(font);
        centralWidget = new QWidget(myWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(370, 50, 81, 31));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 226, 216);\n"
"background-color: rgb(227, 252, 253);"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(220, 160, 411, 27));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(220, 210, 411, 27));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(widget1);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);

        widget2 = new QWidget(centralWidget);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(161, 398, 214, 33));
        horizontalLayout_4 = new QHBoxLayout(widget2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_4->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(widget2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);

        widget3 = new QWidget(centralWidget);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(161, 321, 90, 25));
        horizontalLayout_3 = new QHBoxLayout(widget3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        radioButton = new QRadioButton(widget3);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        horizontalLayout_3->addWidget(radioButton);

        myWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(myWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 878, 28));
        myWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        myWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(myWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        myWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(lineEdit, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);

        retranslateUi(myWindow);

        QMetaObject::connectSlotsByName(myWindow);
    } // setupUi

    void retranslateUi(QMainWindow *myWindow)
    {
        myWindow->setWindowTitle(QApplication::translate("myWindow", "myWindow", nullptr));
        label_4->setText(QApplication::translate("myWindow", "QQ\347\231\273\345\275\225", nullptr));
        label->setText(QApplication::translate("myWindow", "\347\231\273\345\275\225:", nullptr));
        label_2->setText(QApplication::translate("myWindow", "\350\264\246\345\217\267:", nullptr));
        pushButton->setText(QApplication::translate("myWindow", "\347\231\273\345\275\225", nullptr));
        pushButton_2->setText(QApplication::translate("myWindow", "\345\217\226\346\266\210", nullptr));
        label_3->setText(QApplication::translate("myWindow", "\350\256\260\344\275\217\345\257\206\347\240\201 :", nullptr));
        radioButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class myWindow: public Ui_myWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWINDOW_H
