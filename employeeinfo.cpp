#include "employeeinfo.h"
#include "ui_employeeinfo.h"

employeeinfo::employeeinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::employeeinfo)
{
    ui->setupUi(this);
}

employeeinfo::~employeeinfo()
{
    delete ui;
}

void employeeinfo::on_pushButton_clicked()
{

}

