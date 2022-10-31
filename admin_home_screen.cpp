#include "admin_home_screen.h"
#include "ui_admin_home_screen.h"

Admin_Home_Screen::Admin_Home_Screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin_Home_Screen)
{
    ui->setupUi(this);
}

Admin_Home_Screen::~Admin_Home_Screen()
{
    delete ui;
}
