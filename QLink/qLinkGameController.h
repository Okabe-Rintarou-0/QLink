#ifndef QLINKGAMECONTROLLER_H
#define QLINKGAMECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>

class QLinkGameController : public QObject {
    Q_OBJECT
public:
    static QLinkGameController *getInstance();

    void reset();

    void startGame();

    void addScore(int increament);

    void setRestSquares(int restSquares);

private:
    int score;
    int restSquares;
    static QLinkGameController *instance;

    QLinkGameController();

    ~QLinkGameController();

signals:
    void scoreChanged(const QString &);
    void gameOver(const QString &);
};

#endif // QLINKGAMECONTROLLER_H
