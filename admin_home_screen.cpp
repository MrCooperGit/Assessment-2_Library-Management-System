#include "admin_home_screen.h"
#include "ui_admin_home_screen.h"
#include <QPixmap>
#include "add_new_book_screen.h"
#include "admin_catalogue_screen.h"
#include "add_new_member_screen.h"
#include "member_list_screen.h"

admin_home_screen::admin_home_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_home_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Admin Home");

    //Setting button images
    QIcon button1_icon("://img/menu.label1.png");
    ui->button_img_1->setIcon(button1_icon);

    QIcon button2_icon("://img/menu.label2.png");
    ui->button_img_2->setIcon(button2_icon);

    QIcon button3_icon("://img/menu.label3.png");
    ui->button_img_3->setIcon(button3_icon);

    QIcon button4_icon("://img/menu.label4.png");
    ui->button_img_4->setIcon(button4_icon);

    //Setting logo images
    QPixmap headerlogo_pix(":/img/homescreen-label.PNG");
    ui->label_img->setPixmap(headerlogo_pix);

    QPixmap footerlogo_pix(":/img/library.label.png");
    ui->label_img_2->setPixmap(footerlogo_pix);
}

admin_home_screen::~admin_home_screen()
{
    delete ui;
}

//Home screen navigation to other screens

//Navigate to add new book screen
void admin_home_screen::on_pushButton_clicked()
{
    add_new_book_screen *_add_new_book_screen = new add_new_book_screen;
    _add_new_book_screen->show();
    close();
}
void admin_home_screen::on_button_img_1_clicked()
{
    add_new_book_screen *_add_new_book_screen = new add_new_book_screen;
    _add_new_book_screen->show();
    close();
}


//Navigate to admin catalogue screen / modify catalogue screen
void admin_home_screen::on_pushButton_2_clicked()
{
    admin_catalogue_screen *_admin_catalogue_screen = new admin_catalogue_screen;
    _admin_catalogue_screen->show();
    close();

}
void admin_home_screen::on_button_img_2_clicked()
{
    admin_catalogue_screen *_admin_catalogue_screen = new admin_catalogue_screen;
    _admin_catalogue_screen->show();
    close();
}


//Navigate to add new member screen
void admin_home_screen::on_pushButton_3_clicked()
{
    add_new_member_screen *_add_new_member_screen = new add_new_member_screen;
    _add_new_member_screen->show();
    close();
}
void admin_home_screen::on_button_img_3_clicked()
{
    add_new_member_screen *_add_new_member_screen = new add_new_member_screen;
    _add_new_member_screen->show();
    close();
}


//Navigate to member list screen / modify member screen
void admin_home_screen::on_pushButton_4_clicked()
{
    member_list_screen *_member_list_screen = new member_list_screen;
    _member_list_screen->show();
    close();
}
void admin_home_screen::on_button_img_4_clicked()
{
    member_list_screen *_member_list_screen = new member_list_screen;
    _member_list_screen->show();
    close();
}

