#include "QCharacterWidget.h"
#include "QSquarePanelWidget.h"

QCharacterWidget::QCharacterWidget(int id) : id(id) {
    setAutoFillBackground(true);
    moveSpeed = DEFAULT_MOVE_SPEED;
}

void QCharacterWidget::setWidth(int w) {
    this->w = w;
}

void QCharacterWidget::setHeight(int h) {
    this->h = h;
}

void QCharacterWidget::setSize(int w, int h) {
    this->w = w;
    this->h = h;
}

void QCharacterWidget::setSize(const QSize &size) {
    w = size.width();
    h = size.height();
}

void QCharacterWidget::spawn(const QPoint &pos) {
    setGeometry(pos.x(), pos.y(), w, h);
    character.load(QString("%1%2.png").arg(FileConstants::CHARACTER_URL).arg(id + 1));
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(character.scaled(width(), height())));
    setPalette(palette);
    show();

    moveTimer = startTimer(10);
}

void QCharacterWidget::timerEvent(QTimerEvent *event) {
    if (event->timerId() == moveTimer) {
        if (--notMoveCnt == 0) {
            speedX = speedY = 0;
        }
        if (speedX != 0 || speedY != 0) {
            int nextX = x() + speedX;
            int nextY = y() + speedY;
            constrainAndTryActivate(nextX, nextY);
            QWidget::move(nextX, nextY);
        } else {
            notMoveCnt = 5;
        }
    }
}

void QCharacterWidget::moveUp() {
    speedY = -moveSpeed;
}

void QCharacterWidget::moveDown() {
    speedY = moveSpeed;
}

void QCharacterWidget::moveLeft() {
    speedX = -moveSpeed;
}

void QCharacterWidget::moveRight() {
    speedX = moveSpeed;
}

void QCharacterWidget::dash(const QPoint &targetPos) {
    QPoint centerPos = QPoint(targetPos.x() - width() / 2, targetPos.y() - height() / 2);
    if (!QSquarePanelWidget::getInstance()->existsSquare(centerPos))
        QWidget::move(centerPos);
    emit moveTo(id, center());
}

QCharacterWidget::MoveMode QCharacterWidget::getMoveMode() const {
    return moveMode;
}

void QCharacterWidget::startDash(int id) {
    if (this->id == id) {
        moveMode = FLASH;
        QTimer::singleShot(5000, this, [&]() {
            moveMode = MoveMode::COMMON;
        });
    }
}

void QCharacterWidget::move(Direction direction) {
    if (moveMode == FROZEN) return;
    switch (direction) {
        case Direction::Up:
            moveUp();
            break;
        case Direction::Down:
            moveDown();
            break;
        case Direction::Left:
            moveLeft();
            break;
        case Direction::Right:
            moveRight();
            break;
        case Direction::None:
            break;
    }
    emit moveTo(id, center());
}

void QCharacterWidget::constrainAndTryActivate(int &x, int &y) {
    QPoint nextCenter = QPoint(x + width() / 2, y + height() / 2);
    if (QSquarePanelWidget::getInstance()->existsSquare(nextCenter)) {
        QSquarePanelWidget::getInstance()->tryActivate(id, nextCenter);
        x = pos().x();
        y = pos().y();
    } else {
        x = qBound(0, x, 1960 - w);
        y = qBound(0, y, 1080 - h);
    }
}

QPoint QCharacterWidget::center() const {
    return QPoint(pos().x() + width() / 2, pos().y() + height() / 2);
}

void QCharacterWidget::setMoveMode(MoveMode moveMode) {
    this->moveMode = moveMode;
}

