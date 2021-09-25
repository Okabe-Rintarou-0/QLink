#ifndef QSQUAREPANELWIDGET_H
#define QSQUAREPANELWIDGET_H

#include <QWidget>
#include <QQueue>
#include <QVector>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
#include <QTimer>
#include "QLinkGameController.h"
#include "RandomUtil.h"
#include "QLinkArchive.h"
#include "QLinkSquare.h"
#include "DirectionUtil.h"

typedef DirectionUtil::Direction Direction;
class QSquarePanelWidget : public QWidget {
    Q_OBJECT
private:
    enum RunMode { COMMON, HINT } runMode = COMMON;
    int h;
    int w;
    int squareSpacing;
    int restSquares;
    static const QPair<QPoint, QPoint> INVALID_PAIR;
    static const int DEFAULT_SPACING = 5;
    static const int DEFAULT_H = 10;
    static const int DEFAULT_W = 20;
    static const QColor DEFAULT_LINE_COLOR;
    const int next[4][2] = {
            {0,  -1},
            {0,  1},
            {-1, 0},
            {1,  0}
    };
    QVector <QPoint> path;
    QVector <QVector<QLinkSquare *>> squares;
    QGridLayout *gridLayout;
    QQueue <QPoint> activateQueue;
    QVector <QVector<int>> squareMap;
    QMap<int, QVector<QPoint>> squarePosMap;

    QPair <Direction, Direction> getRelativeDirection(const QPoint &from, const QPoint &to) const;

    QPoint toRealPoint(const QPoint &org) const;

    QPair<QPoint, QPoint> linkablePairCache = qMakePair(QPoint(-1, -1), QPoint(-1, -1));

    QSquarePanelWidget();

    void highlightAt(const QPoint &p);

    void updateCache(const QPoint &p1, const QPoint &p2);

    void initSquareMap();

    void renderSquares();

    void setUpGridLayout();

    bool searchLinkabelSquare();

    void hintNext();

    void tryLink();

    bool canPassBy(const QPoint &p) const;

    bool outOfBound(const QPoint &p) const;

    QPoint moveTowards(const QPoint &p, Direction direction) const;

    void removeSquareAt(int x, int y);

    inline void removeSquareAt(QPoint);

    void prepareRandom(QMap<int, int> &);

    bool isLinkable(const QPoint &p1, const QPoint &p2) const;

    void searchForLinkPath(bool &found, QPoint curP, QPoint tgtP, int lineCnt, Direction lastDire,
                           QVector <QVector<bool>> &visited);

    void cancelLink(const QPoint &p1, const QPoint &p2);

    void link(const QPoint &p1, const QPoint &p2);

    bool checkVertical(const QPoint &p1, const QPoint &p2) const;

    bool checkHorizontal(const QPoint &p1, const QPoint &p2) const;

    bool checkStraightLine(const QPoint &p1, const QPoint &p2) const;

    bool checkOneCorner(const QPoint &p1, const QPoint &p2) const;

    bool checkTwoCorner(const QPoint &p1, const QPoint &p2) const;

    void initSquarePosMap();

    bool existsLinkableSquare();

    QPoint toMapPoint(const QPoint &p) const;

    QPoint toMapPoint(int x, int y) const;

    static QSquarePanelWidget *instance;
public:
    static QSquarePanelWidget *getInstance();

    ~QSquarePanelWidget();

    void activate(const QPoint &fromPos);

    void setSize(int h, int w);

    void render();

    void clear();

    void resizeAndRender(int w, int h);

    QSize getSquareSize() const;

    void shuffle();

    QSquarePanelInfo getSquarePanelInfo() const;

    void startHint();
signals:
    void link(const QString &status);
};

#endif // QSQUAREPANELWIDGET_H
