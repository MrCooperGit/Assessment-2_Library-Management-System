#include "admin_catalogue_screen.h"
#include "ui_admin_catalogue_screen.h"
#include "admin_home_screen.h"
#include "member_list_screen.h"
#include "add_new_book_screen.h"

admin_catalogue_screen::admin_catalogue_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_catalogue_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin Catalogue");

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Admin Catalogue Screen");

    //Setting logo images
    QPixmap footerlogo_pix(":/img/library.label.png");
    ui->label_title->setPixmap(footerlogo_pix);
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(footerlogo_pix.scaled(w,h, Qt::KeepAspectRatio));

}

admin_catalogue_screen::~admin_catalogue_screen()
{
    delete ui;
}

void admin_catalogue_screen::on_pushButton_home_clicked()
{
    admin_home_screen *ptr = new class admin_home_screen;
    ptr->show();
    close();
}


void admin_catalogue_screen::on_pushButton_modifyMembers_clicked()
{
    member_list_screen *ptr = new class member_list_screen;
    ptr->show();
    close();
}


void admin_catalogue_screen::on_pushButton_addNewBook_clicked()
{
    add_new_book_screen *ptr = new class add_new_book_screen;
    ptr->show();
    close();
}


void admin_catalogue_screen::on_pushButton_search_clicked()
{

}


void admin_catalogue_screen::on_label_username_windowTitleChanged(const QString &title)
{

}



