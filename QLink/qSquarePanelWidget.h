#ifndef QSQUAREPANELWIDGET_H
#define QSQUAREPANELWIDGET_H
#include <QWidget>
#include <QQueue>
#include <QVector>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
#include "randomUtil.h"
#include "qLinkSquare.h"
class QSquarePanelWidget : public QWidget
{
    Q_OBJECT
private:
    int h;
    int w;
    int squareSpacing;
    static const int DEFUALT_SPACING = 5;
    static const int DEFAULT_H = 10;
    static const int DEFAULT_W = 20;
    static const QColor DEFAULT_LINE_COLOR;
    enum Direction { None = -1, Left = 0, Right, Up, Down };
    const int next[4][2] = {
        {0, -1},
        {0, 1},
        {-1, 0},
        {1, 0}
    };
    QVector<QPoint> path;
    QVector<QVector<QLinkSquare *>> squares;
    QGridLayout* gridLayout;
    QQueue<QPoint> activateQueue;
    QVector<QVector<int>> squareMap;
    QPair<Direction, Direction> getRelativeDirection(QPoint from, QPoint to);
    QPoint toRealPoint(QPoint org);
    void initSquareMap();
    void renderSquares();
    void setUpGridLayout();
    void tryLink();
    bool canPassBy(QPoint p);
    bool outOfBound(QPoint p);
    QPoint moveTowards(QPoint p, Direction direction) const;
    void removeSquareAt(int x, int y);
    inline void removeSquareAt(QPoint);
    void prepareRandom(QMap<int, int> &);
    bool isLinkable(QPoint p1, QPoint p2);
    void searchForLinkPath(bool &found, QPoint curP, QPoint tgtP, int lineCnt, Direction lastDire, QVector<QVector<bool>> &visited);
public:
    QSquarePanelWidget();
    QSquarePanelWidget(QWidget *parent);
    ~QSquarePanelWidget();
    void activate(QPoint fromPos);
    void setSize(int h, int w);
    void render();
    void clear();
    void resizeAndRender(int w, int h);
    QSize getSquareSize();
signals:
    void link(QVector<QPoint> points);
};
#endif // QSQUAREPANELWIDGET_H
