#ifndef MEMBER_LIST_SCREEN_H
#define MEMBER_LIST_SCREEN_H

#include <QWidget>

namespace Ui {
class member_list_screen;
}

class member_list_screen : public QWidget
{
    Q_OBJECT

public:
    explicit member_list_screen(QWidget *parent = nullptr);
    ~member_list_screen();

private slots:
    void on_pushButton_home_clicked();

    void on_pushButton_modifyCatalogue_clicked();

    void on_pushButton_addNewMember_clicked();

    void on_pushButton_search_clicked();

private:
    Ui::member_list_screen *ui;
};

#endif // MEMBER_LIST_SCREEN_H
