#include "edit_book_screen.h"
#include "ui_edit_book_screen.h"
#include "admin_catalogue_screen.h"
#include "admin_home_screen.h"
#include "classes.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>

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
    ui->label_username->setText(User::userName());

    //Setting logo images
    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap pix2("://img/editBook.label.png");
    int w2 = ui->label_heading->width();
    int h2 = ui->label_heading->height();
    ui->label_heading->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));


    QFile file("books.csv");

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

    file.close();


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
        QFile file("books.csv");

        if(!file.exists())
        {
            qCritical() << "File not found";
            QMessageBox::warning(this, "File Error", "File not found - og 1");
            return;
        }

        if(!file.open(QIODevice::ReadOnly))
        {
            qCritical() << file.errorString();
            return;
        }


        //Open temp file
        QFile tempFile("TempBooks.csv");
        if(!tempFile.exists())
        {
            qCritical() << "File not found";
            QMessageBox::warning(this, "File Error", "File not found - temp 1");
            return;
        }

        if(!tempFile.open(QIODevice::WriteOnly))
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

                QMessageBox::information(this, "Title", "Target book found");
            }
            else {

                tempStream << fileID << "," << book.getTitle() << "," << book.getAuthor();

            }
        }

        tempFile.close();
        file.close();


        //Overwrite main file with temp file

        if(!file.exists())
        {
            qCritical() << "File not found";
            QMessageBox::warning(this, "File Error", "File not found -og 2");
            return;
        }

        if(!file.open(QIODevice::WriteOnly))
        {
            qCritical() << file.errorString();
            return;
        }

        QTextStream stream(&file);

        if(!tempFile.exists())
        {
            qCritical() << "File not found";
            QMessageBox::warning(this, "File Error", "File not found -temp 2");
            return;
        }

        if(!tempFile.open(QIODevice::ReadOnly))
        {
            qCritical() << tempFile.errorString();
            return;
        }

        while(!tempFile.atEnd()){

            QString line = tempFile.readLine();

            stream << line;

            QMessageBox::information(this, "Title", "Info entered into orig file");

        }

        file.close();
        tempFile.close();

    }
}

