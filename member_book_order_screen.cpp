#include "member_book_order_screen.h"
#include "ui_member_book_order_screen.h"
#include "member_home_screen.h"
#include "member_catalogue_screen.h"
#include "classes.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include <QDir>
#include <QDebug>

QString _passedID;
Book targetBook;

member_book_order_screen::member_book_order_screen(QString memberInfo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::member_book_order_screen)
{
    ui->setupUi(this);

    qDebug() << QDir::currentPath();

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Order Book");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName);

    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("books.csv")); //file is now specific to the user's directory

    if(!file.exists())  //If file does not exist, will create file in current directory
    {
        if (!file.open(QIODevice::ReadWrite))
            qWarning("Cannot create the file");
        file.close();
    }

    if(!file.open(QIODevice::ReadOnly))   //If file is not opened give error
    {
        qCritical() << file.errorString();
        return;
    }

    QString id;

    _passedID = memberInfo.split(",").first();
    targetBook.setCoverImgRef(memberInfo.split(",").last());



    while(!file.atEnd()){

        QString line = file.readLine();

        //Making a string list to seperate each column of the file
        QStringList fileList;
        fileList = line.split(",");

        //Transfer data from file into variables
        id = fileList[0];

        //If the id passed to this window matches an id in the file
        if (_passedID == id){

            targetBook.setTitle(fileList[1]);
            targetBook.setAuthor(fileList[2]);

            break;
        }

    }

    file.close();


    ui->label_bookTitle->setText(targetBook.getTitle());
    ui->label_author->setText(targetBook.getAuthor());
    ui->label_id->setText(id);

    QPixmap pix2(targetBook.getCoverImgRef());
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
    bool orderPlaced = false;

    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("orders.csv")); //file is now specific to the user's directory

    //Check if book has already been ordered

    if(!file.exists())  //If file does not exist, will create file in current directory
    {
        if (!file.open(QIODevice::ReadWrite))
            qWarning("Cannot create the file");
        file.close();
    }

    if(!file.open(QIODevice::ReadOnly))  //If file is not opened give error
    {
        qCritical() << file.errorString();
        return;
    }


    while(!file.atEnd()){

        QString line = file.readLine();

        QStringList list = line.split(",");

        QString targetBookID = list[0];

        if (targetBookID == _passedID){
            orderPlaced = true;
            break;

        } else {
            orderPlaced = false;
        }
    }

    file.close();


    if(!orderPlaced){

        if(!file.exists())  //If file does not exist, will create file in current directory
        {
            if (!file.open(QIODevice::ReadWrite))
                qWarning("Cannot create the file");
            file.close();
        }

        if(!file.open(QIODevice::WriteOnly | QIODevice::Append))   //If file is not opened give error
        {
            qCritical() << file.errorString();
            return;
        }

            QDate dueDate;
            dueDate = dueDate.currentDate().addDays(14);
            QString strDueDate = dueDate.toString("dd/MM/yyyy");

            QTextStream stream(&file);

            stream << _passedID << "," << targetBook.getTitle() << "," << User::iD << "," << strDueDate << "\n";

            file.close();
            QMessageBox::information(this, "Details", "Order placed successfully");

    } else if(orderPlaced){

        QMessageBox::information(this, "Details", "This book has already been ordered");
    }



}

