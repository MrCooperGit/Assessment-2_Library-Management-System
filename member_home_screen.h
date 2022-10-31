#ifndef MEMBER_HOME_SCREEN_H
#define MEMBER_HOME_SCREEN_H

#include <QWidget>

namespace Ui {
class member_home_screen;
}

class member_home_screen : public QWidget
{
    Q_OBJECT

public:
    explicit member_home_screen(QWidget *parent = nullptr);
    ~member_home_screen();

private slots:
    void on_pushButton_clicked();

    void on_button_img_1_clicked();

    void on_pushButton_2_clicked();

    void on_button_img_2_clicked();

private:
    Ui::member_home_screen *ui;
};

#endif // MEMBER_HOME_SCREEN_H
