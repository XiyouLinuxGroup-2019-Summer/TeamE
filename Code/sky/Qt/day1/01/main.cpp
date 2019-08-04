#include "mywidget.h"
#include <QApplication>
阿道夫阿斯蒂芬
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mywidget w;
    w.show();

    return a.exec();
}
