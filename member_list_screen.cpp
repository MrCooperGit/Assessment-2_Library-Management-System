#include "member_list_screen.h"
#include "ui_member_list_screen.h"

member_list_screen::member_list_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::member_list_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Member List");
}

member_list_screen::~member_list_screen()
{
    delete ui;
}
