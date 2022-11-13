#include "edit_member_screen.h"
#include "ui_edit_member_screen.h"


edit_member_screen::edit_member_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_member_screen)
{
    ui->setupUi(this);
}

edit_member_screen::~edit_member_screen()
{
    delete ui;
}



