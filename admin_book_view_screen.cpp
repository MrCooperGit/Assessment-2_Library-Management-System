#include "admin_book_view_screen.h"
#include "ui_admin_book_view_screen.h"
#include "admin_home_screen.h"
#include "admin_catalogue_screen.h"

admin_book_view_screen::admin_book_view_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_book_view_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Admin Book View");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap pix2(":/img/Hobbit.book.jpg");
    int w2 = ui->label_bookImg->width();
    int h2 = ui->label_bookImg->height();
    ui->label_bookImg->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));

}

admin_book_view_screen::~admin_book_view_screen()
{
    delete ui;
}

void admin_book_view_screen::on_pushButton_home_clicked()
{
    admin_home_screen *ptr = new class admin_home_screen;
    ptr->show();
    close();
}


void admin_book_view_screen::on_pushButton_catalogue_clicked()
{
    admin_catalogue_screen *ptr = new class admin_catalogue_screen;
    ptr->show();
    close();
}


void admin_book_view_screen::on_pushButton_edit_clicked()
{

}

