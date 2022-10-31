#include "your_items_screen.h"
#include "ui_your_items_screen.h"

your_items_screen::your_items_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::your_items_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Your Items");
}

your_items_screen::~your_items_screen()
{
    delete ui;
}
