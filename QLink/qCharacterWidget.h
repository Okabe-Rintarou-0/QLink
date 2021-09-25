#ifndef QCHARACTERWIDGET_H
#define QCHARACTERWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include "FileConstants.h"
#include "DirectionUtil.h"

typedef DirectionUtil::Direction Direction;
class QCharacterWidget : public QWidget {
    Q_OBJECT
public:
    QCharacterWidget(int id);

    enum MoveMode { COMMON, FLASH, FROZEN };

    void spawn();

    void setWidth(int w);

    void setHeight(int h);

    void setSize(int w, int h);

    void setSize(QSize size);

    void move(Direction direction);

    void setMoveMode(MoveMode);

    QPoint center() const;

    void dash(const QPoint &targetPos);

    MoveMode getMoveMode() const;

private:
    QImage character;
    int id;
    int w;
    int h;
    int moveSpeed;

    MoveMode moveMode = FLASH;

    static constexpr int DEFAULT_MOVE_SPEED = 12;

    void constrainPos(int &x, int &y);

    void moveUp();

    void moveDown();

    void moveLeft();

    void moveRight();

public slots:
    void startDash(int id);

signals:
    void moveTo(int, const QPoint &);
};

#endif // QCHARACTERWIDGET_H
