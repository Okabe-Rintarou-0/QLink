#include "qLinkSquare.h"
#include "qSquareImageManager.h"
#include "ImageUtil.h"
#include "QStyleSheetBuilder.h"
QLinkSquare::QLinkSquare()
{
    activated = false;
    widget = new QWidget;
    widget->setAutoFillBackground(true);
}

QLinkSquare::~QLinkSquare()
{
    //delete widget;
}

void QLinkSquare::setBonus(int bonus)
{
    this->bonus = bonus;
}

QWidget *QLinkSquare::getWidget()
{
    return widget;
}

void QLinkSquare::setSize(int w, int h)
{
    this->w = w;
    this->h = h;
}

void QLinkSquare::setIcon(int iconIndex)
{
    this->iconIndex = iconIndex;
    icon = QSquareImageManager::getInstance()->getIcon(iconIndex);
    icon = icon.scaled(QSize(w, h));
    ImageUtil::setBorder(icon, DEFAULT_BORDER_COLOR, 2);
}

void QLinkSquare::activate()
{
    ImageUtil::setBorder(icon, DEFAULT_ACTIVATE_BORDER_COLOR, 2);
    activated = true;
    renderIcon();
}

void QLinkSquare::renderIcon()
{
    QPalette palette;
    palette.setBrush(widget->backgroundRole(), QBrush(icon));
    widget->setPalette(palette);
}

bool QLinkSquare::isActivated() const
{
    return activated;
}

int QLinkSquare::getIconIndex() const
{
    return iconIndex;
}

bool QLinkSquare::equals(QLinkSquare *other) const
{
    return other != nullptr && other->getIconIndex() == iconIndex;
}

void QLinkSquare::reset()
{
    activated = false;
    ImageUtil::setBorder(icon, DEFAULT_BORDER_COLOR, 2);
    renderIcon();
}

void QLinkSquare::clearIcon()
{
    widget->setPalette(QPalette());
}

const QColor QLinkSquare::DEFAULT_BORDER_COLOR = Qt::gray;
const QColor QLinkSquare::DEFAULT_ACTIVATE_BORDER_COLOR = Qt::black;
