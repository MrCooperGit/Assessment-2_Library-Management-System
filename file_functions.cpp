#include "file_functions.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

File_Functions::File_Functions()
{

}

void File_Functions::read_file(QString fileName)
{
    QFile file(fileName);
    if(!file.exists())
    {
        qCritical() << "File not found";
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
    }

    QTextStream stream(&file);

    while (!stream.atEnd()){
        QString line = stream.readLine();
        qInfo() << line;
    }

    file.close();
}

void File_Functions::register_user()
{

}

void File_Functions::update_user()
{

}

void File_Functions::update_book()
{

}

//bool File_Functions::validate_credentials()
//{

//}

//QString File_Functions::display_user()
//{


//}
