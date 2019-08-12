#include "expr.h"
#include "ui_expr.h"
#include"model.h"

expr::expr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::expr)
{
    ui->setupUi(this);
    connect(this->ui->btn_0,SIGNAL(clicked(bool)),this,SLOT(getBtn0()));  //绑定函数
    connect(this->ui->btn_1,SIGNAL(clicked(bool)),this,SLOT(getBtn1()));
    connect(this->ui->btn_2,SIGNAL(clicked(bool)),this,SLOT(getBtn2()));
    this->model1 = new model;

    this->temp = " ";
}

expr::~expr()
{
    delete ui;
}

void expr::getBtn0()
{
    if(temp != " ")
    {
        this->temp  += this->ui->btn_0->text();
        this->ui->lbl_display->setText(this->temp);
    }
}
//对于非 bool 类型,获取属性名本身,设置: set + 属性名
void expr::getBtn1()
{
    this->temp  += this->ui->btn_1->text();
    this->ui->lbl_display->setText(this->temp);
}

void expr::getBtn2()
{
    this->temp  += this->ui->btn_2->text();
    this->ui->lbl_display->setText(this->temp);
}

void expr::on_btn_3_clicked()
{
    this->temp += this->ui->btn_3->text();
    this->ui->lbl_display->setText(this->temp);
}

void expr::on_btn_4_clicked()
{
    this->temp += this->ui->btn_4->text();
    this->ui->lbl_display->setText(this->temp);
}

void expr::on_btn_5_clicked()
{
    this->temp += this->ui->btn_5->text();
    this->ui->lbl_display->setText(this->temp);
}

void expr::on_btn_6_clicked()
{
    this->temp += this->ui->btn_6->text();
    this->ui->lbl_display->setText(this->temp);
}

void expr::on_btn_7_clicked()
{
    this->temp += this->ui->btn_7->text();
    this->ui->lbl_display->setText(this->temp);
}

void expr::on_btn_8_clicked()
{
    this->temp += this->ui->btn_8->text();
    this->ui->lbl_display->setText(this->temp);
}

void expr::on_btn_9_clicked()
{
    this->temp += this->ui->btn_9->text();
    this->ui->lbl_display->setText(this->temp);

}

void expr::on_btn_plus_clicked()
{
    int num = this->temp.toInt();
    this->model1->setNum1(num);
    this->temp = " ";
    QString ex = this->ui->btn_plus->text();
    this->model1->setFlag(ex);
}

void expr::on_btn_sub_clicked()
{
    int num = this->temp.toInt();
    this->model1->setNum1(num);
    this->temp = " ";
    QString ex = this->ui->btn_sub->text();
    this->model1->setFlag(ex);

}

void expr::on_btn_mul_clicked()
{
    int num = this->temp.toInt();
    this->model1->setNum1(num);
    this->temp = " ";
    QString ex = this->ui->btn_mul->text();
    this->model1->setFlag(ex);
}

void expr::on_btn_div_clicked()
{
    int num = this->temp.toInt();
    this->model1->setNum1(num);
    this->temp = " ";
    QString ex = this->ui->btn_div->text();
    this->model1->setFlag(ex);
}

void expr::on_btn_equal_clicked()
{
    int num = this->temp.toInt();
    this->model1->setNum2(num);
    QString res = this->model1->doExpr();
    this->ui->lbl_display->setText(res);
    this->temp = " ";
}

void expr::on_btn_clear_clicked()
{
    this->temp = " ";
//    QString res = " ";
    this->ui->lbl_display->setText(temp);
}
