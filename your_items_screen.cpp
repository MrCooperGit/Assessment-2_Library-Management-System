#include "your_items_screen.h"
#include "ui_your_items_screen.h"
#include "member_catalogue_screen.h"
#include "member_home_screen.h"
#include "loginWindow.h"
#include "QDate"
#include "classes.h"

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

    //construct username in top right corner
    ui->label_username->setText(User::userName());
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

