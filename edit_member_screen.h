#ifndef EDIT_MEMBER_SCREEN_H
#define EDIT_MEMBER_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <QSqlRecord>

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

    QString escapedCSV(QString unexc)
    {
        if (!unexc.contains(QLatin1Char(',')))
            return unexc;
        return '\"' + unexc.replace(QLatin1Char('\"'), QStringLiteral("\"\"")) + '\"';
    }

    void queryToCsv()
    {
        connOpen();
        QSqlQuery query(mydb);
        query.prepare(" select * from users;");

        QDir current;
        QString currentPath = current.currentPath(); //create string of current directory
        QDir dir(currentPath); //QDir variable becomes current directory
        dir.remove("users.csv"); //Delete previous file version to start fresh
        QFile file(dir.filePath("users.csv")); //file is now specific to the user's directory

        if (!file.open(QFile::WriteOnly)){
            qDebug("failed to open csv file");
            return;
        }
        if (!query.exec()){
            qDebug("failed to run query");
            return;
        }
        QTextStream outStream(&file);
        while (query.next()){
            const QSqlRecord record = query.record(); //stores the database row value in record
            for (int i=0, recCount = record.count() ; i<recCount ; ++i){ //count() returns number of fields in record
                if (i>0)
                    outStream << ',';
                outStream << escapedCSV(record.value(i).toString());
            }
            outStream << '\n';
        }
        connClose();
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
