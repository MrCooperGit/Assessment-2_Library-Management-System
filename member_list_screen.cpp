#include "member_list_screen.h"
#include "ui_member_list_screen.h"
#include "admin_catalogue_screen.h"
#include "add_new_member_screen.h"
#include "admin_home_screen.h"

member_list_screen::member_list_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::member_list_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Member List");

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Member List Screen");

    //Setting logo images
    QPixmap footerlogo_pix(":/img/library.label.png");
    ui->label_title->setPixmap(footerlogo_pix);
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(footerlogo_pix.scaled(w,h, Qt::KeepAspectRatio));
}

member_list_screen::~member_list_screen()
{
    delete ui;
}

void member_list_screen::on_pushButton_home_clicked()
{
    admin_home_screen *ptr = new class admin_home_screen;
    ptr->show();
    close();
}


void member_list_screen::on_pushButton_modifyCatalogue_clicked()
{
    admin_catalogue_screen *ptr = new class admin_catalogue_screen;
    ptr->show();
    close();
}


void member_list_screen::on_pushButton_addNewMember_clicked()
{
    add_new_member_screen *ptr = new class add_new_member_screen;
    ptr->show();
    close();
}

