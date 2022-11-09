#include "add_new_member_screen.h"
#include "ui_add_new_member_screen.h"
#include "admin_home_screen.h"
#include "member_list_screen.h"
#include "classes.h"

add_new_member_screen::add_new_member_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_new_member_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Add New Member");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap pix2(":/img/addMember.label.png");
    int w2 = ui->label_heading->width();
    int h2 = ui->label_heading->height();
    ui->label_heading->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName());
}

add_new_member_screen::~add_new_member_screen()
{
    delete ui;
}

void add_new_member_screen::on_pushButton_home_clicked()
{
    admin_home_screen *ptr = new class admin_home_screen;
    ptr->show();
    close();
}


void add_new_member_screen::on_pushButton_members_clicked()
{
    member_list_screen *ptr = new class member_list_screen;
    ptr->show();
    close();
}


void add_new_member_screen::on_pushButton_submit_clicked()
{

}

