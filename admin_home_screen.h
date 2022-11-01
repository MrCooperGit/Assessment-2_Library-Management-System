#ifndef ADMIN_HOME_SCREEN_H
#define ADMIN_HOME_SCREEN_H

#include <QWidget>

namespace Ui {

class admin_home_screen;
}

class admin_home_screen : public QWidget

{
    Q_OBJECT

public:
    explicit admin_home_screen(QWidget *parent = nullptr);
    ~admin_home_screen();

private slots:
    void on_pushButton_clicked();

    void on_button_img_1_clicked();

    void on_pushButton_2_clicked();

    void on_button_img_2_clicked();

    void on_pushButton_3_clicked();

    void on_button_img_3_clicked();

    void on_pushButton_4_clicked();

    void on_button_img_4_clicked();

private:
    Ui::admin_home_screen *ui;

};

#endif // ADMIN_HOME_SCREEN_H
