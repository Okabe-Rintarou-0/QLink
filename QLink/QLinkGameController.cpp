#include "QLinkGameController.h"

QLinkGameController::~QLinkGameController() {
    delete instance;
}

QLinkGameController::QLinkGameController() {
    instance = nullptr;
    score = 0;
    restTime = 0;

    QApplication::connect(QSquarePanelWidget::getInstance(), SIGNAL(linked(int, int)), this, SLOT(update(int, int)));
}

QLinkGameController *QLinkGameController::getInstance() {
    if (instance == nullptr)
        instance = new QLinkGameController;
    return instance;
}

void QLinkGameController::init() {
    score = 0;
    restTime = 120;
    emit scoreChanged("分数: " + QString::number(score));
    emit timeChanged(restTime);
    for (QLinkGameItem *jewel:jewels) {
        jewel->setParent(nullptr);
        jewels.remove(jewel);
        delete jewel;
    }
    if (countDownTimer >= 0) {
        killTimer(countDownTimer);
        countDownTimer = -1;
    }
}

void QLinkGameController::clear() {
    if (countDownTimer >= 0) {
        killTimer(countDownTimer);
        countDownTimer = -1;
    }
}

void QLinkGameController::update(int bonus, int restSquares) {
    addScore(bonus);
    setRestSquares(restSquares);
}

void QLinkGameController::endGame(const QString &msg) {
    clear();
    emit gameOver(msg);
}

void QLinkGameController::forceQuit() {
    clear();
}

void QLinkGameController::addScore(int increment) {
    score += increment;
    emit scoreChanged("分数: " + QString::number(score));
}

void QLinkGameController::setScore(int score) {
    this->score = score;
    emit scoreChanged("分数: " + QString::number(score));
}

void QLinkGameController::setRestSquares(int restSquares) {
    this->restSquares = restSquares;
    if (this->restSquares == 0) {
        endGame("方块均已被消除，游戏结束！");
    }
}

void QLinkGameController::loadFromArchive(const QGlobalInfo &globalInfo) {
    setTime(globalInfo.restTime);
    setScore(globalInfo.scores);
    startCountDown();
}

void QLinkGameController::loadFromArchive(const QGameItemInfo &gameItemInfo) {
    for (QJewelInfo jewelInfo: gameItemInfo.jewels) {
        qDebug() << "form jewel " << jewelInfo.jewelType << " " << jewelInfo.pos << endl;
        spawnJewel(jewelInfo.jewelType, jewelInfo.pos);
    }
}

void QLinkGameController::startGame() {
    init();
    startCountDown();
    emit timeChanged(restTime);
}

void QLinkGameController::pauseGame() {
    killTimer(countDownTimer);
    countDownTimer = -1;
    QCharacterManager::getInstance()->frozenAll();
}

void QLinkGameController::continueGame() {
    startCountDown();
    QCharacterManager::getInstance()->unfrozenAll();
}

void QLinkGameController::countDown() {
    emit timeChanged(--restTime);
    if (restTime == 0) {
        endGame("超时了哦！游戏结束！");
    }
    if (restTime % 20 == 0) {
        randomSpawnJewel();
    }
}

void QLinkGameController::pauseOrContinue() {
    paused = !paused;
    if (!paused)
        pauseGame();
    else
        continueGame();
}

QGameItemInfo QLinkGameController::getGameItemInfo() const {
    QGameItemInfo gameItemInfo;
    for (QLinkGameItem *jewel : jewels) {
        gameItemInfo.addJewel(QJewelInfo(jewel->getJewelType(), jewel->pos()));
    }
    return gameItemInfo;
}

QGlobalInfo QLinkGameController::getGlobalInfo() const {
    return QGlobalInfo(restTime, score);
}

QLinkGameItem *QLinkGameController::getJewel(JewelType jewelType) {
    switch (jewelType) {
        case JewelType::TIME:
            qDebug() << "Time" << endl;
            return new TimeJewel;
        case JewelType::HINT:
            qDebug() << "Hint" << endl;
            return new HintJewel;
        case JewelType::FLASH:
            qDebug() << "Flash" << endl;
            return new FlashJewel;
        case JewelType::SHUFFLE:
            qDebug() << "Shuffle" << endl;
            return new ShuffleJewel;
        case JewelType::UNDEFINED:
            return nullptr;
    }
    return nullptr;
}

QPoint QLinkGameController::getRandomSpawnPoint() {
    QSize size = QSquarePanelWidget::getInstance()->size();
    QPoint pos = QSquarePanelWidget::getInstance()->pos();
    int minX = pos.x(), maxX = pos.x() + size.width();
    int minY = pos.y(), maxY = pos.y() + size.height();
    int x, y;
    bool valid = false;
    do {
        if (RandomUtil::randRange(0, 1)) {
            x = RandomUtil::randRange(150, minX - 150);
        } else
            x = RandomUtil::randRange(maxX + 150, 1810);

        y = RandomUtil::randRange(minY, maxY);

        valid = true;
        for (QLinkGameItem *jewel : jewels) {
            QPoint thisPos = jewel->pos();
            int diffX = thisPos.x() - x;
            int diffY = thisPos.y() - y;
            if (diffX * diffX + diffY * diffY <= 25)
                valid = false;
        }
    } while (!valid);
    return QPoint(x, y);
}

void QLinkGameController::randomSpawnJewel() {
    JewelType jewelType = (JewelType) RandomUtil::randRange(0, 3);
    QPoint randomPos = getRandomSpawnPoint();
    spawnJewel(jewelType, randomPos);
}

void QLinkGameController::spawnJewel(JewelType jewelType, const QPoint &pos) {
    QLinkGameItem *jewel = getJewel(jewelType);

    QApplication::connect(jewel, &QLinkGameItem::picked, this, [=]() {
        jewels.remove(jewel);
    });
    jewels.insert(jewel);
    emit spawnJewel(jewel, pos);
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

void QLinkGameController::setTime(int time) {
    restTime = time;
    emit timeChanged(restTime);
}

QLinkGameController *QLinkGameController::instance;
