#ifndef QLINKGAMECONTROLLER_H
#define QLINKGAMECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QTimerEvent>

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

    static QLinkGameController *instance;

    QLinkGameController();

    ~QLinkGameController();

    void startCountDown();

    void countDown();

protected:
    void timerEvent(QTimerEvent *event) override;

signals:
    void timeChanged(int sec);
    void scoreChanged(const QString &);
    void gameOver(const QString &);
};

#endif // QLINKGAMECONTROLLER_H
