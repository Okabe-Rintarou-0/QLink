#ifndef QSQUAREPANELWIDGET_H
#define QSQUAREPANELWIDGET_H
#include <QWidget>
#include <QQueue>
#include <QVector>
#include <QGridLayout>
#include <QMap>
#include "randomUtil.h"
#include "qLinkSquare.h"
class QSquarePanelWidget : public QWidget
{
private:
    int h;
    int w;
    int squareSpacing;
    static const int DEFUALT_SPACING = 5;
    static const int DEFAULT_H = 10;
    static const int DEFAULT_W = 20;
    QVector<QVector<QLinkSquare *>> squares;
    QGridLayout* gridLayout;
    QQueue<QPoint> activateQueue;
    void renderSquares();
    void setUpGridLayout();
    void tryLink();
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
};
#endif // QSQUAREPANELWIDGET_H
