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

private:
    Ui::member_home_screen *ui;
};

#endif // MEMBER_HOME_SCREEN_H
