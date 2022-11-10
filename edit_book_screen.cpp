#include "edit_book_screen.h"
#include "ui_edit_book_screen.h"

#include <QMessageBox>

edit_book_screen::edit_book_screen(QString id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_book_screen)
{
    ui->setupUi(this);

    QMessageBox::information(this, "Title", id);

    ui->label->setText(id);
}

edit_book_screen::~edit_book_screen()
{
    delete ui;
}
