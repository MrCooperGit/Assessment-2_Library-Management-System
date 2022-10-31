#ifndef ADD_NEW_BOOK_SCREEN_H
#define ADD_NEW_BOOK_SCREEN_H

#include <QWidget>

namespace Ui {
class add_new_book_screen;
}

class add_new_book_screen : public QWidget
{
    Q_OBJECT

public:
    explicit add_new_book_screen(QWidget *parent = nullptr);
    ~add_new_book_screen();

private:
    Ui::add_new_book_screen *ui;
};

#endif // ADD_NEW_BOOK_SCREEN_H
