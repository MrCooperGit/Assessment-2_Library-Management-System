#include "admin_catalogue_screen.h"
#include "ui_admin_catalogue_screen.h"

admin_catalogue_screen::admin_catalogue_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_catalogue_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin Catalogue");
}

admin_catalogue_screen::~admin_catalogue_screen()
{
    delete ui;
}
