#include "QCharacterWidget.h"

QCharacterWidget::QCharacterWidget() {
    setAutoFillBackground(true);
    moveSpeed = DEFAULT_MOVE_SPEED;
}

QCharacterWidget::QCharacterWidget(QWidget *parent) : QWidget(parent) {
    QCharacterWidget();
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
    move(nextX, nextY);
}

void QCharacterWidget::moveDown() {
    int nextX = x();
    int nextY = y() + moveSpeed;
    constrainPos(nextX, nextY);
    move(nextX, nextY);
}

void QCharacterWidget::moveLeft() {
    int nextX = x() - moveSpeed;
    int nextY = y();
    constrainPos(nextX, nextY);
    move(nextX, nextY);
}

void QCharacterWidget::moveRight() {
    int nextX = x() + moveSpeed;
    int nextY = y();
    constrainPos(nextX, nextY);
    move(nextX, nextY);
}

void QCharacterWidget::constrainPos(int &x, int &y) {
    x = qBound(0, x, 1960 - w);
    y = qBound(0, y, 1080 - h);
}

QPoint QCharacterWidget::center() {
    return QPoint(pos().x() + width() / 2, pos().y() + height() / 2);
}

const float QCharacterWidget::ADJUST_K = 1.2;
