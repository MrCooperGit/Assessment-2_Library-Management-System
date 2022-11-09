#ifndef ADD_NEW_MEMBER_SCREEN_H
#define ADD_NEW_MEMBER_SCREEN_H

#include <QWidget>

namespace Ui {
class add_new_member_screen;
}

class add_new_member_screen : public QWidget
{
    Q_OBJECT

public:
    explicit add_new_member_screen(QWidget *parent = nullptr);
    ~add_new_member_screen();

private slots:
    void on_pushButton_home_clicked();

    void on_pushButton_members_clicked();

    void on_pushButton_submit_clicked();

private:
    Ui::add_new_member_screen *ui;
};

#endif // ADD_NEW_MEMBER_SCREEN_H
