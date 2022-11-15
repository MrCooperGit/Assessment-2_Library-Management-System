#include "edit_member_screen.h"
#include "add_new_member_screen.h"
#include "ui_edit_member_screen.h"
#include "classes.h"
#include "admin_home_screen.h"
#include "admin_catalogue_screen.h"
#include "add_new_book_screen.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDir>
#include <QSqlQueryModel>


edit_member_screen::edit_member_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_member_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Edit Member");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap pix2(":/img/editMember.label.png");
    int w2 = ui->label_heading->width();
    int h2 = ui->label_heading->height();
    ui->label_heading->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName);

    //Connect to/Create database and set Table if required
    createDb("/users.db");
    if(!mydb.open()){
         ui->label_status->setText("Failed to connect to database");
    }else
         ui->label_status->setText("Database connected...");
    QSqlQuery qry;
    qry.exec("CREATE TABLE users (email string, idNumber string,"
             "firstName string, lastName string, userType string,"
             "password string)");

    qry.exec("DELETE FROM users"); //clear database before copying .csv file

    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("users.csv")); //file is now specific to the user's directory

    if (!file.open(QIODevice::ReadOnly)) {
           qDebug() << file.errorString();
       }

    QString email, password, firstName, lastName, userType, idNumber;
    while (!file.atEnd()) {
        QString line = file.readLine();
         //place line into string for members only

        //empty the variables before each loop
        email.clear();
        password.clear();
        firstName.clear();
        lastName.clear();
        userType.clear();
        idNumber.clear();

        QStringList list = line.split(","); //split string into string array using "," as break
        //assign variables by index of the string array
        email = list[0];
        password = list[5];
        firstName = list[2];
        lastName = list[3];
        userType = list[4];
        idNumber = list[1];

        //removes '\r\n' from password
        if (password.contains("\r\n")) password.chop(2);
        qDebug() << email << idNumber << firstName << lastName << userType << password ;

        //if statement to include only 'members'
        if (userType == "member"){
            qry.prepare("INSERT INTO users(email, idNumber,"
                        "firstName, lastName, userType,"
                        "password) VALUES('"+email+"', '"+idNumber+"', '"+firstName+"', '"+lastName+"',"
                        "'"+userType+"', '"+password+"')");

            if(!qry.exec()){
                qDebug() << qry.lastError().text();
            }
        }
    }
    connClose();


    //[0] populate table with member data
    QSqlQueryModel * model = new QSqlQueryModel();
    connOpen();
    QSqlQuery * query = new QSqlQuery(mydb);

    query->prepare("SELECT email,idNumber,firstName,lastName FROM users"); //if you don't want to display all
    //then change '*' to column names separated by comma's
    query->exec();
    model->setQuery(*query);
    ui->tableView->setModel(model);

    connClose();
    qDebug() << "Row count: " << (model->rowCount());
    //[0]

}

edit_member_screen::~edit_member_screen()
{
    delete ui;
}



void edit_member_screen::on_pushButton_save_clicked()
{
    QString email, firstName, lastName, iD;
    email = ui->lineEdit_email->text();
    firstName = ui->lineEdit_firstName->text();
    lastName = ui->lineEdit_lastName->text();
    iD = ui->label_idNumber->text();

    connOpen();

    QSqlQuery qry;
    qry.prepare("UPDATE users SET email='"+email+"', firstName='"+firstName+"', lastName='"+lastName+"' WHERE idNumber='"+iD+"' ");

    if(qry.exec()){
        QMessageBox::information(this, tr("Edit"), tr("Data updated successfully"));

        //Update table display with updated database
        QSqlQueryModel * model = new QSqlQueryModel();
        QSqlQuery * query = new QSqlQuery(mydb);
        query->prepare("SELECT email,idNumber,firstName,lastName FROM users"); //if you don't want to display all
        //then change '*' to column names separated by comma's
        query->exec();
        model->setQuery(*query);
        ui->tableView->setModel(model);

        ui->lineEdit_email->clear();
        ui->lineEdit_firstName->clear();
        ui->lineEdit_lastName->clear();

        connClose();
    }else{
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
        connClose();
    }
}


void edit_member_screen::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    connOpen();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE "
                "idNumber='"+val+"' OR email='"+val+"' OR firstName='"+val+"' OR "
                "lastName='"+val+"' ");

    if(qry.exec()){
        while(qry.next()){
            ui->label_email->setText(qry.value(0).toString());
            ui->label_idNumber->setText(qry.value(1).toString());
            ui->label_idNumber2->setText(qry.value(1).toString());
            ui->label_firstName->setText(qry.value(2).toString());
            ui->label_lastName->setText(qry.value(3).toString());
        }
        connClose();
    }else{
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
        connClose();
    }
}


void edit_member_screen::on_pushButton_home_clicked()
{
    admin_home_screen *ptr = new class admin_home_screen;
    ptr->show();
    close();
}


void edit_member_screen::on_pushButton_catalogue_clicked()
{
    admin_catalogue_screen *ptr = new class admin_catalogue_screen;
    ptr->show();
    close();
}


void edit_member_screen::on_pushButton_catalogue_3_clicked()
{
    add_new_member_screen *ptr = new add_new_member_screen;
    ptr->show();
    close();
}

