#include "member_list_screen.h"
#include "ui_member_list_screen.h"
#include "admin_catalogue_screen.h"
#include "add_new_member_screen.h"
#include "admin_home_screen.h"
#include "classes.h"

#include <QDir>
#include <QMessageBox>
#include <QSignalMapper>
#include <QPalette>
#include <QBrush>
#include <QScrollArea>

//bool searched = false;
QString SearchText;

member_list_screen::member_list_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::member_list_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Member List");

    //Setting logo images
    QPixmap footerlogo_pix(":/img/library.label.png");
    ui->label_title->setPixmap(footerlogo_pix);
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(footerlogo_pix.scaled(w,h, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName());

    //create/link file including validation checks
    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("users.csv")); //file is now specific to the user's directory
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
    int defX = 250, defY = 0, defW = 200, defH = 15;
    int btnW = 50;
    int offset_Y = 30, img_offset_X = -80, btn_offset_X = 250;
    int img_W = 50, img_H = 80;
    int book_btn_X, book_btn_Y;

    QWidget *widget = new QWidget(ui->scrollArea);

    while (!file.atEnd()){

        QString line = file.readLine();
        QString firstName;
        QString lastName;
        QString email;
        QString id;

        QString searchText = ui->lineEdit_search->displayText();

        firstName.clear();  lastName.clear(); email.clear();  id.clear();  //Clearing strings from previous line of file

        //Making a string list to seperate each column of the file
        QStringList fileList;
        fileList.clear();
        fileList = line.split(",");

        //Transfer data from file into variables
        firstName = fileList[2];
        lastName = lastName[3];
        email = email[0];
        id = id[1];

        bool searched = false;
        if (searched == false){

            //Creating image for book
//            if (title.contains("The Hobbit")){

//                QLabel *label_title_img = new QLabel(widget);
//                label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
//                QPixmap title_img("://img/Hobbit.book.jpg");
//                label_title_img->setPixmap(title_img.scaled(img_W, img_H));

//            } else if (title.contains("To Kill A Mockingbird")){

//                QLabel *label_title_img = new QLabel(widget);
//                label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
//                QPixmap title_img("://img/Mockingbird.book.jpg");
//                label_title_img->setPixmap(title_img.scaled(img_W, img_H));


//            }
//            else {

//                //Default image that shows if one isn't set
//                QLabel *label_title_img = new QLabel(widget);
//                label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
//                QPixmap title_img("://img/noImage.png");
//                label_title_img->setPixmap(title_img.scaled(img_W, img_H));


//            }


            //Creating Edit Button for member
            QPushButton *edit_btn = new QPushButton(widget);
            edit_btn->setText("Edit");
            edit_btn->setGeometry((defX + btn_offset_X), (defY + offset_Y), btnW, defH);
            edit_btn->setCursor(Qt::PointingHandCursor);


            //Creating labels for the fullName, email, id
            QLabel *label_title = new QLabel(widget);
            label_title->setText(firstName + lastName);
            label_title->setGeometry(defX, (defY + offset_Y), defW, defH);
            defX = label_title->x();
            defY = label_title->y();
            defW = label_title->width();
            defH = label_title->height();


            QLabel *label_author = new QLabel(widget);
            label_author->setText(email);
            label_author->setGeometry(defX, (defY + offset_Y), defW, defH);
            defX = label_author->x();
            defY = label_author->y();
            defW = label_author->width();
            defH = label_author->height();

            QLabel *label_id = new QLabel(widget);
            label_id->setText(id);
            label_id->setGeometry(defX, (defY + offset_Y), defW, defH);
            defX = label_id->x();
            defY = label_id->y() + offset_Y;
            defW = label_id->width();
            defH = label_id->height();


            //Connect edit button signal and slot
            QSignalMapper *signalMapper = new QSignalMapper;
            connect(signalMapper, SIGNAL(mappedString(QString)), this, SLOT(edit_btn_clicked(QString)));
            connect(edit_btn, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
            signalMapper->setMapping(edit_btn, id);

            //Creating view book screen button
//            QPushButton *book_btn = new QPushButton(widget);
//            book_btn->setGeometry((book_btn_X + img_offset_X), (book_btn_Y + offset_Y), defW, 85);
//            edit_btn->setCursor(Qt::PointingHandCursor);
//            book_btn->setFlat(true);
//            connect(book_btn, SIGNAL(clicked(bool)), this, SLOT(book_btn_clicked()));

            ui->scrollArea->verticalScrollBarPolicy();

            label_title->layoutDirection();

            widget->setMinimumHeight(defY);

            ui->scrollArea->setWidget(widget);
            ui->scrollArea->verticalScrollBar();
            ui->scrollArea->ensureWidgetVisible(widget);

        }
    }
    file.close();
}


member_list_screen::~member_list_screen()
{
    delete ui;
}

void member_list_screen::on_pushButton_home_clicked()
{
    admin_home_screen *ptr = new class admin_home_screen;
    ptr->show();
    close();
}


void member_list_screen::on_pushButton_modifyCatalogue_clicked()
{
    admin_catalogue_screen *ptr = new class admin_catalogue_screen;
    ptr->show();
    close();
}


void member_list_screen::on_pushButton_addNewMember_clicked()
{
    add_new_member_screen *ptr = new class add_new_member_screen;
    ptr->show();
    close();
}


void member_list_screen::on_pushButton_search_clicked()
{
    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("users.csv")); //file is now specific to the user's directory

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

    while (!file.atEnd()){

        QString line = file.readLine();
        QString firstName;
        QString lastName;
        QString email;
        QString id;

        firstName.clear();  lastName.clear(); email.clear();  id.clear();  //Clearing strings from previous line of file

        //Making a string list to seperate each column of the file
        QStringList fileList;
        fileList.clear();
        fileList = line.split(",");

        //Transfer data from file into variables
        firstName = fileList[2];
        lastName = lastName[3];
        email = email[0];
        id = id[1];

        QString searchText = ui->lineEdit_search->text();
//        if (searched == true && title.contains(searchText)) {

//                //Creating labels for the title, author, id
//                QLabel *label_title = new QLabel(this);
//                label_title->setText(title);
//                label_title->setGeometry(defX, (defY + offset_Y), defW, defH);

//                defX = label_title->x();
//                defY = label_title->y();
//                defW = label_title->width();
//                defH = label_title->height();

//                QLabel *label_author = new QLabel(this);
//                label_author->setText(author);
//                label_author->setGeometry(defX, (defY + offset_Y), defW, defH);

//                defX = label_author->x();
//                defY = label_author->y();
//                defW = label_author->width();
//                defH = label_author->height();

//                QLabel *label_id = new QLabel(this);
//                label_id->setText(id);
//                label_id->setGeometry(defX, (defY + offset_Y), defW, defH);

//                defX = label_id->x();
//                defY = label_id->y() + offset_Y;
//                defW = label_id->width();
//                defH = label_id->height();
//            }

    }
}

