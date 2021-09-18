#ifndef QLINKSQUARE_H
#define QLINKSQUARE_H
#include <QPushButton>
#include <QImage>
class QLinkSquare
{
private:
    QWidget *widget;
    QImage icon;
    static const QColor DEFAULT_BORDER_COLOR;
    static const QColor DEFAULT_ACTIVATE_BORDER_COLOR;
    int bonus;
    int iconIndex;
    int w;
    int h;
    bool activated;
public:
    void renderIcon();
    void setBonus(int bonus);
    void setIcon(int iconIndex);
    void setSize(int w, int h);
    void activate();
    void reset();
    bool isActivated() const;
    int getIconIndex() const;
    bool equals(QLinkSquare other) const;
    void clearIcon();
    QLinkSquare();
    ~QLinkSquare();
    QWidget *getWidget();
};
#endif // QLINKSQUARE_H
