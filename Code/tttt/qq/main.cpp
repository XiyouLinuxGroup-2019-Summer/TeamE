#include "qqwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qqWindow w;
    w.show();

    return a.exec();
}
