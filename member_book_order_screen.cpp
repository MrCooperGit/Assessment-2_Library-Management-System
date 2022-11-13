#include "member_book_order_screen.h"
#include "ui_member_book_order_screen.h"
#include "member_home_screen.h"
#include "member_catalogue_screen.h"
#include "classes.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

member_book_order_screen::member_book_order_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::member_book_order_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Order Book");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName());


    //TEMPORARY -- Set book details -- change to details provided from member catalogue
    ui->label_bookTitle->setText("The Hobbit");
    ui->label_author->setText("JRR Tolkien");
    ui->label_id->setText("10001");

    QPixmap pix2("://img/Hobbit.book.jpg");
    int w2 = ui->label->width();
    int h2 = ui->label->height();
    ui->label->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));
}

member_book_order_screen::~member_book_order_screen()
{
    delete ui;
}

void member_book_order_screen::on_pushButton_home_clicked()
{
    member_home_screen *ptr = new class member_home_screen;
    ptr->show();
    close();
}


void member_book_order_screen::on_pushButton_catalogue_clicked()
{
    member_catalogue_screen *ptr = new class member_catalogue_screen;
    ptr->show();
    close();
}


void member_book_order_screen::on_pushButton_order_clicked()
{
    QFile file("bookOrders.csv");

    if(!file.exists())
        {
            qCritical() << "File not found";
            QMessageBox::warning(this, "File Error", "File not found");
            return;
        }

        if(!file.open(QIODevice::WriteOnly))
        {
            qCritical() << file.errorString();
            return;
        }

        QString userID; // TO DO - Set to the id of the current user
        QString bookID; // TO DO - Set to the id of the passed book from member catalogue

        QTextStream stream(&file);

        stream << userID << bookID << "\n";

}

