#include "loginWindow.h"
#include "./ui_loginWindow.h"
#include "classes.h"
#include "admin_home_screen.h"
#include "member_home_screen.h"
#include "admin_home_screen.h"

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

    //[0] function to read all orders.csv 'due soon' and 'overdue'
    //and write them in separate files respectively
    //create/link file including validation checks
    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("orders.csv")); //file is now specific to the user's directory

    if(!file.exists()) //create file if it doesn't exist
    {
        if (!file.open(QIODevice::ReadWrite))
        {
        qWarning("Cannot create the file");
        }
        file.close();
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
    }

    //[1] Delete previous file versions to start fresh
    dir.remove("overdue.csv");
    dir.remove("dueSoon.csv");
    //[1]

    //[2] Create files in build path
    QFile file2(dir.filePath("dueSoon.csv")); //file is now specific to the user's directory
    if(!file2.exists()) //create file if it doesn't exist
    {
        if (!file2.open(QIODevice::ReadWrite))
        {
        qWarning("Cannot create the file");
        }
        file2.close();
    }
    QFile file3(dir.filePath("overdue.csv")); //file is now specific to the user's directory
    if(!file3.exists()) //create file if it doesn't exist
    {
        if (!file3.open(QIODevice::ReadWrite))
        {
        qWarning("Cannot create the file");
        }
        file3.close();
    }
    //[2]


    while (!file.atEnd()){

        QString line = file.readLine(); //store each line from file
        QString date, fileUserId, fileBookId;

        Book newBook; //declare book object

        //Making a string list to seperate each column of the file
        QStringList fileList;
        fileList.clear();
        fileList = line.split(",");

        //Transfer data from file into variables
        fileBookId = fileList[0];
        newBook.setTitle(fileList[1]);
        fileUserId = fileList[2];
        date = fileList[3];
        if (date.contains("\n")) date.chop(1); //remove \n from last word in line
        if (date.contains("\r")) date.chop(1); //remove \r from last word in line

        //Compare current date with due dates from file
        QDate currentDate = QDate::currentDate(), fileDate;
        fileDate = QDate::fromString(date, "dd/MM/yyyy");
        int num = currentDate.daysTo(fileDate);

        //If book is due within 3 days, write in dueSoon.csv
        if(num >= 0 && num <= 3){
            if(!file2.open(QIODevice::Append))
            {
                qCritical() << file2.errorString();
            }
            QTextStream stream(&file2); //declare variable to store the stream from file

            //stream pastes the variables into the .csv file with /n for new line and ',' for next cell
            stream << fileBookId << "," << newBook.getTitle() << "," << fileUserId << "," << date << "\n";
            file2.close();
        }

        //If book is overdue, write in overdue.csv
        if (num < 0){
            if(!file3.open(QIODevice::Append))
            {
                qCritical() << file3.errorString();
            }
            QTextStream stream(&file3); //declare variable to store the stream from file

            //stream pastes the variables into the .csv file with /n for new line and ',' for next cell
            stream << fileBookId << "," << newBook.getTitle() << "," << fileUserId << "," << date << "\n";
            file3.close();
        }
    }
    //[0]
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
    QString loginEmail = ui->lineEdit_username->text().toLower();
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

    QString email, password, firstName, lastName, userId;
    while (!file.atEnd()){
        QString line = file.readLine(); //place line into string
        //empty the variables before each loop
        email.clear();
        password.clear();
        firstName.clear();
        lastName.clear();
        userId.clear();


        QStringList list = line.split(","); //split string into string array using "," as break
        //assign variables by index of the string array
        email = list[0].toLower();
        userId = list[1];
        password = list[5];
        firstName = list[2];
        lastName = list[3];

        if (password.contains("\n")) password.chop(1);   //removes '\n' from password
        if (password.contains("\r")) password.chop(1);   //removes '\r' from password

        //using integers to validate login details
        //the compare() function returns 0 if strings are the same
        int validateEmail, validatePass;
        validateEmail = loginEmail.compare(email);
        validatePass = loginPassword.compare(password);

        if(validateEmail==0 && validatePass==0){

            //store first and last name in object of User class for use in other screens
            User::setUserName(firstName, lastName);
            User::iD = userId.toInt(); //set global userId for use in your_items_screen
            qInfo() << User::userName;
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
    stream << email << "," << userId << "," << firstName << "," << lastName << "," << userType << "," << password << "\n";
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


void LoginWindow::on_radioButton_admin_clicked()
{
    QMessageBox::information(this,"Information","The register function is displayed here with a radio button to choose\n"
                                                "'member' or 'admin' for testing/marking purposes only.\n"
                                                "This radio button would be removed for actual implementation.");
}

