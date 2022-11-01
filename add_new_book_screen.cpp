#include "add_new_book_screen.h"
#include "ui_add_new_book_screen.h"
#include <QPixmap>

add_new_book_screen::add_new_book_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_new_book_screen)
{
    ui->setupUi(this);
    //Basic window style
    this->setWindowTitle("Add New Book");
    this->setStyleSheet("background-color: white;");

    QPixmap headerlogo_pix("://img/addBook.label.png");
    ui->header_img->setPixmap(headerlogo_pix);

    QPixmap footerlogo_pix(":/img/library.label.png");
    ui->footer_img->setPixmap(footerlogo_pix);
}

add_new_book_screen::~add_new_book_screen()
{
    delete ui;
}


