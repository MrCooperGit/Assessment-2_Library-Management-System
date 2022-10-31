#include "loginWindow.h"
#include "./ui_loginWindow.h"
#include <QMessageBox>
#include <QPixmap>
#include "member_home_screen.h"
#include "admin_home_screen.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/img/library.label.png");
    int w = ui->label_img->width();
    int h = ui->label_img->height();
    ui->label_img->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_pushButton_clicked()
{

}



void LoginWindow::on_pushButton_login_clicked()
{
    //Open home screen (member/admin) for testing (member home screen header file is included)
    member_home_screen *_member_home_screen = new member_home_screen;
    _member_home_screen->show();
    close();
    //admin_home_screen *_admin_home_screen = new admin_home_screen;
    //_admin_home_screen->show();
    //close();
}

