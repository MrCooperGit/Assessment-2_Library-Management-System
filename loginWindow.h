#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();


public slots:
    void currentDate();

private slots:
    void on_pushButton_register_clicked();

    void on_pushButton_login_clicked();

    void on_lineEdit_email_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::LoginWindow *ui;
    QTimer *timer; //object to start timer to find date with currentDate()

};
#endif // LOGINWINDOW_H
