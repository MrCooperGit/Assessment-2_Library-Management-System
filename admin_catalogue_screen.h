#ifndef ADMIN_CATALOGUE_SCREEN_H
#define ADMIN_CATALOGUE_SCREEN_H

#include <QWidget>

namespace Ui {
class admin_catalogue_screen;
}

class admin_catalogue_screen : public QWidget
{
    Q_OBJECT

public:
    explicit admin_catalogue_screen(QWidget *parent = nullptr);
    ~admin_catalogue_screen();

private:
    Ui::admin_catalogue_screen *ui;
};

#endif // ADMIN_CATALOGUE_SCREEN_H
