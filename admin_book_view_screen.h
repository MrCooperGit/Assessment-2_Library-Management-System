#ifndef ADMIN_BOOK_VIEW_SCREEN_H
#define ADMIN_BOOK_VIEW_SCREEN_H

#include <QWidget>

namespace Ui {
class admin_book_view_screen;
}

class admin_book_view_screen : public QWidget
{
    Q_OBJECT

public:
    explicit admin_book_view_screen(QWidget *parent = nullptr);
    ~admin_book_view_screen();

private slots:
    void on_pushButton_home_clicked();

    void on_pushButton_catalogue_clicked();

    void on_pushButton_edit_clicked();

private:
    Ui::admin_book_view_screen *ui;
};

#endif // ADMIN_BOOK_VIEW_SCREEN_H
