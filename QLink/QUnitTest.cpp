#include "QUnitTest.h"

/***************************************
   1 1 3 4
   2 3
   2 4 3
   4   4
***************************************/

//to simplify
typedef QPoint p;

QUnitTest::QUnitTest() {
    squarePanel = QSquarePanelWidget::getInstance();
}

//to simplify
QPoint QUnitTest::mp(int x, int y) const {
    return squarePanel->toMapPoint(x, y);
}

void QUnitTest::init() {
    QVector<QSquareInfo> squareInfos;

    //row 1
    squareInfos.push_back(QSquareInfo(p(0, 0), 1, 30));
    squareInfos.push_back(QSquareInfo(p(0, 1), 1, 30));
    squareInfos.push_back(QSquareInfo(p(0, 2), 3, 30));
    squareInfos.push_back(QSquareInfo(p(0, 3), 4, 30));

    //row 2
    squareInfos.push_back(QSquareInfo(p(1, 0), 2, 30));
    squareInfos.push_back(QSquareInfo(p(1, 1), 3, 30));

    //row 3
    squareInfos.push_back(QSquareInfo(p(2, 0), 2, 30));
    squareInfos.push_back(QSquareInfo(p(2, 1), 4, 30));
    squareInfos.push_back(QSquareInfo(p(2, 2), 3, 30));

    //row 4
    squareInfos.push_back(QSquareInfo(p(3, 0), 4, 30));
    squareInfos.push_back(QSquareInfo(p(3, 2), 4, 30));

    squarePanel->clear();
    squarePanel->setSize(4, 4);
    squarePanel->renderSquares(squareInfos);
}

void QUnitTest::testHorizontal() {
    init();

    QVERIFY(squarePanel->checkHorizontal(mp(0,0),mp(0,1)));
    QVERIFY(squarePanel->checkHorizontal(mp(3,0),mp(3,2)));

    QVERIFY(!squarePanel->checkHorizontal(mp(0,1),mp(1,1)));
    QVERIFY(!squarePanel->checkHorizontal(mp(0,0),mp(0,0)));
}

void QUnitTest::testVertical() {
    init();

    QVERIFY(squarePanel->checkVertical(mp(1,0),mp(2,0)));
    QVERIFY(squarePanel->checkVertical(mp(2,1),mp(1,1)));

    QVERIFY(!squarePanel->checkVertical(mp(1,0),mp(1,0)));
    QVERIFY(!squarePanel->checkVertical(mp(1,0),mp(1,0)));
}

void QUnitTest::testStraightLine() {
    init();

    QVERIFY(squarePanel->checkStraightLine(p(3,0),p(3,2)));
    QVERIFY(squarePanel->checkStraightLine(p(0,0),p(0,1)));
    QVERIFY(squarePanel->checkStraightLine(p(0,2),p(2,2)));
    QVERIFY(squarePanel->checkStraightLine(p(1,0),p(2,0)));

    QVERIFY(!squarePanel->checkStraightLine(p(0,2),p(1,1)));
    QVERIFY(!squarePanel->checkStraightLine(p(0,0),p(0,0)));
}

void QUnitTest::testOneCorner() {
    init();

    QVERIFY(squarePanel->checkOneCorner(p(3,0),p(2,1)));
    QVERIFY(squarePanel->checkOneCorner(p(3,2),p(2,1)));
    QVERIFY(squarePanel->checkOneCorner(p(0,3),p(3,2)));
    QVERIFY(squarePanel->checkOneCorner(p(0,2),p(1,1)));
    QVERIFY(squarePanel->checkOneCorner(p(2,2),p(1,1)));

    QVERIFY(!squarePanel->checkOneCorner(p(0,3),p(2,1)));
    QVERIFY(!squarePanel->checkOneCorner(p(3,0),p(3,0)));
}

void QUnitTest::testTwoCorner() {
    init();

    QVERIFY(squarePanel->checkTwoCorner(p(0,3),p(2,1)));
    QVERIFY(squarePanel->checkTwoCorner(p(3,0),p(0,3)));

    QVERIFY(!squarePanel->checkTwoCorner(p(0,2),p(2,2)));
    QVERIFY(!squarePanel->checkTwoCorner(p(0,3),p(0,3)));
}

void QUnitTest::testIsLinkable() {
    init();

    QVERIFY(squarePanel->isLinkable(p(0,0),p(0,1)));
    QVERIFY(squarePanel->isLinkable(p(1,0),p(2,0)));
    QVERIFY(squarePanel->isLinkable(p(0,2),p(1,1)));
    QVERIFY(squarePanel->isLinkable(p(2,2),p(1,1)));
    QVERIFY(squarePanel->isLinkable(p(0,3),p(3,0)));
    QVERIFY(squarePanel->isLinkable(p(0,3),p(3,2)));
    QVERIFY(squarePanel->isLinkable(p(3,0),p(2,1)));
    QVERIFY(squarePanel->isLinkable(p(3,2),p(2,1)));
    QVERIFY(squarePanel->isLinkable(p(0,3),p(2,1)));

    QVERIFY(!squarePanel->isLinkable(p(3,3),p(3,3)));
    QVERIFY(!squarePanel->isLinkable(p(0,0),p(0,0)));
    QVERIFY(!squarePanel->isLinkable(p(0,2),p(3,2)));
    QVERIFY(!squarePanel->isLinkable(p(1,1),p(2,1)));
    QVERIFY(!squarePanel->isLinkable(p(0,1),p(0,2)));
    QVERIFY(!squarePanel->isLinkable(p(0,0),p(3,0)));
}

// This is a map without linkable pairs
/***************************************
   1 3 2 5
   5 3 4 6
   2 1 2 1
   6 2 1 4
***************************************/

void QUnitTest::formNotLinkableMap() {
    QVector<QSquareInfo> squareInfos;

    //row 1
    squareInfos.push_back(QSquareInfo(p(0, 0), 1, 30));
    squareInfos.push_back(QSquareInfo(p(0, 1), 4, 30));
    squareInfos.push_back(QSquareInfo(p(0, 2), 2, 30));
    squareInfos.push_back(QSquareInfo(p(0, 3), 5, 30));

    //row 2
    squareInfos.push_back(QSquareInfo(p(1, 0), 5, 30));
    squareInfos.push_back(QSquareInfo(p(1, 1), 3, 30));
    squareInfos.push_back(QSquareInfo(p(1, 2), 4, 30));
    squareInfos.push_back(QSquareInfo(p(1, 3), 6, 30));

    //row 3
    squareInfos.push_back(QSquareInfo(p(2, 0), 2, 30));
    squareInfos.push_back(QSquareInfo(p(2, 1), 1, 30));
    squareInfos.push_back(QSquareInfo(p(2, 2), 2, 30));
    squareInfos.push_back(QSquareInfo(p(2, 3), 1, 30));

    //row 4
    squareInfos.push_back(QSquareInfo(p(3, 0), 6, 30));
    squareInfos.push_back(QSquareInfo(p(3, 1), 2, 30));
    squareInfos.push_back(QSquareInfo(p(3, 2), 1, 30));
    squareInfos.push_back(QSquareInfo(p(3, 3), 4, 30));

    squarePanel->clear();
    squarePanel->setSize(4, 4);
    squarePanel->renderSquares(squareInfos);
}

void QUnitTest::testExistsLinkable() {
    init();

    QVERIFY(squarePanel->existsLinkableSquare());

    formNotLinkableMap();

    QVERIFY(!squarePanel->existsLinkableSquare());
}


