#ifndef QLINKSQUARE_H
#define QLINKSQUARE_H
#include <QPushButton>
#include <QImage>
class QLinkSquare
{
private:
    QWidget *widget;
    int bonus;

public:
    void setBonus(int bonus);
    QLinkSquare();
    ~QLinkSquare();
    QWidget *getWidget();
};
#endif // QLINKSQUARE_H
