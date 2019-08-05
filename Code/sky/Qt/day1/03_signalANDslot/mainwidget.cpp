#include "mainwidget.h"

#include <QPushButton>

Mainwidget::Mainwidget(QWidget *parent)
    : QWidget(parent)
{
    b1.setParent(this);
    b1.setText("close");
    b1.move(100,100);

    b2 = new QPushButton(this);
    b2->setText("abc");

    connect(&b1,&QPushButton::pressed,this,&Mainwidget::close);
    /* &b1信号发出者，指针类型
       &Qpushbutton::pressed 处理的信号     &发送者的类名::信号名字
       this 信号接受者
       &MainWeidget::close; 槽函数，信号处理   &发送者的类名::槽函数名字
    */


    /*自定义槽：普通函数的用法
        Qt5任意成员函数,普通全局函数，静态函数
        槽函数需要和信号一致(参数，返回值)
        由于信都没有返回值，所以槽函数一定没有返回值
    */
    connect(b2,&QPushButton::released,this,&Mainwidget::mySlot);
    connect(b2,&QPushButton::released,&b1,&QPushButton::hide);

    setWindowTitle("boss");
    //this->setWindowTitle("boss");

    b3.setParent(this);
    b3.setText("Change Window");
    b3.move(50,50);

    connect(&b3,&QPushButton::released,this,&Mainwidget::changewindow);
    //w.show();

    connect(&w,&subwidget::mysignal,this,&Mainwidget::dealsub);

}

void Mainwidget::mySlot()
{
    b2->setText("change");
}

void Mainwidget::changewindow()
{
    //child show
    w.show();
    //self shadow
    this->hide();
}

void Mainwidget::dealsub()
{
    w.hide();
    show();
}

Mainwidget::~Mainwidget()
{

}
