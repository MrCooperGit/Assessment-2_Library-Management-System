#include "loginWindow.h"
#include "./ui_loginWindow.h"
#include "classes.h"
#include "admin_home_screen.h"
#include "edit_member_screen.h"
#include "edit_book_screen.h"
#include "member_home_screen.h"
#include "admin_home_screen.h"
#include "admin_catalogue_screen.h"
#include "member_catalogue_screen.h"
#include "member_list_screen.h"
#include "add_new_book_screen.h"
#include "add_new_member_screen.h"
#include "admin_book_view_screen.h"
#include "your_items_screen.h"
#include "member_book_order_screen.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QPixmap>
#include <QDateTime>
#include <QDebug>
#include <QDir>



LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Login");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_img->width();
    int h = ui->label_img->height();
    ui->label_img->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    //construct timer to read date when screen opens
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(currentDate()));
    timer->start(1000); //time in ms

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

//Function to display the current date
void LoginWindow::currentDate(){
    QDate date = QDate::currentDate();
    QString strDate = date.toString("dd/MM/yyyy");
    ui->label_date->setText(strDate);
}

void LoginWindow::on_pushButton_login_clicked()
{
    QString loginEmail = ui->lineEdit_username->text();
    QString loginPassword = ui->lineEdit_password->text();

    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("users.csv")); //file is now specific to the user's directory

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

    //QTextStream stream(&file);
    QString email, password, firstName, lastName;
    while (!file.atEnd()){
        QString line = file.readLine(); //place line into string

        //empty the variables before each loop
        email.clear();
        password.clear();
        firstName.clear();
        lastName.clear();


        QStringList list = line.split(","); //split string into string array using "," as break
        //assign variables by index of the string array
        email = list[0];
        password = list[5];
        firstName.replace(0,12, list[2]);
        lastName.replace(0,12, list[3]);

        if (password.contains("\r\n")) password.chop(2);   //removes '\r\n' from password

        //using integers to validate login details
        //the compare() function returns 0 if strings are the same
        int validateEmail, validatePass;
        validateEmail = loginEmail.compare(email);
        validatePass = loginPassword.compare(password);

        if(validateEmail==0 && validatePass==0){

            //store first and last name in object of User class for use in other screens
            User::setName(firstName, lastName);
            qInfo() << User::userName();
            file.close();
            if(line.contains("admin")){
                admin_home_screen *admin_home_screen = new class admin_home_screen;
                admin_home_screen->show();
                close();
                return;
            }else {
                member_home_screen *member_home_screen = new class member_home_screen;
                member_home_screen->show();
                close();
                return;
            }
        }
    }

    file.close();
    ui->lineEdit_password->clear();

    QMessageBox::warning(this, "Warning", "Sorry, your email/username or password is incorrect! Try again.");
}


void LoginWindow::on_pushButton_register_clicked()
{
    //loop requires that all fields have data
    while(!ui->lineEdit_email->text().isEmpty() &&
          !ui->lineEdit_firstName->text().isEmpty() &&
          !ui->lineEdit_lastName->text().isEmpty() &&
          !ui->lineEdit_password2->text().isEmpty() &&
          (ui->radioButton_admin->isChecked() || ui->radioButton_member->isChecked()))
    {
    QString email = ui->lineEdit_email->text(); //String variables which store the text in the lineEdit boxes
    QString firstName = ui->lineEdit_firstName->text();
    QString lastName = ui->lineEdit_lastName->text();
    QString password = ui->lineEdit_password2->text();
    QString userType; //Below radio buttons will determine the string for this variable

    if(ui->radioButton_admin->isChecked()){
        userType.replace(0,99,"admin");
    }
    if(ui->radioButton_member->isChecked()){
        userType.replace(0,99,"member");
    }

    //First find the current directory
    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("users.csv")); //file is now specific to the user's directory

    if(!file.exists())  //If file does not exist, will create file in current directory
    {
        if (!file.open(QIODevice::ReadWrite))
        {
        qWarning("Cannot create the file");
        return;
        }
        file.close();
    }

    if(!file.open(QIODevice::Append)) //open file in append which adds new data to end
    {
        qCritical() << file.errorString(); //displays error if file not opened
        return;
    }

    QTextStream stream(&file); //declare variable to store the stream from file

    int userId = User::getUserId(); //generate userId

    //stream pastes the variables into the .csv file with /n for new line and ',' for next cell
    stream << "\n" << email << "," << userId << "," << firstName << "," << lastName << "," << userType << "," << password;
    file.close();

    ui->lineEdit_username->setText(ui->lineEdit_email->text());
    ui->lineEdit_email->clear();
    ui->lineEdit_firstName->clear();
    ui->lineEdit_lastName->clear();
    ui->lineEdit_password2->clear();

    QMessageBox::information(this, "Details", "Registration successful"); //displays message box showing success

    User::iD = 0; //Reset userId calculator

    return;
    }

    QMessageBox::critical(this, "Critical", "Please ensure all fields are entered!");
}

void LoginWindow::on_pushButton_temp_clicked()
{
    admin_catalogue_screen *ptr = new admin_catalogue_screen;
    ptr->show();
    close();
}

