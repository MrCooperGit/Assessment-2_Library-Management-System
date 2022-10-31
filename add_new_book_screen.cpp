#include "add_new_book_screen.h"
#include "ui_add_new_book_screen.h"

add_new_book_screen::add_new_book_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_new_book_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Add New Book");
}

add_new_book_screen::~add_new_book_screen()
{
    delete ui;
}
