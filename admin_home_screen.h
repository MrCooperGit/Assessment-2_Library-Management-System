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

private:
    Ui::admin_home_screen *ui;
};

#endif // ADMIN_HOME_SCREEN_H
