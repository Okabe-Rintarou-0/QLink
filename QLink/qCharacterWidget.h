#ifndef QCHARACTERWIDGET_H
#define QCHARACTERWIDGET_H

#include "FileConstants.h"
#include <QWidget>
#include <QKeyEvent>

class QCharacterWidget : public QWidget {
private:
    QImage character;
    int w;
    int h;
    int moveSpeed;
    static const float ADJUST_K;
    static const int DEFAULT_MOVE_SPEED = 12;

    void constrainPos(int &x, int &y);

public:
    QCharacterWidget();

    QCharacterWidget(QWidget *parent);

    void spawn();

    void setWidth(int w);

    void setHeight(int h);

    void setSize(int w, int h);

    void setSize(QSize size);

    void moveUp();

    void moveDown();

    void moveLeft();

    void moveRight();

    QPoint center() const;
};

#endif // QCHARACTERWIDGET_H
