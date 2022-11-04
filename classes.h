#ifndef CLASSES_H
#define CLASSES_H

#include <QString>
#include <QObject>


class User {
    QString firstName, lastName;
    QString password;


public:
    static int iD;
    User(QString fN, QString lN, QString p);
    static int getUserId();
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
};


class Book : public Item {
    QString title;
    QString author;

public:
    Book();
    static int getItemId();
};

#endif // CLASSES_H
