#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class subwidget : public QWidget
{
    Q_OBJECT
public:
    explicit subwidget(QWidget *parent = 0);
    void sendslot;
private:
    QPushButton b;
signals:
     //There must be signals.
    //It have no return value,but can have arcgument.
    //It do not need to be defined.
    void mysignal();
public slots:
};

#endif // SUBWIDGET_H
