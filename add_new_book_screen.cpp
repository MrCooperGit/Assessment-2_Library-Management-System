#include "add_new_book_screen.h"
#include "ui_add_new_book_screen.h"
#include "admin_home_screen.h"
#include "admin_catalogue_screen.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QLabel>

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
}

add_new_book_screen::~add_new_book_screen()
{
    delete ui;
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
    QString serialNumber = ui->lineEdit_id->displayText();

    QFile file ("books.csv");

    if(!file.exists())  //If file does not exist give error
    {
        qCritical() << "File not found";
        QMessageBox::warning(this, "File Error", "File not found");
        return;
    }

    if(!file.open(QIODevice::WriteOnly | QIODevice::Append))   //If file is not opened give error
    {
        qCritical() << file.errorString();
        return;
    }

    QTextStream stream(&file);

    //Input string variables into the file
    stream << serialNumber << "," << bookTitle << "," << author << "\n";

    file.close();

    ui->label_confirmSubmit->setText("Submitted");
}

