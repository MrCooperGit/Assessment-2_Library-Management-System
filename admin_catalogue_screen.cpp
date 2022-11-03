#include "admin_catalogue_screen.h"
#include "ui_admin_catalogue_screen.h"
#include "admin_home_screen.h"
#include "member_list_screen.h"
#include "add_new_book_screen.h"

#include <QFile>
#include <QMessageBox>
#include <QScrollArea>
#include <QPixmap>

bool searched = false;
QString searchText;

admin_catalogue_screen::admin_catalogue_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_catalogue_screen)
{
    ui->setupUi(this);

    //QScrollArea *scrollArea = new QScrollArea;
    //scrollArea->setWidget(this);
    //scrollArea->setGeometry(0, 0, this->width(), this->height());


    //Basic window style
    this->setWindowTitle("Admin Catalogue");
    this->setStyleSheet("background-color: white;");

    //Setting logo images
    QPixmap footerlogo_pix(":/img/library.label.png");
    ui->label_title->setPixmap(footerlogo_pix);
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(footerlogo_pix.scaled(w,h, Qt::KeepAspectRatio));

    QFile file("books.csv");

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

    int defX = 250, defY = 80, defW = 200, defH = 15;
    int offset_Y = 30, offset_X = -80;

    int img_W = 50, img_H = 80;

    //Bool to skip first line of file which is blank
    bool firstLine = true;

    while (!file.atEnd()){

        QString line = file.readLine();

        if (!firstLine){    //Skips first line of file

            QString title;
            QString author;
            QString id;

            QString searchText = ui->lineEdit_search->displayText();

            title.clear();  author.clear();  id.clear();  //Clearing strings from previous line of file

            //Making a string list to seperate each column of the file
            QStringList fileList;
            fileList.clear();
            fileList = line.split(",");

            //Transfer data from file into variables
            title = fileList.value(fileList.length()-2);
            author = fileList.value(fileList.length()-1);
            id = fileList.value(fileList.length()-3);


            if (searched == false){

                //Creating image for book

                if (title.contains("The Hobbit")){

                    QLabel *label_title_img = new QLabel(this);
                    label_title_img->setGeometry((defX + offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img("://img/Hobbit.book.jpg");
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (title.contains("To Kill A Mockingbird")){

                    QLabel *label_title_img = new QLabel(this);
                    label_title_img->setGeometry((defX + offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img("://img/Mockingbird.book.jpg");
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));
                }
                else {

                    //Default image that shows if one isn't set
                    QLabel *label_title_img = new QLabel(this);
                    label_title_img->setGeometry((defX + offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img("://img/noImage.png");
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));
                }


                //Creating labels for the title, author, id
                QLabel *label_title = new QLabel(this);
                label_title->setText(title);
                label_title->setGeometry(defX, (defY + offset_Y), defW, defH);

                defX = label_title->x();
                defY = label_title->y();
                defW = label_title->width();
                defH = label_title->height();

                QLabel *label_author = new QLabel(this);
                label_author->setText(author);
                label_author->setGeometry(defX, (defY + offset_Y), defW, defH);

                defX = label_author->x();
                defY = label_author->y();
                defW = label_author->width();
                defH = label_author->height();

                QLabel *label_id = new QLabel(this);
                label_id->setText(id);
                label_id->setGeometry(defX, (defY + offset_Y), defW, defH);

                defX = label_id->x();
                defY = label_id->y() + offset_Y;
                defW = label_id->width();
                defH = label_id->height();
            }
        }

        firstLine = false;
    }

    file.close();


    //----------------------------------------------------------------


    //Search
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

        if (!firstLine){    //Skips first line of file

            QString title;
            QString author;
            QString id;

            title.clear();  author.clear();  id.clear();  //Clearing strings from previous line of file

            //Making a string list to seperate each column of the file
            QStringList fileList;
            fileList.clear();
            fileList = line.split(",");

            //Transfer data from file into variables
            title = fileList.value(fileList.length()-2);
            author = fileList.value(fileList.length()-1);
            id = fileList.value(fileList.length()-3);

            if (searched == true && title.contains(searchText)) {

                //Creating image for book

                if (title.contains("The Hobbit")){

                    QLabel *label_title_img = new QLabel(this);
                    label_title_img->setGeometry((defX + offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img("://img/Hobbit.book.jpg");
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (title.contains("To Kill A Mockingbird")){

                    QLabel *label_title_img = new QLabel(this);
                    label_title_img->setGeometry((defX + offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img("://img/Mockingbird.book.jpg");
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));
                }
                else {

                    //Default image that shows if one isn't set
                    QLabel *label_title_img = new QLabel(this);
                    label_title_img->setGeometry((defX + offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img("://img/noImage.png");
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));
                }


                //Creating labels for the title, author, id
                QLabel *label_title = new QLabel(this);
                label_title->setText(title);
                label_title->setGeometry(defX, (defY + offset_Y), defW, defH);

                defX = label_title->x();
                defY = label_title->y();
                defW = label_title->width();
                defH = label_title->height();

                QLabel *label_author = new QLabel(this);
                label_author->setText(author);
                label_author->setGeometry(defX, (defY + offset_Y), defW, defH);

                defX = label_author->x();
                defY = label_author->y();
                defW = label_author->width();
                defH = label_author->height();

                QLabel *label_id = new QLabel(this);
                label_id->setText(id);
                label_id->setGeometry(defX, (defY + offset_Y), defW, defH);

                defX = label_id->x();
                defY = label_id->y() + offset_Y;
                defW = label_id->width();
                defH = label_id->height();
            }
        }

        firstLine = false;
    }
}

admin_catalogue_screen::~admin_catalogue_screen()
{
    delete ui;
}

void admin_catalogue_screen::on_pushButton_home_clicked()
{
    admin_home_screen *ptr = new class admin_home_screen;
    ptr->show();
    close();
}


void admin_catalogue_screen::on_pushButton_modifyMembers_clicked()
{
    member_list_screen *ptr = new class member_list_screen;
    ptr->show();
    close();
}


void admin_catalogue_screen::on_pushButton_addNewBook_clicked()
{
    add_new_book_screen *ptr = new class add_new_book_screen;
    ptr->show();
    close();
}


void admin_catalogue_screen::on_pushButton_search_clicked()
{
    searchText = ui->lineEdit_search->displayText();

    if (searchText.isEmpty()){
        searched = false;
    } else if (!searchText.isEmpty()){
        searched = true;
    }

    admin_catalogue_screen *ptr = new admin_catalogue_screen;
    ptr->show();
    close();

}


void admin_catalogue_screen::on_label_username_windowTitleChanged(const QString &title)
{

}



