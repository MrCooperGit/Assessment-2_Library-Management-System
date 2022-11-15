#ifndef YOUR_ITEMS_SCREEN_H
#define YOUR_ITEMS_SCREEN_H

#include <QWidget>
#include <QDir>
#include <QMessageBox>

namespace Ui {
class your_items_screen;

    QString getUserId();
}

class your_items_screen : public QWidget
{
    Q_OBJECT

public:
    explicit your_items_screen(QWidget *parent = nullptr);
    ~your_items_screen();

private slots:
    void on_pushButton_catalogue_clicked();

    void on_pushButton_home_clicked();

    void currentDate();

private:
    Ui::your_items_screen *ui;

    QTimer *timer;
};

#endif // YOUR_ITEMS_SCREEN_H
