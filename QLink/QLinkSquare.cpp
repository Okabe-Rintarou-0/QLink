#include "QLinkSquare.h"
#include "QSquareImageManager.h"
#include "ImageUtil.h"
#include "QStyleSheetBuilder.h"
#include <QDebug>

QLinkSquare::QLinkSquare() {
    activated = false;
    widget = new QWidget;
    bonusLabel = new QLabel(widget);
    widget->setAutoFillBackground(true);
}

QLinkSquare::~QLinkSquare() {
    bonusLabel->setParent(nullptr);
    delete bonusLabel;
}

int QLinkSquare::getBonus() const {
    return bonus;
}

void QLinkSquare::setBonus(int bonus) {
    this->bonus = bonus;
    bonusLabel->setFont(QFont("Microsoft YaHei", w / 10, w / 1.5));
    bonusLabel->setGeometry(0, 0, w / 3, h / 6);
    bonusLabel->raise();
    bonusLabel->setText(QString::number(bonus));
}

QWidget *QLinkSquare::getWidget() {
    return widget;
}

void QLinkSquare::setSize(int w, int h) {
    this->w = w;
    this->h = h;
}

void QLinkSquare::setIcon(int iconIndex) {
    this->iconIndex = iconIndex;
    icon = QSquareImageManager::getInstance()->getIcon(iconIndex);
    icon = icon.scaled(QSize(w, h));
    ImageUtil::setBorder(icon, DEFAULT_BORDER_COLOR, 2);
}

void QLinkSquare::activate(int idx) {
    ImageUtil::setBorder(icon, DEFAULT_ACTIVATE_BORDER_COLORS[idx], 2);
    activated = true;
    renderIcon();
}

void QLinkSquare::highlight() {
    ImageUtil::setBorder(icon, DEFAULT_HIGHLIGHT_BORDER_COLOR, 2);
    renderIcon();
}

void QLinkSquare::renderIcon() {
    QPalette palette;
    palette.setBrush(widget->backgroundRole(), QBrush(icon));
    widget->setPalette(palette);
}

bool QLinkSquare::isActivated() const {
    return activated;
}

int QLinkSquare::getIconIndex() const {
    return iconIndex;
}

bool QLinkSquare::equals(QLinkSquare *other) const {
    return other != nullptr && other->getIconIndex() == iconIndex;
}

void QLinkSquare::reset() {
    activated = false;
    ImageUtil::setBorder(icon, DEFAULT_BORDER_COLOR, 2);
    renderIcon();
}

void QLinkSquare::clear() {
    widget->setPalette(QPalette());
    bonusLabel->clear();
}

void QLinkSquare::setAndRenderIcon(int iconIndex, int bonus) {
    setIcon(iconIndex);
    setBonus(bonus);
    renderIcon();
}

const QColor QLinkSquare::DEFAULT_HIGHLIGHT_BORDER_COLOR = Qt::red;
const QColor QLinkSquare::DEFAULT_BORDER_COLOR = Qt::gray;
const QColor QLinkSquare::DEFAULT_ACTIVATE_BORDER_COLORS[2] = {Qt::black, QColor("#9400d3")};
