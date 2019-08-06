#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <subwidget.h>//chid window head file
class Mainwidget : public QWidget
{
    Q_OBJECT

public:
    Mainwidget(QWidget *parent = 0);
    ~Mainwidget();

    void mySlot();
    void changewindow();

private:
    QPushButton b1;
    QPushButton *b2;
    QPushButton b3;

    subwidget w;
};

#endif // MAINWIDGET_H
