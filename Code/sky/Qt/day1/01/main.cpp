#include "mywidget.h"

//QApplication
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mywidget w;
    w.show();

    return a.exec();
}
