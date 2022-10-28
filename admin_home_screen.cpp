#include "admin_home_screen.h"
#include "ui_admin_home_screen.h"
#include <QPixmap>

admin_home_screen::admin_home_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_home_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Admin Home Screen");

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
