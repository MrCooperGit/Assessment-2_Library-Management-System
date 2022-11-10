#ifndef EMPLOYEEINFO_H
#define EMPLOYEEINFO_H

#include <QWidget>

namespace Ui {
class employeeinfo;
}

class employeeinfo : public QWidget
{
    Q_OBJECT

public:
    explicit employeeinfo(QWidget *parent = nullptr);
    ~employeeinfo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::employeeinfo *ui;
};

#endif // EMPLOYEEINFO_H
