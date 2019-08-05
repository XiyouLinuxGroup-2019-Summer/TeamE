#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mainwidget w;//先执行构造函数
    w.show();

    return a.exec();//wait
}
