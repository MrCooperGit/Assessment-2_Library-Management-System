#ifndef EDIT_MEMBER_SCREEN_H
#define EDIT_MEMBER_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QDir>
#include <QFile>


namespace Ui {
class edit_member_screen;
}

class edit_member_screen : public QWidget
{
    Q_OBJECT

public:
    explicit edit_member_screen(QWidget *parent = nullptr);
    ~edit_member_screen();

    QSqlDatabase mydb;

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

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_home_clicked();

    void on_pushButton_catalogue_clicked();

    void on_pushButton_catalogue_3_clicked();

private:
    Ui::edit_member_screen *ui;
};

#endif // EDIT_MEMBER_SCREEN_H
