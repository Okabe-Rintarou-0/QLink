#ifndef QUNITTEST_H
#define QUNITTEST_H
#include <QtTest/QtTest>
#include "QLinkSquare.h"
#include "QLinkArchive.h"
#include "QSquarePanelWidget.h"
class QSquarePanelWidget;

class QUnitTest: public QObject
{
    Q_OBJECT
private:
    QSquarePanelWidget *squarePanel;

    void init();

    QPoint mp(int x, int y) const;
private slots:
    void testHorizontal();

    void testVertical();

    void testStraightLine();

    void testOneCorner();

    void testTwoCorner();

    void testIsLinkable();

public:
    QUnitTest();
};

#endif // QUNITTEST_H
