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

    //Setting logo images
    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap pix2(":/img/homescreen-label.PNG");
    int w2 = ui->label_heading->width();
    int h2 = ui->label_heading->height();
    ui->label_heading->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));

    QPixmap pix3(":/img/menu.label1.png");
    ui->label->setPixmap(pix3.scaled(150,140, Qt::IgnoreAspectRatio));

    QPixmap pix4(":/img/menu.label2.png");
    ui->label_2->setPixmap(pix4.scaled(150,140, Qt::IgnoreAspectRatio));

    QPixmap pix5(":/img/menu.label3.png");
    ui->label_3->setPixmap(pix5.scaled(150,140, Qt::IgnoreAspectRatio));

    QPixmap pix6(":/img/menu.label4.png");
    ui->label_4->setPixmap(pix6.scaled(150,140, Qt::IgnoreAspectRatio));
}

admin_home_screen::~admin_home_screen()
{
    delete ui;
}

//Home screen navigation to other screens


void admin_home_screen::on_pushButton_addNewBook_clicked()
{
    add_new_book_screen *ptr = new class add_new_book_screen;
    ptr->show();
    close();
}


void admin_home_screen::on_pushButton_addNewBookImg_clicked()
{
    add_new_book_screen *ptr = new class add_new_book_screen;
    ptr->show();
    close();
}


void admin_home_screen::on_pushButton_modifCatalogueImg_clicked()
{
    admin_catalogue_screen *ptr = new class admin_catalogue_screen;
    ptr->show();
    close();
}


void admin_home_screen::on_pushButton_modifyCatalogue_clicked()
{
    admin_catalogue_screen *ptr = new class admin_catalogue_screen;
    ptr->show();
    close();
}


void admin_home_screen::on_pushButton_addNewMemberImg_clicked()
{
    add_new_member_screen *ptr = new class add_new_member_screen;
    ptr->show();
    close();
}


void admin_home_screen::on_pushButton_addNewMember_clicked()
{
    add_new_member_screen *ptr = new class add_new_member_screen;
    ptr->show();
    close();
}


void admin_home_screen::on_pushButton_modifyMemberImg_clicked()
{
    member_list_screen *ptr = new class member_list_screen;
    ptr->show();
    close();
}


void admin_home_screen::on_pushButton_modifyMember_clicked()
{
    member_list_screen *ptr = new class member_list_screen;
    ptr->show();
    close();
}

