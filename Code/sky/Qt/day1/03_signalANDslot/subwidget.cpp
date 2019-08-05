#include "subwidget.h"

subwidget::subwidget(QWidget *parent) : QWidget(parent)
{

    setWindowTitle("brother");
    b.setParent(this);
    b.setText("Change to Main Window");

    connect(&b,&QPushButton::clicked,this,&subwidget::sendslot);
}

void subwidget::sendslot()
{
    emit mysignal();//send signal
}
