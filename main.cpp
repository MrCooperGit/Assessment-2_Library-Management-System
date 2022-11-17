#include "loginWindow.h"
#include "classes.h"

#include <QApplication>


int User::iD = 0;
int Item::iD = 0;
QString User::userName;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow w;
    w.show();
    return a.exec();
}
