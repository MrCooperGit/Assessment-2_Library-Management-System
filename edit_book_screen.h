#ifndef EDIT_BOOK_SCREEN_H
#define EDIT_BOOK_SCREEN_H

#include <QWidget>

namespace Ui {
class edit_book_screen;
}

class edit_book_screen : public QWidget
{
    Q_OBJECT

public:
    explicit edit_book_screen(QString id, QWidget *parent = nullptr);
    ~edit_book_screen();

private slots:
    void on_pushButton_home_clicked();

    void on_pushButton_members_clicked();

    void on_pushButton_submit_clicked();

private:
    Ui::edit_book_screen *ui;
};

#endif // EDIT_BOOK_SCREEN_H
