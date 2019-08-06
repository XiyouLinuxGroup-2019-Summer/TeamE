#include <QApplication>
#include <QWidget>
#include <QPushButton>
int main(int argc,char **argv)
{
    QApplication app(argc,argv);
    QWidget w;
    w.setWindowTitle("Hello world");//title


    QPushButton b;
    b.setText("button1");//button
    b.setParent(&w);

    b.move(100,100);


    QPushButton b2(&w);
    b.setText("button2");

    w.show();
    return app.exec();
}
