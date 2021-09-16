#include "QLinkSquare.h"
QLinkSquare::QLinkSquare()
{
    widget = new QWidget;
    widget->setStyleSheet("background-color:black;");
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

