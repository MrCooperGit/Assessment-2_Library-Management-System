#ifndef MEMBER_BOOK_ORDER_SCREEN_H
#define MEMBER_BOOK_ORDER_SCREEN_H

#include <QWidget>

namespace Ui {
class member_book_order_screen;
}

class member_book_order_screen : public QWidget
{
    Q_OBJECT

public:
    explicit member_book_order_screen(QString memberInfo, QWidget *parent = nullptr);
    ~member_book_order_screen();

private slots:
    void on_pushButton_home_clicked();

    void on_pushButton_catalogue_clicked();

    void on_pushButton_order_clicked();

private:
    Ui::member_book_order_screen *ui;
};

#endif // MEMBER_BOOK_ORDER_SCREEN_H
