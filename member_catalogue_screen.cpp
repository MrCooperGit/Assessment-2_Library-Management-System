#include "member_catalogue_screen.h"
#include "ui_member_catalogue_screen.h"
#include "member_home_screen.h"

member_catalogue_screen::member_catalogue_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::member_catalogue_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Member Catalogue");

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Member Catalogue Screen");

    //Setting logo images
    QPixmap footerlogo_pix(":/img/library.label.png");
    ui->label_title->setPixmap(footerlogo_pix);
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(footerlogo_pix.scaled(w,h, Qt::KeepAspectRatio));
}

member_catalogue_screen::~member_catalogue_screen()
{
    delete ui;
}

void member_catalogue_screen::on_pushButton_home_clicked()
{
    member_home_screen *ptr = new class member_home_screen;
    ptr->show();
    close();
}

