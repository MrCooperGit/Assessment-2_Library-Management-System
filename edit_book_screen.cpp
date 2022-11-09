#include "edit_book_screen.h"
#include "ui_edit_book_screen.h"

edit_book_screen::edit_book_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_book_screen)
{
    ui->setupUi(this);
}

edit_book_screen::~edit_book_screen()
{
    delete ui;
}
