#include "admin_book_view_screen.h"
#include "ui_admin_book_view_screen.h"
#include "admin_home_screen.h"
#include "admin_catalogue_screen.h"
#include "classes.h"

#include <QMessageBox>
#include <QFile>

admin_book_view_screen::admin_book_view_screen(QString bookInfo, QWidget *parent) :
    QWidget(parent),

    ui(new Ui::admin_book_view_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Admin Book View");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName());

    QFile file("Books.csv");

    if(!file.exists())
    {
        qCritical() << "File not found";
        QMessageBox::warning(this, "File Error", "File not found");
        return;
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
        return;
    }


    QString title;
    QString author;
    QString id;

    QString passedID = bookInfo.split(",").first();
    QString img_ref = bookInfo.split(",").last();

    while(!file.atEnd()){

        QString line = file.readLine();

        //Making a string list to seperate each column of the file
        QStringList fileList;
        fileList = line.split(",");

        //Transfer data from file into variables
        id = fileList[0];

        //If the id passed to this window matches an id in the file
        if (passedID == id){

            title = fileList.value(fileList.length()-2);
            author = fileList.value(fileList.length()-1);

            break;
        }

    }

    file.close();

    ui->label_bookTitle->setText(title);
    ui->label_bookAuthor->setText(author);
    ui->label_bookID->setText(passedID);

    QPixmap pix2(img_ref);
    int w2 = ui->label_bookImg->width();
    int h2 = ui->label_bookImg->height();
    ui->label_bookImg->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));

}

admin_book_view_screen::~admin_book_view_screen()
{
    delete ui;
}

void admin_book_view_screen::on_pushButton_home_clicked()
{
    admin_home_screen *ptr = new class admin_home_screen;
    ptr->show();
    close();
}


void admin_book_view_screen::on_pushButton_catalogue_clicked()
{
    admin_catalogue_screen *ptr = new class admin_catalogue_screen;
    ptr->show();
    close();
}


void admin_book_view_screen::on_pushButton_edit_clicked()
{

}

