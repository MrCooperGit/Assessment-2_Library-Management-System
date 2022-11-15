#include "add_new_member_screen.h"
#include "ui_add_new_member_screen.h"
#include "admin_home_screen.h"
#include "edit_member_screen.h"
#include "classes.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QLabel>
#include <QDir>

add_new_member_screen::add_new_member_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_new_member_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Add New Member");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap pix2(":/img/addMember.label.png");
    int w2 = ui->label_heading->width();
    int h2 = ui->label_heading->height();
    ui->label_heading->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName);

    //construct serial number label with integer
    ui->label_idNumber->setText(QString::number(User::getUserId()));
    User::iD = 0;

}

add_new_member_screen::~add_new_member_screen()
{
    delete ui;
}

void add_new_member_screen::on_pushButton_home_clicked()
{
    admin_home_screen *ptr = new class admin_home_screen;
    ptr->show();
    close();
}


void add_new_member_screen::on_pushButton_members_clicked()
{
    edit_member_screen *ptr = new edit_member_screen;
    ptr->show();
    close();
}


void add_new_member_screen::on_pushButton_submit_clicked()
{
//    Member newMember;
//    newMember.setName(ui->lineEdit_firstName->displayText(), ui->lineEdit_lastName->displayText());
//    newMember.setPassword(ui->lineEdit_password->displayText());
//    newMember.setEmail(ui->lineEdit_email->displayText());

    QString firstname, lastName, email, password;
    firstname = ui->lineEdit_firstName->text();
    lastName =ui->lineEdit_lastName->text();
    email = ui->lineEdit_email->text();
    password = ui->lineEdit_password->text();

    while(!ui->lineEdit_firstName->displayText().isEmpty() && !ui->lineEdit_lastName->displayText().isEmpty() && !ui->lineEdit_email->displayText().isEmpty() && !ui->lineEdit_password->displayText().isEmpty())
    {
        QDir current;
        QString currentPath = current.currentPath(); //create string of current directory
        QDir dir(currentPath); //QDir variable becomes current directory
        QFile file(dir.filePath("users.csv")); //file is now specific to the user's directory

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

        int userId = User::getUserId(); //generate userId

        //Input string variables into the file
//        stream << newMember.getEmail() << "," << userId << "," << newMember.getFirstName() << "," << newMember.getLastName() << "," << "member" << "," << newMember.getPassword() << '\n';
        stream << email << "," << userId << "," << firstname << "," << lastName << "," << "member" << "," << password << '\n';


        file.close();

        QMessageBox::information(this, "Details", "Item added successfully"); //displays message box showing success

        //Clear the fields
        ui->lineEdit_firstName->clear();
        ui->lineEdit_lastName->clear();
        ui->lineEdit_password->clear();
        ui->lineEdit_email->clear();

        //Update the serial number
        User::iD = 0; //must reset iD as it is a global constant variable
        ui->label_idNumber->setText(QString::number(User::getUserId()));
        User::iD = 0; //must reset iD as it is a global constant variable

        return;
    }

    QMessageBox::warning(this, "Warning", "You have not filled in the required fields.\nPlease enter the Book Title and the Author.");
}

