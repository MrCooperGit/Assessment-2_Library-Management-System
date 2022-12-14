#include "classes.h"

#include <QFile>
#include <QDir>
#include <QString>
#include <QTextStream>


//Counts the number of lines in file and returns it as static int for userId
int User::getUserId(){
    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("users.csv")); //file is now specific to the user's directory
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
        return 0;
    }

    while(!file.atEnd()){
        file.readLine();
        iD++;
    }
    file.close();
    return iD + 10001;
}


int Item::getItemId(){
    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("books.csv")); //file is now specific to the user's directory
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
        return 0;
    }

    while(!file.atEnd()){
        file.readLine();
        iD++;
    }
    file.close();
    return iD + 10001;
}

