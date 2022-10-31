#include "loginWindow.h"
#include "./ui_loginWindow.h"
#include "file_functions.h"
#include "admin_home_screen.h"
//#include "library.h"
#include <QMessageBox>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QStringList>


LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/img/library.label.png");
    int w = ui->label_img->width();
    int h = ui->label_img->height();
    ui->label_img->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_pushButton_login_clicked()
{
    QString loginEmail = ui->lineEdit_username->text();
    QString loginPassword = ui->lineEdit_password->text();

    //read_file(":/csv/users.csv"); //function call not working
    QFile file("C:/Users/Shaun Cooper/Documents/Qt Projects/Assessment-2_Library-Management-System/users.csv");
    if(!file.exists())
    {
        qCritical() << "File not found";
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
    }

    //QTextStream stream(&file);
    QString email, password;
    while (!file.atEnd()){
        QString line = file.readLine(); //place line into string to edit line with append
        email.append(line.split(',').first()); //separates line into array of strings using ','. Chooses the first string as variable
        password.append(line.split(',').last());
        qInfo() << email << password ;
       // email.remove(0,2); //need to remove '\n' from beginning of string. Starting at index 0 for 2 occassions
        //password.remove(0,2);
        qInfo() << loginEmail << email << loginPassword << password; //just to check if email and password are selected properly
        int validateEmail, validatePass;
        validateEmail = loginEmail.compare(email);
        validatePass = loginPassword.compare(password);
        qInfo() << validateEmail << validatePass;
//        if(loginEmail.contains(email) && loginPassword.contains(password)){
//            file.close();
//            Admin_Home_Screen *admin_home_screen = new Admin_Home_Screen;
//            admin_home_screen->show();
//            close();
//            return;
//        }
    }

    file.close();
    ui->lineEdit_password->clear();
//    Admin_Home_Screen *admin_home_screen = new Admin_Home_Screen;
//    admin_home_screen->show();
//    close();

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


    QFile file("C:/Users/Shaun Cooper/Documents/Qt Projects/Assessment-2_Library-Management-System/users.csv"); //create variable for the file
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

