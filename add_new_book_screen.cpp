#include "add_new_book_screen.h"
#include "qtimer.h"
#include "ui_add_new_book_screen.h"
#include "admin_home_screen.h"
#include "admin_catalogue_screen.h"
#include "classes.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QLabel>
#include <QDate>
#include <QDir>

add_new_book_screen::add_new_book_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_new_book_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Add New Book");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap pix2(":/img/addBook.label.png");
    int w2 = ui->label_heading->width();
    int h2 = ui->label_heading->height();
    ui->label_heading->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));

    //construct timer to read date when screen opens
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(currentDate()));
    timer->start(1000); //time in ms

    //construct username in top right corner
    ui->label_username->setText(User::userName());

    //construct serial number label with integer
    ui->label_snDisplay->setText(QString::number(Item::getItemId()));
}

add_new_book_screen::~add_new_book_screen()
{
    delete ui;
}

void add_new_book_screen::currentDate(){
    QDate date = QDate::currentDate();
    QString strDate = date.toString("dd/MM/yyyy");
    ui->label_date->setText(strDate);
}

void add_new_book_screen::on_pushButton_home_clicked()
{
    admin_home_screen *ptr = new class admin_home_screen;
    ptr->show();
    close();
}


void add_new_book_screen::on_pushButton_modifyCatalogue_clicked()
{
    admin_catalogue_screen *ptr = new class admin_catalogue_screen;
    ptr->show();
    close();
}


//When user submits book details
void add_new_book_screen::on_pushButton_clicked()
{
    QString bookTitle = ui->lineEdit_title->displayText();
    QString author = ui->lineEdit_author->displayText();

    while(!ui->lineEdit_title->displayText().isEmpty() && !ui->lineEdit_author->displayText().isEmpty())
    {
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

        if(!file.open(QIODevice::WriteOnly | QIODevice::Append))   //If file is not opened give error
        {
            qCritical() << file.errorString();
            return;
        }

        QTextStream stream(&file); //declare variable to store the stream from file

        int itemId = Item::getItemId(); //generate itemId

        //Input string variables into the file
        stream << "\n" << itemId << "," << bookTitle << "," << author;

        file.close();

        QMessageBox::information(this, "Details", "Item added successfully"); //displays message box showing success

        //Clear the fields
        ui->lineEdit_title->clear();
        ui->lineEdit_author->clear();

        //Update the serial number
        Item::iD = 0; //must reset iD as it is a global constant variable
        ui->label_snDisplay->setText(QString::number(Item::getItemId()));
        Item::iD = 0; //must reset iD as it is a global constant variable

        return;
    }

    QMessageBox::warning(this, "Warning", "You have not filled in the required fields.\nPlease enter the Book Title and the Author.");
}

