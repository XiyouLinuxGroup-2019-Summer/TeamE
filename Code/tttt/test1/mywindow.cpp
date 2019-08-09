#include "mywindow.h"
#include "ui_mywindow.h"
#include <QDebug>
#include<QString>

myWindow::myWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myWindow)
{
    ui->setupUi(this);
    //connect(谁,发出了什么信号,谁,执行了什么操作);
    connect(this->ui->denglu,SIGNAL(clicked(bool)),this,SLOT(login()));
//    connect(this->ui->close,SIGNAL(clicked(bool)),this,SLOT(closeThis()));
}

myWindow::~myWindow()
{
    delete ui;
}

void myWindow::login()
{
    static int count = 0;
    qDebug() << "login";
    QString name = this->ui->le_account->text();
    QString password = this->ui->le_password->text();

    if(name == "jack" && password == "1234")
    {
        qDebug() << "ok";
    }
    else
    {
        count++;
        qDebug() << "no";
        if(count > 3)
        {
            //this->close();
            disconnect(this->ui->denglu,SIGNAL(clicked(bool)),this,SLOT(login()));
        }
    }

}

void myWindow::closeThis()
{
    this->close();
}

void myWindow::on_close_clicked()
{
    this->close();
}

void myWindow::on_le_account_textChanged(const QString &arg1)
{
    qDebug() << "wen ben gai bian l";
}
