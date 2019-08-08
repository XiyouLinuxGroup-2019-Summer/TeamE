#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->btn_0,SIGNAL(clicked(bool)),this,SLOT(getbut0()));
    connect(this->ui->btn_1,SIGNAL(clicked(bool)),this,SLOT(getbut1()));
    connect(this->ui->btn_2,SIGNAL(clicked(bool)),this,SLOT(getbut2()));
    this->mod = new model;

    this->tmp = "";//init
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getbut0()
{
    if(this->tmp != "")
    {
        this->tmp += this->ui->btn_0->text();
        this->ui->lbl_display->setText(this->tmp);
    }

}

void MainWindow::getbut1()
{
    this->tmp += this->ui->btn_1->text();
    this->ui->lbl_display->setText(this->tmp);
}

void MainWindow::getbut2()
{
    this->tmp += this->ui->btn_2->text();
    this->ui->lbl_display->setText(this->tmp);
}

void MainWindow::on_btn_4_clicked()
{
    this->tmp += this->ui->btn_4->text();
    this->ui->lbl_display->setText(this->tmp);
}

void MainWindow::on_btn_5_clicked()
{
    this->tmp += this->ui->btn_5->text();
    this->ui->lbl_display->setText(this->tmp);
}

void MainWindow::on_btn_6_clicked()
{
    this->tmp += this->ui->btn_6->text();
    this->ui->lbl_display->setText(this->tmp);
}

void MainWindow::on_btn_7_clicked()
{
    this->tmp += this->ui->btn_7->text();
    this->ui->lbl_display->setText(this->tmp);
}

void MainWindow::on_btn_8_clicked()
{
    this->tmp += this->ui->btn_8->text();
    this->ui->lbl_display->setText(this->tmp);
}

void MainWindow::on_btn_9_clicked()
{
    this->tmp += this->ui->btn_9->text();
    this->ui->lbl_display->setText(this->tmp);
}

void MainWindow::on_btn_3_clicked()
{
    this->tmp += this->ui->btn_3->text();
    this->ui->lbl_display->setText(this->tmp);
}

void MainWindow::on_btn_plus_clicked()
{
    int num = this->tmp.toInt();
    this->mod->setNum1(num);
    this->tmp = "";
    this->ui->lbl_display->setText(this->tmp);
    QString ex = this->ui->btn_plus->text();
    this->mod->setFlag(ex);
}

void MainWindow::on_btn_sub_clicked()
{
    int num = this->tmp.toInt();
    this->mod->setNum1(num);
    this->tmp = "";
    this->ui->lbl_display->setText(this->tmp);
    QString ex = this->ui->btn_sub->text();
    this->mod->setFlag(ex);
}

void MainWindow::on_btn_mul_clicked()
{
    int num = this->tmp.toInt();
    this->mod->setNum1(num);
    this->tmp = "";
    this->ui->lbl_display->setText(this->tmp);
    QString ex = this->ui->btn_mul->text();
    this->mod->setFlag(ex);
}

void MainWindow::on_btn_div_clicked()
{
    int num = this->tmp.toInt();
    this->mod->setNum1(num);
    this->tmp = "";
    this->ui->lbl_display->setText(this->tmp);
    QString ex = this->ui->btn_div->text();
    this->mod->setFlag(ex);
}

void MainWindow::on_btn_equal_clicked()
{
    int num = this->tmp.toInt();
    this->mod->setNum2(num);
    QString res = this->mod->doexpr();
    this->ui->lbl_display->setText(res);
    this->tmp = "";
}

void MainWindow::on_btn_clear_clicked()
{
    this->tmp = "";
    this->ui->lbl_display->setText("0");
}
