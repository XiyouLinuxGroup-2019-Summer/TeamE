#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>

namespace Ui {
class myWindow;
}

class myWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit myWindow(QWidget *parent = nullptr);
    ~myWindow();

private slots:    //cao han shu
    void login();
    void closeThis();


    void on_close_clicked();

    void on_le_account_textChanged(const QString &arg1);

private:
    Ui::myWindow *ui;
};

#endif // MYWINDOW_H
