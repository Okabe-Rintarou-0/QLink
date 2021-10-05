#ifndef QLINKGAMECONTROLLER_H
#define QLINKGAMECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QSet>
#include <QTimerEvent>
#include "RandomUtil.h"
#include "QLinkGameItem.h"
#include "Jewels.h"
#include "QLinkArchive.h"
#include "QSquarePanelWidget.h"
#include "QCharacterManager.h"

typedef QLinkGameItem::JewelType JewelType;

class QLinkGameController : public QObject {
    Q_OBJECT
public:
    static QLinkGameController *getInstance();

    void reset();

    void startGame();

    void addScore(int increament);

    void setRestSquares(int restSquares);

    void addTime(int sec);

    void pauseGame();

    void continueGame();

    void endGame();

    void pauseOrContinue();

    void loadFromArchive(const QGlobalInfo &globalInfo);

    void loadFromArchive(const QGameItemInfo &gameItemInfo);

    QGameItemInfo getGameItemInfo() const;

    QGlobalInfo getGlobalInfo() const;

private:
    bool paused = true;
    int score;
    int restSquares;
    int restTime;
    int countDownTimer;
    QSet<QLinkGameItem *> jewels;

    static QLinkGameController *instance;

    QLinkGameController();

    ~QLinkGameController();

    QPoint getRandomFormPoint();

    void startCountDown();

    void countDown();

    QLinkGameItem *getJewel(JewelType jewelType);

    void formJewel();

    void formJewel(JewelType jewelType, const QPoint &pos);

protected:
    void timerEvent(QTimerEvent *event) override;

signals:
    void timeChanged(int sec);

    void scoreChanged(const QString &);

    void gameOver(const QString &);

    void formJewel(QLinkGameItem *jewel, const QPoint &pos);
};

#endif // QLINKGAMECONTROLLER_H
