#ifndef LIBRARY_H
#define LIBRARY_H
#include "qtmetamacros.h"
#include <QObject>

enum userType{admin, member};

class Library : public QObject
{
    Q_OBJECT
public:
    Library();
    void RegisterNewUser();
    //void setUsername(QString username);
    void setUserType(enum userType);
    void setPassword(QByteArray password);

public slots:
    void setUsername(QString username);

private:
    enum userType;
    QString username;
    QByteArray password;
};

#endif // LIBRARY_H
