#include "QLinkGameController.h"

QLinkGameController::~QLinkGameController() {
    delete instance;
}

QLinkGameController::QLinkGameController() {
    instance = nullptr;
    score = 0;
}

QLinkGameController *QLinkGameController::getInstance() {
    if (instance == nullptr)
        instance = new QLinkGameController;
    return instance;
}

void QLinkGameController::reset() {
    score = 0;
    emit scoreChanged("分数: " + QString::number(score));
}

void QLinkGameController::addScore(int increament) {
    score += increament;
    emit scoreChanged("分数: " + QString::number(score));
}

void QLinkGameController::setRestSquares(int restSquares)
{
    this->restSquares = restSquares;
    if (this->restSquares == 0)
    {
        emit gameOver("方块均已被消除，游戏结束！");
    }
}

void QLinkGameController::startGame()
{
    reset();
}

QLinkGameController *QLinkGameController::instance;
