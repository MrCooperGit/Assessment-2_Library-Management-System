#include "admin_catalogue_screen.h"
#include "ui_admin_catalogue_screen.h"
#include "admin_home_screen.h"
#include "edit_member_screen.h"
#include "add_new_book_screen.h"
#include "edit_book_screen.h"
#include "admin_book_view_screen.h"
#include "edit_member_screen.h"
#include "classes.h"


#include <QFile>
#include <QMessageBox>
#include <QScrollArea>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QSignalMapper>

bool searched = false;
bool emptySearch = false;
int numofItems = 0;
QString searchText;

QString BookTitleToLower(QString bookTitle);

admin_catalogue_screen::admin_catalogue_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_catalogue_screen)
{
    ui->setupUi(this);

    //Basic window style
    this->setWindowTitle("Admin Catalogue");
    this->setStyleSheet("background-color: white;");

    //Setting logo images
    QPixmap footerlogo_pix(":/img/library.label.png");
    ui->label_title->setPixmap(footerlogo_pix);
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(footerlogo_pix.scaled(w,h, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName);

    numofItems = 0;

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


            if (searched == false){

                //Creating image for book
                if (newBook.getTitle().toLower().contains(BookTitleToLower("The Hobbit"))){

                    newBook.setCoverImgRef("://img/Hobbit.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("To Kill A Mockingbird"))){

                    newBook.setCoverImgRef("://img/Mockingbird.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("The Fellowship of the Ring"))){

                    newBook.setCoverImgRef(":/img/FofRing.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("It Felt Like a Kiss"))){

                    newBook.setCoverImgRef(":/img/itFeltLikeAKiss.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("Starsight"))){

                    newBook.setCoverImgRef(":/img/starsight.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));


                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("She Said Three Said"))){

                    newBook.setCoverImgRef("://img/LYONS.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));


                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("Tess Pendragon and the Wand of Avalon"))){

                    newBook.setCoverImgRef("://img/wandOfAvalon.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));


                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("Zero Hour"))){

                    newBook.setCoverImgRef("://img/zeroHour.book.jpg");
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


                //Creating Edit Button for book
                QPushButton *edit_btn = new QPushButton(widget);
                edit_btn->setText("Edit");
                edit_btn->setGeometry((defX + btn_offset_X), (defY + offset_Y), btnW, defH);
                edit_btn->setCursor(Qt::PointingHandCursor);



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


                //Connect edit button signal and slot
                QSignalMapper *signalMapper = new QSignalMapper;
                connect(signalMapper, SIGNAL(mappedString(QString)), this, SLOT(edit_btn_clicked(QString)));

                connect(edit_btn, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));

                signalMapper->setMapping(edit_btn, id);

                //Creating view book screen button
                QPushButton *book_btn = new QPushButton(widget);
                book_btn->setGeometry((book_btn_X + img_offset_X), (book_btn_Y + offset_Y), defW, 85);

                book_btn->setFlat(true);
                book_btn->setCursor(Qt::PointingHandCursor);

                //Connect book button signal and slot
                QString book_view_info = id + "," + newBook.getCoverImgRef();

                QSignalMapper *book_btn_signalMapper = new QSignalMapper;
                connect(book_btn_signalMapper, SIGNAL(mappedString(QString)), this, SLOT(book_btn_clicked(QString)));

                connect(book_btn, SIGNAL(clicked(bool)), book_btn_signalMapper, SLOT(map()));

                book_btn_signalMapper->setMapping(book_btn, book_view_info);


                ui->scrollArea->verticalScrollBarPolicy();

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


        if (searched == true) {

            ui->lineEdit_search->setText(searchText);

            if (newBook.getTitle().toLower().contains(searchText.toLower())){

                numofItems++;

                //Creating image for book
                if (newBook.getTitle().toLower().contains(BookTitleToLower("The Hobbit"))){

                    newBook.setCoverImgRef("://img/Hobbit.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("To Kill A Mockingbird"))){

                    newBook.setCoverImgRef("://img/Mockingbird.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("The Fellowship of the Ring"))){

                    newBook.setCoverImgRef(":/img/FofRing.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("It Felt Like a Kiss"))){

                    newBook.setCoverImgRef(":/img/itFeltLikeAKiss.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));

                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("Starsight"))){

                    newBook.setCoverImgRef(":/img/starsight.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));


                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("She Said Three Said"))){

                    newBook.setCoverImgRef("://img/LYONS.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));


                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("Tess Pendragon and the Wand of Avalon"))){

                    newBook.setCoverImgRef("://img/wandOfAvalon.book.jpg");
                    QLabel *label_title_img = new QLabel(widget);
                    label_title_img->setGeometry((defX + img_offset_X), (defY + offset_Y), img_W, img_H);
                    QPixmap title_img(newBook.getCoverImgRef());
                    label_title_img->setPixmap(title_img.scaled(img_W, img_H));


                } else if (newBook.getTitle().toLower().contains(BookTitleToLower("Zero Hour"))){

                    newBook.setCoverImgRef("://img/zeroHour.book.jpg");
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


                //Creating Edit Button for book
                QPushButton *edit_btn = new QPushButton(widget);
                edit_btn->setText("Edit");
                edit_btn->setGeometry((defX + btn_offset_X), (defY + offset_Y), btnW, defH);
                edit_btn->setCursor(Qt::PointingHandCursor);


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

                //Connect edit button signal and slot
                QSignalMapper *edit_btn_signalMapper = new QSignalMapper;
                connect(edit_btn_signalMapper, SIGNAL(mappedString(QString)), this, SLOT(edit_btn_clicked(QString)));

                connect(edit_btn, SIGNAL(clicked(bool)), edit_btn_signalMapper, SLOT(map()));

                edit_btn_signalMapper->setMapping(edit_btn, id);


                //Creating view book screen button
                QPushButton *book_btn = new QPushButton(widget);
                book_btn->setGeometry((book_btn_X + img_offset_X), (book_btn_Y + offset_Y), defW, 85);
                book_btn->setCursor(Qt::PointingHandCursor);


                //Connect book button signal and slot
                QString book_view_info = id + "," + newBook.getCoverImgRef();

                QSignalMapper *book_btn_signalMapper = new QSignalMapper;
                connect(book_btn_signalMapper, SIGNAL(mappedString(QString)), this, SLOT(book_btn_clicked(QString)));

                connect(book_btn, SIGNAL(clicked(bool)), book_btn_signalMapper, SLOT(map()));

                book_btn_signalMapper->setMapping(book_btn, book_view_info);


                book_btn->setFlat(true);

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

//Returns book title in lowercase for non case sensitive comparison
QString BookTitleToLower(QString bookTitle){

    QString s = bookTitle.toLower();
    return s;

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

void admin_catalogue_screen::edit_btn_clicked(QString id){

    edit_book_screen *ptr = new class edit_book_screen(id);
    ptr->show();
    close();


}

void admin_catalogue_screen::book_btn_clicked(QString bookInfo){

    admin_book_view_screen *ptr = new admin_book_view_screen(bookInfo);
    ptr->show();
    close();

}


void admin_catalogue_screen::on_pushButton_modifyMembers_clicked()
{
    edit_member_screen *ptr = new edit_member_screen;
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
        if (numofItems == 0 && searched){

            QMessageBox::information(this, "Title", "Book not found");

            searched = false;


            admin_catalogue_screen *ptr = new admin_catalogue_screen;
            ptr->show();
            this->close();


        } else {

            ptr->show();
            close();
        }




}


void admin_catalogue_screen::on_label_username_windowTitleChanged(const QString &title)
{

}



