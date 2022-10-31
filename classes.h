#ifndef CLASSES_H
#define CLASSES_H

#include <QString>

class User {
    int ID;
    QString firstName, lastName;
    QString username;
    QString password;
};


class Member : public User {
    QString emailAddress;
};


class Admin : public User {

};


class Item {
    int ID;
};


class Book : public Item {
    QString title;
    QString author;
};

#endif // CLASSES_H
