#ifndef EDIT_MEMBER_SCREEN_H
#define EDIT_MEMBER_SCREEN_H

#include <QWidget>

namespace Ui {
class edit_member_screen;
}

class edit_member_screen : public QWidget
{
    Q_OBJECT

public:
    explicit edit_member_screen(QWidget *parent = nullptr);
    ~edit_member_screen();

private:
    Ui::edit_member_screen *ui;
};

#endif // EDIT_MEMBER_SCREEN_H
