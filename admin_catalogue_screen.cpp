#include "admin_catalogue_screen.h"
#include "ui_admin_catalogue_screen.h"
#include "admin_home_screen.h"
#include "member_list_screen.h"
#include "add_new_book_screen.h"
#include "classes.h"


#include <QFile>
#include <QMessageBox>

admin_catalogue_screen::admin_catalogue_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_catalogue_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin Catalogue");

    //Basic window style
    this->setStyleSheet("background-color: white;");
    this->setWindowTitle("Admin Catalogue Screen");

    //Setting logo images
    QPixmap footerlogo_pix(":/img/library.label.png");
    ui->label_title->setPixmap(footerlogo_pix);
    int w = ui->label_title->width();
    int h = ui->label_title->height();
    ui->label_title->setPixmap(footerlogo_pix.scaled(w,h, Qt::KeepAspectRatio));

    //construct username in top right corner
    ui->label_username->setText(User::userName());

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

    int defX = 250, defY = 80, defW = 200, defH = 10;
    int offset_Y = 30;

    while (!file.atEnd()){

        QString line = file.readLine();

        QString title;
        QString author;
        QString id;

        QString searchText = ui->lineEdit_search->displayText();

        title.clear();  author.clear();  id.clear();  //Clearing strings from previous line of file

        //Making a string list to seperate each column of the file
        QStringList fileList;
        fileList.append(line.split(("")));


        title.append(fileList.value(0+1));
        author.append(fileList.value(0+2));
        id.append(fileList.value(0));


        if (searchText.isEmpty()){

            QLabel *label_title = new QLabel(this);
            label_title->setText("title");
            label_title->setGeometry(defX, (defY + offset_Y), defW, defH);

            defX = label_title->x();
            defY = label_title->y();
            defW = label_title->width();
            defH = label_title->height();

            QLabel *label_author = new QLabel(this);
            label_author->setText("author");
            label_author->setGeometry(defX, (defY + offset_Y), defW, defH);

            defX = label_author->x();
            defY = label_author->y();
            defW = label_author->width();
            defH = label_author->height();

            QLabel *label_id = new QLabel(this);
            label_id->setText("id");
            label_id->setGeometry(defX, (defY + offset_Y), defW, defH);

            defX = label_id->x();
            defY = label_id->y() + offset_Y;
            defW = label_id->width();
            defH = label_id->height();
        }

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

}


void admin_catalogue_screen::on_label_username_windowTitleChanged(const QString &title)
{

}



