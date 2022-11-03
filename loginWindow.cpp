#include "loginWindow.h"
#include "./ui_loginWindow.h"
//#include "file_functions.h"
#include "admin_home_screen.h"
#include "member_home_screen.h"
#include "admin_home_screen.h"
#include "admin_catalogue_screen.h"
#include "member_catalogue_screen.h"
#include "member_list_screen.h"
#include "add_new_book_screen.h"
#include "add_new_member_screen.h"
#include "admin_book_view_screen.h"
#include "your_items_screen.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QPixmap>
#include <QDateTime>
#include <QDebug>


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

void LoginWindow::currentDate(){
    QDate date = QDate::currentDate();
    QString strDate = date.toString("dd/MM/yyyy");
    ui->label_date->setText(strDate);
}

void LoginWindow::on_pushButton_login_clicked()
{
    QString loginEmail = ui->lineEdit_username->text();
    QString loginPassword = ui->lineEdit_password->text();

    QFile file("D:/Yoobee/Integrated Studio 2/Assessment 2/repo/users.csv");

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

    QTextStream stream(&file);
    QString email, password;
    while (!file.atEnd()){
        QString line = file.readLine(); //place line into string to edit line with append
        email.clear();
        password.clear();
        email.append(line.split(',').first()); //separates line into array of strings using ','. Chooses the first string as variable
        password.append(line.split(',').last());
        qInfo() << email << password ;
        if (password.contains('\n')) password.chop(1);   //removes '\n' from password
        qInfo() << loginEmail << email << loginPassword << password; //just to check if email and password are selected properly
        int validateEmail, validatePass;
        validateEmail = loginEmail.compare(email);
        validatePass = loginPassword.compare(password);
        qInfo() << validateEmail << validatePass;
        if(validateEmail==0 && validatePass==0){
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


    QFile file("D:/Yoobee/Integrated Studio 2/Assessment 2/repo/users.csv"); //create variable for the file
    //also note that you cannot open .qrc files in write modes. Read-only.
    if(!file.open(QIODevice::Append)) //open file in append which adds new data to end
    {
        qCritical() << file.errorString(); //displays error if file not opened
    }
    QTextStream stream(&file); //declare variable to store the stream from file
    stream << "\n" << email << "," << firstName << "," << lastName << "," << userType << "," << password;
    //stream pastes the variables into the .csv file with /n for new line and ',' for next cell
    file.close();

    ui->lineEdit_email->clear();
    ui->lineEdit_firstName->clear();
    ui->lineEdit_lastName->clear();
    ui->lineEdit_password2->clear();

    QMessageBox::information(this, "Details", "Registration successful"); //displays message box showing success
}


void LoginWindow::on_pushButton_temp_clicked()
{
    add_new_book_screen *ptr = new add_new_book_screen;
    ptr->show();
    close();
}

