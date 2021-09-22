#ifndef QSQUAREPANELWIDGET_H
#define QSQUAREPANELWIDGET_H

#include <QWidget>
#include <QQueue>
#include <QVector>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
#include "QLinkGameController.h"
#include "RandomUtil.h"
#include "QLinkSquare.h"

class QSquarePanelWidget : public QWidget {
    Q_OBJECT
private:
    int h;
    int w;
    int squareSpacing;
    int restSquares;
    static const int DEFAULT_SPACING = 5;
    static const int DEFAULT_H = 10;
    static const int DEFAULT_W = 20;
    static const QColor DEFAULT_LINE_COLOR;
    enum Direction {
        None = -1, Left = 0, Right, Up, Down
    };
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

    void initSquareMap();

    void renderSquares();

    void setUpGridLayout();

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

    void link(QPoint p1, QPoint p2);

    bool checkVertical(const QPoint &p1, const QPoint &p2) const;

    bool checkHorizontal(const QPoint &p1, const QPoint &p2) const;

    bool checkStraightLine(const QPoint &p1, const QPoint &p2) const;

    bool checkOneCorner(const QPoint &p1, const QPoint &p2) const;

    bool checkTwoCorner(const QPoint &p1, const QPoint &p2) const;

    void initSquarePosMap();

    bool existsLinkableSquare();

    QPoint toMapPoint(const QPoint &p) const;

    QPoint toMapPoint(int x, int y) const;

public:
    QSquarePanelWidget();

    QSquarePanelWidget(QWidget *parent);

    ~QSquarePanelWidget();

    void activate(const QPoint &fromPos);

    void setSize(int h, int w);

    void render();

    void clear();

    void resizeAndRender(int w, int h);

    QSize getSquareSize() const;

    void reassign();
signals:
    void link(QVector < QPoint > points);
};

#endif // QSQUAREPANELWIDGET_H
