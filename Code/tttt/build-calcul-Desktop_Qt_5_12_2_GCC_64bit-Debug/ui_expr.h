/********************************************************************************
** Form generated from reading UI file 'expr.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPR_H
#define UI_EXPR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_expr
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lbl_display;
    QGridLayout *gridLayout;
    QPushButton *btn_6;
    QPushButton *btn_equal;
    QPushButton *btn_8;
    QPushButton *btn_5;
    QPushButton *btn_3;
    QPushButton *btn_7;
    QPushButton *btn_4;
    QPushButton *btn_mul;
    QPushButton *btn_2;
    QPushButton *btn_plus;
    QPushButton *btn_div;
    QPushButton *btn_sub;
    QPushButton *btn_0;
    QPushButton *btn_9;
    QPushButton *btn_1;
    QPushButton *btn_clear;

    void setupUi(QDialog *expr)
    {
        if (expr->objectName().isEmpty())
            expr->setObjectName(QString::fromUtf8("expr"));
        expr->resize(394, 480);
        expr->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(expr);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        lbl_display = new QLabel(expr);
        lbl_display->setObjectName(QString::fromUtf8("lbl_display"));
        lbl_display->setStyleSheet(QString::fromUtf8("font: 57 20pt \"Ubuntu\";\n"
"color: rgb(46, 52, 54);"));
        lbl_display->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(lbl_display);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn_6 = new QPushButton(expr);
        btn_6->setObjectName(QString::fromUtf8("btn_6"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_6->sizePolicy().hasHeightForWidth());
        btn_6->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_6, 1, 2, 1, 1);

        btn_equal = new QPushButton(expr);
        btn_equal->setObjectName(QString::fromUtf8("btn_equal"));
        sizePolicy.setHeightForWidth(btn_equal->sizePolicy().hasHeightForWidth());
        btn_equal->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_equal, 3, 2, 1, 1);

        btn_8 = new QPushButton(expr);
        btn_8->setObjectName(QString::fromUtf8("btn_8"));
        sizePolicy.setHeightForWidth(btn_8->sizePolicy().hasHeightForWidth());
        btn_8->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_8, 0, 1, 1, 1);

        btn_5 = new QPushButton(expr);
        btn_5->setObjectName(QString::fromUtf8("btn_5"));
        sizePolicy.setHeightForWidth(btn_5->sizePolicy().hasHeightForWidth());
        btn_5->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_5, 1, 1, 1, 1);

        btn_3 = new QPushButton(expr);
        btn_3->setObjectName(QString::fromUtf8("btn_3"));
        sizePolicy.setHeightForWidth(btn_3->sizePolicy().hasHeightForWidth());
        btn_3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_3, 2, 2, 1, 1);

        btn_7 = new QPushButton(expr);
        btn_7->setObjectName(QString::fromUtf8("btn_7"));
        sizePolicy.setHeightForWidth(btn_7->sizePolicy().hasHeightForWidth());
        btn_7->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_7, 0, 0, 1, 1);

        btn_4 = new QPushButton(expr);
        btn_4->setObjectName(QString::fromUtf8("btn_4"));
        sizePolicy.setHeightForWidth(btn_4->sizePolicy().hasHeightForWidth());
        btn_4->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_4, 1, 0, 1, 1);

        btn_mul = new QPushButton(expr);
        btn_mul->setObjectName(QString::fromUtf8("btn_mul"));
        sizePolicy.setHeightForWidth(btn_mul->sizePolicy().hasHeightForWidth());
        btn_mul->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_mul, 2, 3, 1, 1);

        btn_2 = new QPushButton(expr);
        btn_2->setObjectName(QString::fromUtf8("btn_2"));
        sizePolicy.setHeightForWidth(btn_2->sizePolicy().hasHeightForWidth());
        btn_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_2, 2, 1, 1, 1);

        btn_plus = new QPushButton(expr);
        btn_plus->setObjectName(QString::fromUtf8("btn_plus"));
        sizePolicy.setHeightForWidth(btn_plus->sizePolicy().hasHeightForWidth());
        btn_plus->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_plus, 0, 3, 1, 1);

        btn_div = new QPushButton(expr);
        btn_div->setObjectName(QString::fromUtf8("btn_div"));
        sizePolicy.setHeightForWidth(btn_div->sizePolicy().hasHeightForWidth());
        btn_div->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_div, 3, 3, 1, 1);

        btn_sub = new QPushButton(expr);
        btn_sub->setObjectName(QString::fromUtf8("btn_sub"));
        sizePolicy.setHeightForWidth(btn_sub->sizePolicy().hasHeightForWidth());
        btn_sub->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_sub, 1, 3, 1, 1);

        btn_0 = new QPushButton(expr);
        btn_0->setObjectName(QString::fromUtf8("btn_0"));
        sizePolicy.setHeightForWidth(btn_0->sizePolicy().hasHeightForWidth());
        btn_0->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_0, 3, 1, 1, 1);

        btn_9 = new QPushButton(expr);
        btn_9->setObjectName(QString::fromUtf8("btn_9"));
        sizePolicy.setHeightForWidth(btn_9->sizePolicy().hasHeightForWidth());
        btn_9->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_9, 0, 2, 1, 1);

        btn_1 = new QPushButton(expr);
        btn_1->setObjectName(QString::fromUtf8("btn_1"));
        sizePolicy.setHeightForWidth(btn_1->sizePolicy().hasHeightForWidth());
        btn_1->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_1, 2, 0, 1, 1);

        btn_clear = new QPushButton(expr);
        btn_clear->setObjectName(QString::fromUtf8("btn_clear"));
        sizePolicy.setHeightForWidth(btn_clear->sizePolicy().hasHeightForWidth());
        btn_clear->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btn_clear, 3, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 8);

        retranslateUi(expr);

        QMetaObject::connectSlotsByName(expr);
    } // setupUi

    void retranslateUi(QDialog *expr)
    {
        expr->setWindowTitle(QApplication::translate("expr", "\350\256\241\347\256\227\345\231\250", nullptr));
        lbl_display->setText(QApplication::translate("expr", "0", nullptr));
        btn_6->setText(QApplication::translate("expr", "6", nullptr));
        btn_equal->setText(QApplication::translate("expr", "=", nullptr));
        btn_8->setText(QApplication::translate("expr", "8", nullptr));
        btn_5->setText(QApplication::translate("expr", "5", nullptr));
        btn_3->setText(QApplication::translate("expr", "3", nullptr));
        btn_7->setText(QApplication::translate("expr", "7", nullptr));
        btn_4->setText(QApplication::translate("expr", "4", nullptr));
        btn_mul->setText(QApplication::translate("expr", "*", nullptr));
        btn_2->setText(QApplication::translate("expr", "2", nullptr));
        btn_plus->setText(QApplication::translate("expr", "+", nullptr));
        btn_div->setText(QApplication::translate("expr", "/", nullptr));
        btn_sub->setText(QApplication::translate("expr", "-", nullptr));
        btn_0->setText(QApplication::translate("expr", "0", nullptr));
        btn_9->setText(QApplication::translate("expr", "9", nullptr));
        btn_1->setText(QApplication::translate("expr", "1", nullptr));
        btn_clear->setText(QApplication::translate("expr", "c", nullptr));
    } // retranslateUi

};

namespace Ui {
    class expr: public Ui_expr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPR_H
