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

    void on_pushButton_addNewBook_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_modifyCatalogue_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_addNewMember_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_modifyMember_clicked();

private:
    Ui::admin_home_screen *ui;

};

#endif // ADMIN_HOME_SCREEN_H
