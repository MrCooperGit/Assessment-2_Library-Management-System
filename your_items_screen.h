#ifndef YOUR_ITEMS_SCREEN_H
#define YOUR_ITEMS_SCREEN_H

#include <QWidget>

namespace Ui {
class your_items_screen;
}

class your_items_screen : public QWidget
{
    Q_OBJECT

public:
    explicit your_items_screen(QWidget *parent = nullptr);
    ~your_items_screen();

private:
    Ui::your_items_screen *ui;
};

#endif // YOUR_ITEMS_SCREEN_H
