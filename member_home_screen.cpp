#include "member_home_screen.h"
#include "ui_member_home_screen.h"
#include <QPixmap>
#include "member_catalogue_screen.h"
#include "your_items_screen.h"

member_home_screen::member_home_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::member_home_screen)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Member Home");

    //Setting button images
    QIcon button1_icon("://img/menu.label1.png");
    ui->button_img_1->setIcon(button1_icon);

    QIcon button2_icon("://img/menu.label2.png");
    ui->button_img_2->setIcon(button2_icon);

    //Setting logo images
    QPixmap headerlogo_pix("://img/homescreen-label.PNG");
    ui->label_img->setPixmap(headerlogo_pix);

    QPixmap footerlogo_pix("://img/library.label.png");
    ui->label_img_2->setPixmap(footerlogo_pix);
}

member_home_screen::~member_home_screen()
{
    delete ui;
}

//Home screen navigation to other screens

//Navigate to member catalogue screen / view catalogue screen
void member_home_screen::on_pushButton_clicked()
{
    member_catalogue_screen *_member_catalogue_screen = new member_catalogue_screen;
    _member_catalogue_screen->show();
    close();
}
void member_home_screen::on_button_img_1_clicked()
{
    member_catalogue_screen *_member_catalogue_screen = new member_catalogue_screen;
    _member_catalogue_screen->show();
    close();
}

//Navigate to your items screen
void member_home_screen::on_pushButton_2_clicked()
{
    your_items_screen *_your_items_screen = new your_items_screen;
    _your_items_screen->show();
    close();
}
void member_home_screen::on_button_img_2_clicked()
{
    your_items_screen *_your_items_screen = new your_items_screen;
    _your_items_screen->show();
    close();
}

