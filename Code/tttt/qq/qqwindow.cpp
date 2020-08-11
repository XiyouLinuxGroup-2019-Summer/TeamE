#include "qqwindow.h"
#include "ui_qqwindow.h"

qqWindow::qqWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qqWindow)
{
    ui->setupUi(this);
}

qqWindow::~qqWindow()
{
    delete ui;
}
