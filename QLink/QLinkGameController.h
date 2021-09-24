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
#include "QSquarePanelWidget.h"

class QLinkGameController : public QObject {
    Q_OBJECT
public:
    static QLinkGameController *getInstance();

    void reset();

    void startGame();

    void addScore(int increament);

    void setRestSquares(int restSquares);

    void addTime(int sec);

private:
    int score;
    int restSquares;
    int restTime;
    int countDownTimer;
    QSet<QLinkGameItem *> jewels;

    static QLinkGameController *instance;

    QLinkGameController();

    ~QLinkGameController();

    void startCountDown();

    void countDown();

    QLinkGameItem *getJewel(int category);

    void formJewel();

protected:
    void timerEvent(QTimerEvent *event) override;

signals:
    void timeChanged(int sec);
    void scoreChanged(const QString &);
    void gameOver(const QString &);
    void formJewel(QLinkGameItem *jewel, const QPoint &pos);
};

#endif // QLINKGAMECONTROLLER_H
