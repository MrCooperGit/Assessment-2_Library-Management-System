#include "member_catalogue_screen.h"
#include "ui_member_catalogue_screen.h"
#include "member_home_screen.h"
#include "member_book_order_screen.h"
#include "classes.h"
#include "your_items_screen.h"

#include <QFile>
#include <QMessageBox>
#include <QScrollArea>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QSignalMapper>
#include <QDir>

bool _searched = false;
bool _emptySearch = false;
int _numofItems = 0;
QString _searchText;

member_catalogue_screen::member_catalogue_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::member_catalogue_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Member Catalogue");

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Member Catalogue Screen");

    //Setting logo images
    QPixmap footerlogo_pix(":/img/library.label.png");
    ui->label_title->setPixmap(footerlogo_pix);
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(footerlogo_pix.scaled(w,h, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName);

    _numofItems = 0;

    QDir current;
    QString currentPath = current.currentPath(); //create string of current directory
    QDir dir(currentPath); //QDir variable becomes current directory
    QFile file(dir.filePath("books.csv")); //file is now specific to the user's directory

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

    int defX = 250, defY = 0, defW = 200, defH = 15;
    int btnW = 50;
    int offset_Y = 30, img_offset_X = -80, btn_offset_X = 250;

    int img_W = 50, img_H = 80;

    int book_btn_X, book_btn_Y;

    QWidget *widget = new QWidget(ui->scrollArea);

    while (!file.atEnd()){

        QString line = file.readLine();
        QString id;

        Book newBook;


            //Making a string list to seperate each column of the file
            QStringList fileList;
            fileList.clear();
            fileList = line.split(",");

            //Transfer data from file into variables
            newBook.setTitle(fileList.value(fileList.length()-2));
            newBook.setAuthor(fileList.value(fileList.length()-1));
            id = fileList.value(fileList.length()-3);


            if (_searched == false){

                //Creating image for book
                if (newBook.getTitle().contains("The Hobbit")){

                    newBook.setCoverImgRef("://img/Hobbit.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (newBook.getTitle().contains("To Kill A Mockingbird")){

                    newBook.setCoverImgRef("://img/Mockingbird.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));


                }
                else {

                    //Default image that shows if one isn't set
                    newBook.setCoverImgRef("://img/noImage.png");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));


                }


                //Creating labels for the title, author, id
                QLabel *label_title = new QLabel(widget);
                label_title->setText(newBook.getTitle());
                label_title->setGeometry(defX, (defY + offset_Y), defW, defH);


                book_btn_X = defX;
                book_btn_Y = defY;

                defX = label_title->x();
                defY = label_title->y();
                defW = label_title->width();
                defH = label_title->height();



                QLabel *label_author = new QLabel(widget);
                label_author->setText(newBook.getAuthor());
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



                //Creating view book screen button
                QPushButton *book_btn = new QPushButton(widget);
                book_btn->setGeometry((book_btn_X + img_offset_X), (book_btn_Y + offset_Y), defW, 85);

                book_btn->setFlat(true);
                book_btn->setCursor(Qt::PointingHandCursor);

                //Connect book button signal and slot
                QString book_view_info = id + "," + newBook.getCoverImgRef();

                QSignalMapper *book_btn_signalMapper = new QSignalMapper;
                connect(book_btn_signalMapper, SIGNAL(mappedString(QString)), this, SLOT(member_btn_clicked(QString)));

                connect(book_btn, SIGNAL(clicked(bool)), book_btn_signalMapper, SLOT(map()));

                book_btn_signalMapper->setMapping(book_btn, book_view_info);


                ui->scrollArea->verticalScrollBarPolicy();

                label_title->layoutDirection();

                widget->setMinimumHeight(defY);

                ui->scrollArea->setWidget(widget);
                ui->scrollArea->verticalScrollBar();
                ui->scrollArea->ensureWidgetVisible(widget);

            }

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

        QString id;

        Book newBook;

        //Making a string list to seperate each column of the file
        QStringList fileList;
        fileList.clear();
        fileList = line.split(",");

        //Transfer data from file into variables
        newBook.setTitle(fileList.value(fileList.length()-2));
        newBook.setAuthor(fileList.value(fileList.length()-1));
        id = fileList.value(fileList.length()-3);


        if (_searched == true) {

            ui->lineEdit_search->setText(_searchText);

            if (newBook.getTitle().toLower().contains(_searchText.toLower())){

                _numofItems++;

                //Creating image for book

                if (newBook.getTitle().contains("The Hobbit")){

                    newBook.setCoverImgRef("://img/Hobbit.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (newBook.getTitle().contains("To Kill A Mockingbird")){

                    newBook.setCoverImgRef("://img/Mockingbird.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));
                }
                else {

                    //Default image that shows if one isn't set
                    newBook.setCoverImgRef("://img/noImage.png");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));
                }


                //Creating labels for the title, author, id
                QLabel *label_title = new QLabel(widget);
                label_title->setText(newBook.getTitle());
                label_title->setGeometry(defX, (defY + offset_Y), defW, defH);

                book_btn_X = defX;
                book_btn_Y = defY;

                defX = label_title->x();
                defY = label_title->y();
                defW = label_title->width();
                defH = label_title->height();

                QLabel *label_author = new QLabel(widget);
                label_author->setText(newBook.getAuthor());
                label_author->setGeometry(defX, (defY + offset_Y), defW, defH);

                defX = label_author->x();
                defY = label_author->y();
                defW = label_author->width();
                defH = label_author->height();

                QLabel *label_id = new QLabel(widget);
                label_id->setText("Book ID: " + id);
                label_id->setGeometry(defX, (defY + offset_Y), defW, defH);

                defX = label_id->x();
                defY = label_id->y() + offset_Y;
                defW = label_id->width();
                defH = label_id->height();


                //Creating view book screen button
                QPushButton *member_btn = new QPushButton(widget);
                member_btn->setGeometry((book_btn_X + img_offset_X), (book_btn_Y + offset_Y), defW, 85);
                member_btn->setCursor(Qt::PointingHandCursor);


                //Connect book button signal and slot
                QString member_view_info = id + "," + newBook.getCoverImgRef();

                QSignalMapper *member_btn_signalMapper = new QSignalMapper;
                connect(member_btn_signalMapper, SIGNAL(mappedString(QString)), this, SLOT(member_btn_clicked(QString)));

                connect(member_btn, SIGNAL(clicked(bool)), member_btn_signalMapper, SLOT(map()));

                member_btn_signalMapper->setMapping(member_btn, member_view_info);


                member_btn->setFlat(true);

                ui->scrollArea->verticalScrollBarPolicy();

                label_title->layoutDirection();

                widget->setMinimumHeight(defY);

                ui->scrollArea->setWidget(widget);
                ui->scrollArea->verticalScrollBar();
                ui->scrollArea->ensureWidgetVisible(widget);
            }
        }
    }
        file.close();
}


member_catalogue_screen::~member_catalogue_screen()
{
    delete ui;
}

void member_catalogue_screen::on_pushButton_home_clicked()
{
    member_home_screen *ptr = new class member_home_screen;
    ptr->show();
    close();
}

void member_catalogue_screen::member_btn_clicked(QString memberInfo){

    member_book_order_screen *ptr = new member_book_order_screen(memberInfo);
    ptr->show();
    close();

}


void member_catalogue_screen::on_pushButton_search_clicked()
{
    _searchText = ui->lineEdit_search->displayText();

    if (_searchText.isEmpty()){
        _searched = false;
    } else if (!_searchText.isEmpty()){
        _searched = true;
    }


        member_catalogue_screen *ptr = new member_catalogue_screen;
        if (_numofItems == 0 && _searched){

            QMessageBox::information(this, "Title", "Book not found");

            _searched = false;


            member_catalogue_screen *ptr = new member_catalogue_screen;
            ptr->show();
            this->close();


        } else {

            ptr->show();
            close();
        }
}


void member_catalogue_screen::on_pushButton_yourItems_clicked()
{
    your_items_screen *ptr = new class your_items_screen;
    ptr->show();
    close();
}

