#include "edit_book_screen.h"
#include "ui_edit_book_screen.h"
#include "admin_catalogue_screen.h"
#include "admin_home_screen.h"
#include "classes.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>

QString targetID;
QString newTitle;
QString newAuthor;

edit_book_screen::edit_book_screen(QString id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_book_screen)
{
    ui->setupUi(this);

    targetID = id;

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Edit Book");

    //construct username in top right corner
    ui->label_username->setText(User::userName);

    //Setting logo images
    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap pix2("://img/editBook.label.png");
    int w2 = ui->label_heading->width();
    int h2 = ui->label_heading->height();
    ui->label_heading->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));


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

    if(!file.open(QIODevice::ReadOnly))  //If file is not opened give error
    {
        qCritical() << file.errorString();
        return;
    }

    Book targetBook;
    QString fileID;

    while(!file.atEnd()){

        QString line = file.readLine();

        //Making a string list to seperate each column of the file
        QStringList fileList;
        fileList = line.split(",");

        //Transfer data from file into variables
        fileID = fileList[0];

        //If the id passed to this window matches an id in the file
        if (fileID == targetID){

            targetBook.setTitle(fileList[1]);
            targetBook.setAuthor(fileList[2]);

            break;
        }

    }


    ui->lineEdit_cTitle->setText(targetBook.getTitle());
    ui->lineEdit_cAuthor->setText(targetBook.getAuthor());

    ui->lineEdit_cTitle->setReadOnly(true);
    ui->lineEdit_cAuthor->setReadOnly(true);
}

edit_book_screen::~edit_book_screen()
{
    delete ui;
}

void edit_book_screen::on_pushButton_home_clicked()
{
    admin_home_screen *ptr = new admin_home_screen;
    ptr->show();
    close();
}


void edit_book_screen::on_pushButton_members_clicked()
{
    admin_catalogue_screen *ptr = new admin_catalogue_screen;
    ptr->show();
    close();
}



void edit_book_screen::on_pushButton_submit_clicked()
{
    newTitle = ui->lineEdit_newTitle->displayText();
    newAuthor = ui->lineEdit_newAuthor->displayText();

    //Update file with new data

    if (!ui->lineEdit_newTitle->displayText().isEmpty() && !ui->lineEdit_newAuthor->displayText().isEmpty()){ //If the user has entered a new title and author

        //Open original file
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

        if(!file.open(QIODevice::ReadOnly))  //If file is not opened give error
        {
            qCritical() << file.errorString();
            return;
        }


        //Open temp file
        QDir current2;
        QString currentPath2 = current2.currentPath(); //create string of current directory
        QDir dir2(currentPath2); //QDir variable becomes current directory
        QFile tempFile(dir2.filePath("tempBooks.csv")); //file is now specific to the user's directory


        if(!tempFile.exists())  //If file does not exist, will create file in current directory
        {
            if (!tempFile.open(QIODevice::ReadWrite))
                qWarning("Cannot create the file");
            tempFile.close();
        }

        if(!tempFile.open(QIODevice::WriteOnly))  //If file is not opened give error
        {
            qCritical() << tempFile.errorString();
            return;
        }

        QTextStream tempStream(&tempFile);

        //Input lines from main file into temp file
        while(!file.atEnd()){

            Book book;

            QString line = file.readLine();

            QStringList fileList;
            fileList = line.split(",");

            //Transfer data from file into variables
            QString fileID = fileList[0];
            book.setTitle(fileList[1]);
            book.setAuthor(fileList[2]);

            if (fileID == targetID){
                tempStream << targetID << "," << newTitle << "," << newAuthor << "\n";

            }
            else {

                tempStream << fileID << "," << book.getTitle() << "," << book.getAuthor();

            }
        }

        tempFile.close();
        file.close();


        //Overwrite main file with temp file

        if(!file.exists())  //If file does not exist, will create file in current directory
        {
            if (!file.open(QIODevice::ReadWrite))
                qWarning("Cannot create the file");
            file.close();
        }

        if(!file.open(QIODevice::WriteOnly))  //If file is not opened give error
        {
            qCritical() << file.errorString();
            return;
        }

        QTextStream stream(&file);

        if(!tempFile.exists())  //If file does not exist, will create file in current directory
        {
            if (!tempFile.open(QIODevice::ReadWrite))
                qWarning("Cannot create the file");
            tempFile.close();
        }

        if(!tempFile.open(QIODevice::ReadOnly))  //If file is not opened give error
        {
            qCritical() << tempFile.errorString();
            return;
        }

        while(!tempFile.atEnd()){

            QString line = tempFile.readLine();

            stream << line;

        }

        file.close();
        tempFile.close();

        QMessageBox::information(this, "Details", "Book updated successfully");

    } else {

        QMessageBox::information(this, "Details", "Please enter a new title and author before submitting");
    }

    //Remove tempBooks.csv from directory
    QDir current2;
    QString currentPath2 = current2.currentPath(); //create string of current directory
    QDir dir2(currentPath2); //QDir variable becomes current directory
    dir2.remove("tempBooks.csv");

    ui->lineEdit_newTitle->clear();
    ui->lineEdit_newAuthor->clear();
}

