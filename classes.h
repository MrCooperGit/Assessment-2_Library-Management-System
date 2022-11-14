#ifndef CLASSES_H
#define CLASSES_H

#include <QString>
#include <QObject>


class User {
    QString password;

public:
    QString firstName, lastName;
    static QString userName;
    static int iD;

    static int getUserId();

    void setName(QString fName, QString lName){
        this->firstName = fName;
        this->lastName = lName;
    }
    void setPassword(QString password){
        this->password = password;
    }

    QString getFirstName(){
        return firstName;
    }
    QString getLastName(){
        return lastName;
    }
    QString getPassword(){
        return password;
    }
    static void setUserName(QString fName, QString lName){
        User::userName = fName + lName;
    }
};


class Member : public User {
    QString emailAddress;

public:
    Member();

    void setEmail(QString email){
        this->emailAddress = email;
    }

    QString getEmail(){
        return emailAddress;
    }
};


class Admin : public User {
    QString username;

public:
    Admin();
};


class Item {

public:
    static int iD;

    //Item();
    static int getItemId();
};


class Book : public Item {
    QString title;
    QString author;
    QString coverImgRef;

public:
    //Book();

    void setTitle(QString title){
        this->title = title;
    }

    void setAuthor(QString author){
        this->author = author;
    }

    void setCoverImgRef(QString coverImgRef){
        this->coverImgRef = coverImgRef;
    }

    QString getTitle(){
        return title;
    }

    QString getAuthor(){
        return author;
    }

    QString getCoverImgRef(){
        return coverImgRef;
    }
};


#endif // CLASSES_H
