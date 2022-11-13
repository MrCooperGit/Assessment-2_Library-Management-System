#include "employeeinfo.h"
#include "ui_employeeinfo.h"
#include "classes.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDir>
#include <QSqlQueryModel>

employeeinfo::employeeinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::employeeinfo)
{
    ui->setupUi(this);

    //Basic window style
    this->setWindowTitle("Test Window");
    this->setStyleSheet("background-color: white;");

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

    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("users.csv")); //file is now specific to the user's directory

    if (!file.open(QIODevice::ReadOnly)) {
           qDebug() << file.errorString();
       }

    QString email, password, firstName, lastName, userType, idNumber;
    while (!file.atEnd()) {
        QString line = file.readLine(); //place line into string

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

        if (password.contains("\r\n")) password.chop(2);   //removes '\r\n' from password
        qDebug() << email << idNumber << firstName << lastName << userType << password ;
        qry.prepare("INSERT INTO users(email, idNumber,"
                    "firstName, lastName, userType,"
                    "password) VALUES('"+email+"', '"+idNumber+"', '"+firstName+"', '"+lastName+"',"
                    "'"+userType+"', '"+password+"')");

        if(!qry.exec()){
            qDebug() << qry.lastError().text();
        }
    }
}

employeeinfo::~employeeinfo()
{
    delete ui;
}

void employeeinfo::on_pushButton_save_clicked()
{
    QString email, firstName, lastName, iD;
    //int idNumber = Item::getItemId();
    //iD = idNumber.toString();
    email = ui->lineEdit_email->text();
    firstName = ui->lineEdit_firstName->text();
    lastName = ui->lineEdit_lastName->text();
    iD = ui->lineEdit_idNumber->text();

    connOpen();

    QSqlQuery qry;
    qry.prepare("INSERT INTO users (email, idNumber, firstName, lastName) values ('"+email+"', '"+iD+"', '"+firstName+"', '"+lastName+"')");

    if(qry.exec()){
        QMessageBox::information(this, tr("Save"), tr("Data saved successfully"));
        connClose();
    }else{
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }

}


void employeeinfo::on_pushButton_edit_clicked()
{
    QString email, firstName, lastName, iD;
    email = ui->lineEdit_email->text();
    firstName = ui->lineEdit_firstName->text();
    lastName = ui->lineEdit_lastName->text();
    iD = ui->lineEdit_idNumber->text();

    connOpen();

    QSqlQuery qry;
    qry.prepare("UPDATE users SET email='"+email+"', idNumber='"+iD+"', firstName='"+firstName+"', lastName='"+lastName+"' WHERE idNumber='"+iD+"' ");

    if(qry.exec()){
        QMessageBox::information(this, tr("Edit"), tr("Data updated successfully"));
        connClose();
    }else{
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }
}


void employeeinfo::on_pushButton_delete_clicked()
{
    QString email, firstName, lastName, iD;
    email = ui->lineEdit_email->text();
    firstName = ui->lineEdit_firstName->text();
    lastName = ui->lineEdit_lastName->text();
    iD = ui->lineEdit_idNumber->text();

    connOpen();

    QSqlQuery qry;
    qry.prepare("DELETE FROM users WHERE idNumber='"+iD+"' ");

    if(qry.exec()){
        QMessageBox::information(this, tr("Delete"), tr("Data deleted successfully"));
        connClose();
    }else{
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }
}


void employeeinfo::on_pushButton_loadTable_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    connOpen();
    QSqlQuery * qry = new QSqlQuery(mydb);

    qry->prepare("SELECT * FROM users"); //if you don't want to display all
    //then change '*' to column names separated by comma's
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);

    connClose();
    qDebug() << "Row count: " << (model->rowCount());
}


void employeeinfo::on_pushButton_listView_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    connOpen();
    QSqlQuery * qry = new QSqlQuery(mydb);

    qry->prepare("SELECT lastName FROM users");
    qry->exec();
    model->setQuery(*qry);
    ui->listView->setModel(model);
    ui->comboBox->setModel(model);

    connClose();
    qDebug() << "Row count: " << (model->rowCount());
}




void employeeinfo::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString name = ui->comboBox->currentText();
    connOpen();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE lastName='"+name+"' ");

    if(qry.exec()){
        while(qry.next()){
            ui->lineEdit_email->setText(qry.value(0).toString());
            ui->lineEdit_firstName->setText(qry.value(2).toString());
            ui->lineEdit_lastName->setText(qry.value(3).toString());
            ui->lineEdit_idNumber->setText(qry.value(1).toString());
        }
        connClose();
    }else{
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }
}

