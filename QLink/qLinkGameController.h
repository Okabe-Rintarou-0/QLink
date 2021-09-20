#ifndef QLINKGAMECONTROLLER_H
#define QLINKGAMECONTROLLER_H
#include <QObject>
#include <QDebug>

class QLinkGameController: public QObject
{
    Q_OBJECT
public:
    static QLinkGameController *getInstance();
    void reset();
    void addScore(int increament);
private:
    int score;
    static QLinkGameController *instance;
    QLinkGameController();
    ~QLinkGameController();
signals:
    void scoreChanged(const QString &);
};

#endif // QLINKGAMECONTROLLER_H
