#include "loginWindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QSharedPointer>

void basics(){
    QFile file("test.txt");
    if(!file.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not open the file!";
        qCritical() << file.errorString();
        return;
    }

    qInfo() << "Writing file...";
    file.write(QByteArray("Hello World"));
    file.flush(); // pushes the data to the disk/device

    qInfo() << "Reading file...";
    file.seek(0);
    qInfo() << file.readAll();

    file.close();
}

bool writeFile(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        qCritical() << file.errorString();
        return false;
    }

    QTextStream stream(&file);
    for(int i=0; i < 5; i++)
    {
        stream << QString::number(i) << "Hello World\r\n";
    }
   // stream << qmap;

    file.close();
    return true;
}

void readFile(QString filename)
{
    QFile file(filename);
    if(!file.exists())
    {
        qCritical() << "File not found";
        return;
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
        return;
    }

    QTextStream stream(&file);
    //QString data = stream.readAll();

    while (!stream.atEnd()){
        QString line = stream.readLine();
        qInfo() << line;
    }

    file.close();

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    LoginWindow w;
    w.show();
    return a.exec();
}
