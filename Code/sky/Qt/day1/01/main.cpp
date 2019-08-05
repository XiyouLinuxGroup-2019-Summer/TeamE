#include "mywidget.h"

#include <QApplication>//yingyongchengxulei

//QApplication应用程序类
//Qt头文件没有.h
//头文件和类名一样
int main(int argc, char *argv[])
{
    //only one object
    QApplication a(argc, argv);


    Mywidget w;
    w.show();

    //让程序一直执行
    //等待事件发生
    return a.exec();
}
