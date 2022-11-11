#ifndef EMPLOYEEINFO_H
#define EMPLOYEEINFO_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QDir>
#include <QFile>


namespace Ui {
class employeeinfo;
}

class employeeinfo : public QWidget
{
    Q_OBJECT

public:
    QSqlDatabase mydb;

    explicit employeeinfo(QWidget *parent = nullptr);
    ~employeeinfo();

    bool createDb(QString dbName){
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        QDir current;
        QString currentPath = current.currentPath(); //create string of current directory
        qInfo();
        mydb.setDatabaseName(currentPath + dbName);
        if(!mydb.open()){
           qDebug() << ("Failed to create database");
           return false;
        }else{
            qDebug() << ("Database created");
            return true;
        }
    }

    void connClose(){
        mydb.close();
    }
    bool connOpen(){
        mydb.open();
        if(!mydb.open()){
           qDebug() << ("Failed to connect to database");
           return false;
        }else{
            qDebug() << ("Database connected...");
            return true;
        }
    }

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_loadTable_clicked();

    void on_pushButton_listView_clicked();


    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::employeeinfo *ui;

};

#endif // EMPLOYEEINFO_H
