#include "qLinkGameController.h"

QLinkGameController::~QLinkGameController()
{
    delete instance;
}

QLinkGameController::QLinkGameController()
{
    instance = nullptr;
    score = 0;
}

QLinkGameController *QLinkGameController::getInstance()
{
    if(instance == nullptr)
        instance = new QLinkGameController;
    return instance;
}

void QLinkGameController::reset()
{
    score = 0;
    emit scoreChanged("分数: " + QString::number(score));
}

void QLinkGameController::addScore(int increament)
{
    score += increament;
    emit scoreChanged("分数: " + QString::number(score));
}

QLinkGameController *QLinkGameController::instance;
