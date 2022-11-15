#include "admin_home_screen.h"
#include "ui_admin_home_screen.h"
#include "add_new_book_screen.h"
#include "admin_catalogue_screen.h"
#include "add_new_member_screen.h"
#include "edit_member_screen.h"
#include "classes.h"

#include <QPixmap>


admin_home_screen::admin_home_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_home_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Admin Home");

//    QPixmap *image = new QPixmap(":/img/menu.label1.png");
//    QIcon icon(*image);
//    QSize iconSize(image->width(), image->height());
    ui->pushButton->setIcon(QIcon(":/img/menu.label1.png"));
    ui->pushButton->setIconSize(QSize(180,140));

    //Setting logo images
    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap pix2(":/img/homescreen-label.PNG");
    int w2 = ui->label_heading->width();
    int h2 = ui->label_heading->height();
    ui->label_heading->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));

    //Setting button icons
    ui->pushButton->setIcon(QIcon(":/img/menu.label1.png"));
    ui->pushButton->setIconSize(QSize(190,130));

    ui->pushButton_2->setIcon(QIcon(":/img/menu.label2.png"));
    ui->pushButton_2->setIconSize(QSize(190,130));

    ui->pushButton_3->setIcon(QIcon(":/img/menu.label3.png"));
    ui->pushButton_3->setIconSize(QSize(190,130));

    ui->pushButton_4->setIcon(QIcon(":/img/menu.label4.png"));
    ui->pushButton_4->setIconSize(QSize(190,130));

    ui->label_username->setText(User::userName);
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


void admin_home_screen::on_pushButton_clicked()
{
    add_new_book_screen *ptr = new class add_new_book_screen;
    ptr->show();
    close();
}


void admin_home_screen::on_pushButton_modifyCatalogue_clicked()
{
    admin_catalogue_screen *ptr = new class admin_catalogue_screen;
    ptr->show();
    close();
}


void admin_home_screen::on_pushButton_2_clicked()
{
    admin_catalogue_screen *ptr = new class admin_catalogue_screen;
    ptr->show();
    close();
}


void admin_home_screen::on_pushButton_3_clicked()
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


void admin_home_screen::on_pushButton_4_clicked()
{
    edit_member_screen *ptr = new edit_member_screen;
    ptr->show();
    close();
}


void admin_home_screen::on_pushButton_modifyMember_clicked()
{
    edit_member_screen *ptr = new class edit_member_screen;
    ptr->show();
    close();
}

