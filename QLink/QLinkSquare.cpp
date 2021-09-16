#include "QLinkSquare.h"
#include "QSquareImageManager.h"
QLinkSquare::QLinkSquare()
{
    widget = new QWidget;
    widget->setAutoFillBackground(true);
    //widget->setStyleSheet("background-color:black;");
}

QLinkSquare::~QLinkSquare()
{
    delete widget;
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
    QImage icon = QSquareImageManager::getInstance()->getIcon(iconIndex);
    QPalette palette;
    palette.setBrush(widget->backgroundRole(), QBrush(icon.scaled(QSize(w, h))));
    widget->setPalette(palette);
}
