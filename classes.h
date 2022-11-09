#ifndef CLASSES_H
#define CLASSES_H

#include <QString>
#include <QObject>


class User {
    QString password;

public:
    static QString firstName, lastName;
    static int iD;

    static int getUserId();
    static QString userName();
    static void setName(QString fName, QString lastName);
};


class Member : public User {
    QString emailAddress;

public:
    Member();
};


class Admin : public User {
    QString username;

public:
    Admin();
};


class Item {

public:
    static int iD;

    Item();
    static int getItemId();
};


class Book : public Item {
    QString title;
    QString author;

public:
    Book();
};

#endif // CLASSES_H
