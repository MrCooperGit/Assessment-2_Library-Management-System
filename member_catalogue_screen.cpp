#include "member_catalogue_screen.h"
#include "ui_member_catalogue_screen.h"

member_catalogue_screen::member_catalogue_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::member_catalogue_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Member Catalogue");
}

member_catalogue_screen::~member_catalogue_screen()
{
    delete ui;
}
