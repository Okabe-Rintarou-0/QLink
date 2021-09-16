#ifndef QLINKSQUARE_H
#define QLINKSQUARE_H
#include <QPushButton>
#include <QImage>
class QLinkSquare
{
private:
    QWidget *widget;
    int bonus;
    int w;
    int h;
public:
    void setBonus(int bonus);
    void setIcon(int iconIndex);
    void setSize(int w, int h);
    QLinkSquare();
    ~QLinkSquare();
    QWidget *getWidget();
};
#endif // QLINKSQUARE_H
