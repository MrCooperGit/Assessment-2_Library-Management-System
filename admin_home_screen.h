#ifndef ADMIN_HOME_SCREEN_H
#define ADMIN_HOME_SCREEN_H

#include <QWidget>

namespace Ui {
class Admin_Home_Screen;
}

class Admin_Home_Screen : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_Home_Screen(QWidget *parent = nullptr);
    ~Admin_Home_Screen();

private:
    Ui::Admin_Home_Screen *ui;
};

#endif // ADMIN_HOME_SCREEN_H
