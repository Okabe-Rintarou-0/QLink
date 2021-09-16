#ifndef QSQUAREPANELWIDGET_H
#define QSQUAREPANELWIDGET_H
#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include "QLinkSquare.h"
class QSquarePanelWidget : public QWidget
{
private:
    //height
    int h;
    //width
    int w;
    static const int DEFAULT_H = 10;
    static const int DEFAULT_W = 20;
    QVector<QVector<QLinkSquare *>> squares;
    QGridLayout* gridLayout;

    void renderSquares();
    void setUpGridLayout();
public:
    QSquarePanelWidget();
    ~QSquarePanelWidget();
    void setSize(int h, int w);
    void render();
    void clear();
    void resizeAndRender(int w, int h);
};
#endif // QSQUAREPANELWIDGET_H
