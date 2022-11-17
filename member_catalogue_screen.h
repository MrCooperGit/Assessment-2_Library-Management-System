#ifndef MEMBER_CATALOGUE_SCREEN_H
#define MEMBER_CATALOGUE_SCREEN_H

#include <QWidget>

namespace Ui {
class member_catalogue_screen;
}

class member_catalogue_screen : public QWidget
{
    Q_OBJECT

public:
    explicit member_catalogue_screen(QWidget *parent = nullptr);
    ~member_catalogue_screen();

private slots:
    void on_pushButton_home_clicked();

    void member_btn_clicked(QString);

    void on_pushButton_search_clicked();

    void on_pushButton_yourItems_clicked();

private:
    Ui::member_catalogue_screen *ui;
};

#endif // MEMBER_CATALOGUE_SCREEN_H
