#include "your_items_screen.h"
#include "ui_your_items_screen.h"
#include "member_catalogue_screen.h"
#include "member_home_screen.h"
#include "loginWindow.h"
#include "QDate"
#include "classes.h"

#include <QDir>
#include <QMessageBox>
#include <QSignalMapper>
#include <QPalette>
#include <QBrush>
#include <QScrollArea>
#include <QSharedPointer>

your_items_screen::your_items_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::your_items_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Your Items");

    QPixmap pix(":/img/library.label.png");
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap pix2(":/img/yourItems.label.png");
    int w2 = ui->label_heading->width();
    int h2 = ui->label_heading->height();
    ui->label_heading->setPixmap(pix2.scaled(w2,h2, Qt::KeepAspectRatio));

    //construct timer to read date when screen opens
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(currentDate()));
    timer->start(1000); //time in ms

    // [0] construct username in top right corner and populate userId from userName
    ui->label_username->setText(User::userName);
//    QDir current;
//    QString currentPath = current.currentPath(); //create string of current directory
//    QDir dir(currentPath); //QDir variable becomes current directory
//    QFile fileU(dir.filePath("users.csv")); //file is now specific to the user's directory

//    if(!fileU.exists())
//    {
//        qCritical() << "File not found";
//    }

//    if(!fileU.open(QIODevice::ReadOnly))
//    {
//        qCritical() << fileU.errorString();
//    }

//    QString userId;
//    while (!fileU.atEnd()){
//        QString line = fileU.readLine(); //place line into string
//        qInfo() << line;
//        //empty the variables before each loop
//        userId.clear();

//        QString fName, lName; //temp variables to store names

//        //Making a string list to seperate each column of the file
//        QStringList fileList;
//        fileList.clear();
//        fileList = line.split(",");
//        fName = fileList[2];
//        lName = fileList[3];

//        //return the userId of the user logged in
//        if(line.contains(fName) && line.contains(lName)){
//            QStringList list = line.split(","); //split string into string array using "," as break
//            //assign variables by index of the string array
//            userId = list[1];
//            qInfo() << userId;
//            break;
//        }
//    }
    //[0]

    //create/link file including validation checks
    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("orders.csv")); //file is now specific to the user's directory
    if(!file.exists())
    {
        qCritical() << "File not found";
        QMessageBox::warning(this, "File Error", "File not found");
        return;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
        return;
    }

    //variables to determine size of objects later
    int defX = 5 /*x axis start*/, defY = 0 /*becomes y axis start for extra labels*/, defW = 130 /*label width*/, defH = 30 /*label height*/, offset_Y = 5 /*y axis start*/;

    //can only have one scrollArea widget, so call here outside the loop
    QWidget *currentlyLoaned = new QWidget(ui->scrollArea_currentlyLoaned);
    QWidget *dueSoon = new QWidget(ui->scrollArea_dueSoon);
    QWidget *overdue = new QWidget(ui->scrollArea_overdue);

    while (!file.atEnd()){

        QString line = file.readLine(); //store each line from file
        QString date, fileUserId;

        Book newBook; //declare book object

        //Making a string list to seperate each column of the file
        QStringList fileList;
        fileList.clear();
        fileList = line.split(",");

        //Transfer data from file into variables
        newBook.setTitle(fileList.value(fileList.length()-3));
        fileUserId = fileList.value(fileList.length()-2);
        date = fileList.value(fileList.length()-1);
        date.chop(2); //remove \r\n from last word in line

        //Compare current date with due dates from file
        QDate currentDate = QDate::currentDate(), fileDate;
        fileDate = QDate::fromString(date, "dd/MM/yyyy");
        int num = currentDate.daysTo(fileDate);

        //set scroll bar and ensure scroll widget is visible
        ui->scrollArea_currentlyLoaned->verticalScrollBarPolicy();
        ui->scrollArea_currentlyLoaned->setWidget(currentlyLoaned);
        ui->scrollArea_currentlyLoaned->verticalScrollBar();
        ui->scrollArea_currentlyLoaned->ensureWidgetVisible(currentlyLoaned);
        ui->scrollArea_overdue->verticalScrollBarPolicy();
        ui->scrollArea_overdue->setWidget(overdue);
        ui->scrollArea_overdue->verticalScrollBar();
        ui->scrollArea_overdue->ensureWidgetVisible(overdue);
        ui->scrollArea_dueSoon->verticalScrollBarPolicy();
        ui->scrollArea_dueSoon->setWidget(dueSoon);
        ui->scrollArea_dueSoon->verticalScrollBar();
        ui->scrollArea_dueSoon->ensureWidgetVisible(dueSoon);

        //if the userId on order.csv file matches the userId of the logged in user, then the book will display in one of four scrollArea widgets
        if(fileUserId.toInt() == User::iD){

            //All books ordered by the user will display in currentlyLoaned scroll area
            QLabel *label_title = new QLabel(currentlyLoaned);
            label_title->setWordWrap(true);
            label_title->setText(newBook.getTitle() + " Due: (" + date + ")");
            label_title->setGeometry(defX, (defY + offset_Y), defW, defH);

            defY += defH + offset_Y; //update y start position after each label
            offset_Y = 30; //30 px space between labels

            //If book is due within 3 days, display in Due Soon scroll area
            int DdefX = 5, DdefY = 0, DdefW = 130, DdefH = 30, Doffset_Y = 5;
            if(num >= 0 && num <= 3){
                //Creating labels for the title
                QLabel *label_title = new QLabel(dueSoon);
                label_title->setWordWrap(true);
                label_title->setText(newBook.getTitle() + " Due: (" + date + ")");
                label_title->setGeometry(DdefX, (DdefY + Doffset_Y), DdefW, DdefH);

                DdefY += DdefH + Doffset_Y; //update y start position after each label
                Doffset_Y = 30; //30 px space between labels

            }

            //If book is overdue, display in Overdue scroll area
            int OdefX = 5, OdefY = 0, OdefW = 130, OdefH = 30, Ooffset_Y = 5;
            if (num < 0){
                //Creating labels for the title
                QLabel *label_title = new QLabel(overdue);
                label_title->setWordWrap(true);
                label_title->setText(newBook.getTitle() + " Due: (" + date + ")");
                label_title->setGeometry(OdefX, (OdefY + Ooffset_Y), OdefW, OdefH);

                OdefY += OdefH + Ooffset_Y; //update y start position after each label
                Ooffset_Y = 30; //30 px space between labels
            }
            //update minimum height for all scroll areas
            currentlyLoaned->setMinimumHeight(defY);
            dueSoon->setMinimumHeight(DdefY);
            overdue->setMinimumHeight(OdefY);
        }
    }
}

your_items_screen::~your_items_screen()
{
    delete ui;
}

void your_items_screen::currentDate(){
    QDate date = QDate::currentDate();
    QString strDate = date.toString("dd/MM/yyyy");
    ui->label_date->setText(strDate);
}

void your_items_screen::on_pushButton_catalogue_clicked()
{
    member_catalogue_screen *ptr = new class member_catalogue_screen;
    ptr->show();
    close();
}


void your_items_screen::on_pushButton_home_clicked()
{
    member_home_screen *ptr = new class member_home_screen;
    ptr->show();
    close();
}



