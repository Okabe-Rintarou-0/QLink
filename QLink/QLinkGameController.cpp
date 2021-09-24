#include "QLinkGameController.h"

QLinkGameController::~QLinkGameController() {
    delete instance;
}

QLinkGameController::QLinkGameController() {
    instance = nullptr;
    score = 0;
    restTime = 0;
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
    if (restTime % 5 == 0) {
        formJewel();
    }
}

QLinkGameItem *QLinkGameController::getJewel(int category) {
    switch (category) {
        case 0:
            qDebug() << "Time" << endl;
            return new TimeJewel;
        case 1:
            qDebug() << "Hint" << endl;
            return new HintJewel;
        case 2:
            qDebug() << "Flash" << endl;
            return new FlashJewel;
        case 3:
            qDebug() << "Shuffle" << endl;
            return new ShuffleJewel;
    }
    return nullptr;
}

///Form pos need to be optimized
void QLinkGameController::formJewel() {
    int category = RandomUtil::randRange(0, 3);
    QLinkGameItem *jewel = getJewel(category);

    QSize size = QSquarePanelWidget::getInstance()->size();
    QPoint pos = QSquarePanelWidget::getInstance()->pos();
    int minX = pos.x(), maxX = pos.x() + size.width();
    int minY = pos.y(), maxY = pos.y() + size.height();
    int x, y;
    bool valid;
    do {
        if (RandomUtil::randRange(0, 1)) {
            x = RandomUtil::randRange(50, minX - 50);
        }
        else
            x = RandomUtil::randRange(maxX + 50, 1910);
        if (RandomUtil::randRange(0, 1)) {
            y = RandomUtil::randRange(50, minY - 50);
        }
        else
            y = RandomUtil::randRange(maxY + 50, 1030);

        valid = true;
        for (QLinkGameItem *jewel : jewels) {
            QPoint thisPos = jewel->pos();
            int diffX = thisPos.x() - x;
            int diffY = thisPos.y() - y;
            if (diffX * diffX + diffY * diffY <= 25)
                valid = false;
        }
    } while(!valid);
    QApplication::connect(jewel, &QLinkGameItem::picked, this, [=](){
        jewels.remove(jewel);
    });
    jewels.insert(jewel);
    emit formJewel(jewel, QPoint(x, y));
}

void QLinkGameController::startCountDown() {
    countDownTimer = startTimer(1000, Qt::TimerType::PreciseTimer);
}

void QLinkGameController::timerEvent(QTimerEvent *event) {
    if (event->timerId() == countDownTimer) {
        countDown();
    }
}

void QLinkGameController::addTime(int sec) {
    restTime += sec;
    emit timeChanged(restTime);
}

QLinkGameController *QLinkGameController::instance;
