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
    restTime = 120;
    emit scoreChanged("分数: " + QString::number(score));
    emit timeChanged(restTime);
}

void QLinkGameController::addScore(int increament) {
    score += increament;
    emit scoreChanged("分数: " + QString::number(score));
}

void QLinkGameController::setRestSquares(int restSquares) {
    this->restSquares = restSquares;
    if (this->restSquares == 0) {
        emit gameOver("方块均已被消除，游戏结束！");
    }
}

void QLinkGameController::startGame() {
    reset();
    startCountDown();
    emit timeChanged(restTime);
}

void QLinkGameController::countDown() {
    emit timeChanged(--restTime);
    if (restTime == 0) {
        emit gameOver("超时！游戏结束！");
        killTimer(countDownTimer);
    }
}

void QLinkGameController::startCountDown() {
    countDownTimer = startTimer(1000, Qt::TimerType::PreciseTimer);
}

void QLinkGameController::timerEvent(QTimerEvent *event) {
    if (event->timerId() == countDownTimer) {
        countDown();
    }
}

QLinkGameController *QLinkGameController::instance;
