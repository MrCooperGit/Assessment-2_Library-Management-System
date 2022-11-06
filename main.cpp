#include "loginWindow.h"
#include "classes.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QSharedPointer>

int User::iD = 0;
int Item::iD = 0;
QString User::firstName, User::lastName;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow w;
    w.show();
    return a.exec();
}
