#ifndef QLINKSQUARE_H
#define QLINKSQUARE_H

#include <QPushButton>
#include <QImage>
#include <QLabel>

class QLinkSquare {
private:
    QWidget *widget;
    QLabel *bonusLabel;
    QImage icon;
    static const QColor DEFAULT_BORDER_COLOR;
    static const QColor DEFAULT_ACTIVATE_BORDER_COLORS[2];
    static const QColor DEFAULT_HIGHLIGHT_BORDER_COLOR;
    int bonus;
    int iconIndex;
    int w;
    int h;
    bool activated;
public:
    int getBonus() const;

    void setBonus(int bonus);

    void renderIcon();

    void setIcon(int iconIndex);

    void setAndRenderIcon(int iconIndex, int scores);

    void setSize(int w, int h);

    void activate(int idx);

    void highlight();

    void reset();

    bool isActivated() const;

    int getIconIndex() const;

    bool equals(QLinkSquare *other) const;

    void clear();

    QLinkSquare();

    ~QLinkSquare();

    QWidget *getWidget();
};

#endif // QLINKSQUARE_H
