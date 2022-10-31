#include "library.h"
#include "QSharedPointer"

Library::Library()
{

}

void Library::RegisterNewUser()
{

}

void Library::setUsername(QString username)
{
    QSharedPointer<Library> ptr(new Library());
    ptr->username = username;
}

//void Library::setUserType(enum userType)
//{

//}

void Library::setPassword(QByteArray password)
{
    Library::password = password;
}
