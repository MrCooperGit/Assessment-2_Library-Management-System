#include "member_book_order_screen.h"
#include "ui_member_book_order_screen.h"
#include "member_home_screen.h"
#include "member_catalogue_screen.h"

member_book_order_screen::member_book_order_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::member_book_order_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Order Book");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

}

member_book_order_screen::~member_book_order_screen()
{
    delete ui;
}

void member_book_order_screen::on_pushButton_home_clicked()
{
    member_home_screen *ptr = new class member_home_screen;
    ptr->show();
    close();
}


void member_book_order_screen::on_pushButton_catalogue_clicked()
{
    member_catalogue_screen *ptr = new class member_catalogue_screen;
    ptr->show();
    close();
}


void member_book_order_screen::on_pushButton_order_clicked()
{

}

