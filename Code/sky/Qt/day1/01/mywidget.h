#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class Mywidget : public QWidget
{
    Q_OBJECT

public:
    Mywidget(QWidget *parent = 0);
    ~Mywidget();
};

#endif // MYWIDGET_H
