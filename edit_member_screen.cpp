#include "edit_member_screen.h"
#include "ui_edit_member_screen.h"
#include "classes.h"

edit_member_screen::edit_member_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_member_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Edit Member");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap pix2(":/img/editMember.label.png");
    int w2 = ui->label_heading->width();
    int h2 = ui->label_heading->height();
    ui->label_heading->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName());

}

edit_member_screen::~edit_member_screen()
{
    delete ui;
}

