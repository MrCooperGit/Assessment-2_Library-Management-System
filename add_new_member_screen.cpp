#include "add_new_member_screen.h"
#include "ui_add_new_member_screen.h"

add_new_member_screen::add_new_member_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_new_member_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Add New Member");
}

add_new_member_screen::~add_new_member_screen()
{
    delete ui;
}
