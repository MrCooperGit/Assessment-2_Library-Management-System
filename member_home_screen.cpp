#include "member_home_screen.h"
#include "ui_member_home_screen.h"
#include <QPixmap>
#include "member_catalogue_screen.h"
#include "your_items_screen.h"
#include "classes.h"

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
    ui->button_img_1->setFlat(true);

    QIcon button2_icon("://img/menu.label2.png");
    ui->button_img_2->setIcon(button2_icon);
    ui->button_img_2->setFlat(true);

    //Setting logo images
    QPixmap headerlogo_pix("://img/homescreen-label.PNG");
    int w2 = ui->label_img->width();
    int h2 = ui->label_img->height();
    ui->label_img->setPixmap(headerlogo_pix.scaled(w2,h2, Qt::KeepAspectRatio));


    QPixmap footerlogo_pix("://img/library.label.png");
    int w = ui->label_img_2->width();
    int h = ui->label_img_2->height();
    ui->label_img_2->setPixmap(footerlogo_pix.scaled(w,h, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName);
}

member_home_screen::~member_home_screen()
{
    delete ui;
}

//Home screen navigation to other screens

//Navigate to member catalogue screen / view catalogue screen
void member_home_screen::on_pushButton_viewCatalogue_clicked()
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
void member_home_screen::on_pushButton_yourItems_clicked()
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







