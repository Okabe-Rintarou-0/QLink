#include "QCharacterWidget.h"

QCharacterWidget::QCharacterWidget(int id): id(id) {
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

void QCharacterWidget::setSize(QSize size) {
    w = size.width();
    h = size.height();
}

void QCharacterWidget::spawn() {
    character.load(QString("%1%2.png").arg(FileConstants::CHARACTER_URL).arg(1));
    QPalette palette;
    setGeometry(200, 200, w, h);
    palette.setBrush(backgroundRole(), QBrush(character.scaled(width(), height())));
    setPalette(palette);
}

void QCharacterWidget::moveUp() {
    int nextX = x();
    int nextY = y() - moveSpeed;
    constrainPos(nextX, nextY);
    QWidget::move(nextX, nextY);
}

void QCharacterWidget::moveDown() {
    int nextX = x();
    int nextY = y() + moveSpeed;
    constrainPos(nextX, nextY);
    QWidget::move(nextX, nextY);
}

void QCharacterWidget::moveLeft() {
    int nextX = x() - moveSpeed;
    int nextY = y();
    constrainPos(nextX, nextY);
    QWidget::move(nextX, nextY);
}

void QCharacterWidget::moveRight() {
    int nextX = x() + moveSpeed;
    int nextY = y();
    constrainPos(nextX, nextY);
    QWidget::move(nextX, nextY);
}

void QCharacterWidget::dash(const QPoint &targetPos) {
    QPoint centerPos = QPoint(targetPos.x() - width() / 2, targetPos.y() - height() / 2);
    QWidget::move(centerPos);
}

QCharacterWidget::MoveMode QCharacterWidget::getMoveMode() const {
    return moveMode;
}

void QCharacterWidget::startDash(int id) {
    if (this->id == id) {
        moveMode = FLASH;
        QTimer::singleShot(5000, this, [&](){
            moveMode = MoveMode::COMMON;
        });
    }
}

void QCharacterWidget::move(Direction direction){
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

void QCharacterWidget::constrainPos(int &x, int &y) {
    x = qBound(0, x, 1960 - w);
    y = qBound(0, y, 1080 - h);
}

QPoint QCharacterWidget::center() const {
    return QPoint(pos().x() + width() / 2, pos().y() + height() / 2);
}

void QCharacterWidget::setMoveMode(MoveMode moveMode) {
    this->moveMode = moveMode;
}

