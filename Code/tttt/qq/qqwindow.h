#ifndef QQWINDOW_H
#define QQWINDOW_H

#include <QMainWindow>

namespace Ui {
class qqWindow;
}

class qqWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit qqWindow(QWidget *parent = nullptr);
    ~qqWindow();

private:
    Ui::qqWindow *ui;
};

#endif // QQWINDOW_H
