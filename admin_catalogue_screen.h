#ifndef ADMIN_CATALOGUE_SCREEN_H
#define ADMIN_CATALOGUE_SCREEN_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class admin_catalogue_screen;
}

class admin_catalogue_screen : public QWidget
{
    Q_OBJECT

public:
    explicit admin_catalogue_screen(QWidget *parent = nullptr);
    ~admin_catalogue_screen();

private slots:
    void on_pushButton_home_clicked();

    void on_pushButton_modifyMembers_clicked();

    void on_pushButton_addNewBook_clicked();

    void on_pushButton_search_clicked();

    void on_label_username_windowTitleChanged(const QString &title);

    void edit_btn_clicked(QString);

    void book_btn_clicked(QString);

private:
    Ui::admin_catalogue_screen *ui;
};

#endif // ADMIN_CATALOGUE_SCREEN_H
