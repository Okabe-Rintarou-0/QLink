#include "qSquarePanelWidget.h"
#include <QDebug>
#include <QDateTime>
QSquarePanelWidget::QSquarePanelWidget()
{
    h = DEFAULT_H;
    w = DEFAULT_W;
    squareSpacing = DEFUALT_SPACING;
    gridLayout = new QGridLayout;
}

QSquarePanelWidget::QSquarePanelWidget(QWidget *parent): QWidget(parent)
{
    QSquarePanelWidget();
}

QSquarePanelWidget::~QSquarePanelWidget()
{
    clear();
}

void QSquarePanelWidget::setSize(int w, int h)
{
    this->w = w;
    this->h = h;
}

void QSquarePanelWidget::prepareRandom(QMap<int, int> & randomIconIdxToNum)
{
    int totalNum = w * h / 2;
    int randomSeed = QDateTime::currentDateTime().toTime_t();
    randomSeed = RandomUtil::randRange(0, randomSeed) + randomSeed;
    srand(randomSeed);
    int randomNum = RandomUtil::randRange(totalNum / 8, totalNum / 16);
    randomNum = qMin(randomNum, 40);
    int iconNum = totalNum / randomNum;
    int rest = totalNum % randomNum;
    for (int i = 0; i < randomNum; ++i)
    {
        int randomIdx;
        do
        {
            randomIdx = RandomUtil::randRange(1, 40);
        } while(randomIconIdxToNum.contains(randomIdx));
        int additional = 0;
        if (rest)
        {
            additional = RandomUtil::randRange(1, rest);
            rest -= additional;
        }
        randomIconIdxToNum.insert(randomIdx, (iconNum + additional) * 2);
    }
}

QPair<QSquarePanelWidget::Direction, QSquarePanelWidget::Direction> QSquarePanelWidget::getRelativeDirection(QPoint from, QPoint to)
{
    QPair<Direction, Direction> relativeDirection;
    QPoint diff = to - from;
    if (diff.x() < 0)
        relativeDirection.first = Up;
    else if (diff.x() > 0)
        relativeDirection.first = Down;
    else
        relativeDirection.first = None;
    if (diff.y() < 0)
        relativeDirection.second = Left;
    else if(diff.y() > 0)
        relativeDirection.second = Right;
    else
        relativeDirection.second = None;
    return relativeDirection;
}
void QSquarePanelWidget::renderSquares()
{
    QMap<int, int> randomIconIdxToNum;
    prepareRandom(randomIconIdxToNum);

    for (int i = 0; i < h; ++i)
    {
        squares.push_back(QVector<QLinkSquare *>(w));
        for (int j = 0; j < w; ++j)
        {
            QLinkSquare *square = new QLinkSquare;
            int restHeight = (800 - (h - 1) * squareSpacing);
            int randomId = RandomUtil::randRange(0, randomIconIdxToNum.size() - 1);
            auto it = randomIconIdxToNum.begin();
            for (int i = 0; i < randomId; ++i, ++it);
            square->setSize(restHeight / h, restHeight / h);
            square->setIcon(it.key());
            square->renderIcon();
            squares[i][j] = square;
            gridLayout->addWidget(square->getWidget(), i, j, 1, 1);
            --it.value();
            if (it.value() == 0)
                randomIconIdxToNum.remove(it.key());
        }
    }
}

void QSquarePanelWidget::initSquareMap()
{
    squareMap.clear();
    for(int i = 0; i <= h + 1; ++i)
    {
        QVector<int> row(w + 2, 0);
        squareMap.push_back(row);
    }

    for(int i = 1; i <= h; ++i)
    {
        for(int j = 1; j <= w; ++j)
        {
            squareMap[i][j] = squares[i - 1][j - 1]->getIconIndex();
        }
    }
}

void QSquarePanelWidget::activate(QPoint fromPos)
{
    int fromX = fromPos.x();
    int fromY = fromPos.y();
    int col = (fromX - pos().x()) / ((800 - (h - 1) * squareSpacing) / h + squareSpacing);
    int row = (fromY - pos().y()) / ((800 - (h - 1) * squareSpacing) / h + squareSpacing);

    if (0 <= row && row < h && 0 <= col && col < w)
    {
        QLinkSquare *targetSquare = squares[row][col];
        if (targetSquare != nullptr && !targetSquare->isActivated())
        {
            targetSquare->activate();
            activateQueue.enqueue(QPoint(row, col));
            tryLink();
        }
    }
}

void QSquarePanelWidget::removeSquareAt(int x, int y)
{
    QLinkSquare *targetSquare = squares[x][y];
    if (targetSquare != nullptr)
    {
//        targetSquare->getWidget()->setParent(nullptr);
//        gridLayout->removeWidget(targetSquare->getWidget());
//        delete targetSquare;
        targetSquare->clearIcon();
        squares[x][y] = nullptr;
        squareMap[x + 1][y + 1] = 0;
    }
}

void QSquarePanelWidget::removeSquareAt(QPoint p)
{
    removeSquareAt(p.x(), p.y());
}

void QSquarePanelWidget::setUpGridLayout()
{
    gridLayout->setSpacing(squareSpacing);
    gridLayout->setMargin(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
}

void QSquarePanelWidget::render()
{
    renderSquares();
    initSquareMap();
    setUpGridLayout();
    setLayout(gridLayout);
    setGeometry(980 - (800 * w / h) / 2, 100, 800 * w / h, 800);
    QPainter painter;
}

void QSquarePanelWidget::clear()
{
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (squares[i][j] == nullptr) continue;
            gridLayout->removeWidget(squares[i][j]->getWidget());
            squares[i][j]->getWidget()->setParent(nullptr);
            delete squares[i][j];
        }
    }
    squares.clear();
}

void QSquarePanelWidget::resizeAndRender(int w, int h)
{
    clear();
    setSize(w, h);
    render();
}

QPoint QSquarePanelWidget::moveTowards(QPoint p, Direction direction) const
{
    return QPoint(p.x() + next[direction][0], p.y() + next[direction][1]);
}

bool QSquarePanelWidget::canPassBy(QPoint p)
{
    return !outOfBound(p) && squareMap[p.x()][p.y()] == 0;
}

bool QSquarePanelWidget::outOfBound(QPoint p)
{
    return p.x() < 0 || p.x() > h + 1 || p.y() < 0 || p.y() > w + 1;
}

void QSquarePanelWidget::searchForLinkPath(bool &found, QPoint curP, QPoint tgtP, int lineCnt, Direction lastDire, QVector<QVector<bool>> &visited)
{
    if (lineCnt > 3) return;
    if (curP == tgtP)
    {
        path.push_back(tgtP);
        found = true;
        return;
    }
    QPair<Direction, Direction> relativeDirection = getRelativeDirection(curP, tgtP);

    QVector<Direction> directions = {Left, Right, Up, Down};

    if(relativeDirection.first != None)
        qSwap(directions[0], directions[relativeDirection.first]);

    if(relativeDirection.second != None)
        qSwap(directions[1], directions[relativeDirection.second]);

    Direction curDire;
    QPoint nextP;
    int curCnt;

    for (int i = 0; i < 4; ++i)
    {
        curDire = directions[i];
        curCnt = curDire != lastDire ? lineCnt + 1 : lineCnt;
        nextP = moveTowards(curP, curDire);
        if ((!canPassBy(nextP) || visited[nextP.x()][nextP.y()]) && nextP != tgtP) continue;
        if (curDire != lastDire)
            path.push_back(curP);
        visited[nextP.x()][nextP.y()] = true;
        searchForLinkPath(found, nextP, tgtP, curCnt, curDire, visited);
        if (found) return;
        if (curDire != lastDire)
            path.pop_back();
        visited[nextP.x()][nextP.y()] = false;
    }
}

bool QSquarePanelWidget::isLinkable(QPoint p1, QPoint p2)
{
    QLinkSquare *firstSquare = squares[p1.x()][p1.y()];
    QLinkSquare *secondSquare = squares[p2.x()][p2.y()];
    bool found = false;
    if (firstSquare->equals(secondSquare))
    {
        QVector<QVector<bool>> visited(h + 2, QVector<bool>(w + 2, false));
        QPoint from = QPoint(p1.x() + 1, p1.y() + 1);
        QPoint to = QPoint(p2.x() + 1, p2.y() + 1);
        path.clear();
        searchForLinkPath(found, from, to, 0, None, visited);
    }
    return found;
}

QPoint QSquarePanelWidget::toRealPoint(QPoint org)
{
    int rx = pos().x()
            + (800 - (h - 1) * squareSpacing) / (2 * h) * (1 + 2 * (org.y() - 1))
            + (org.y() - 1) * squareSpacing;
    int ry = pos().y()
            + (800 - (h - 1) * squareSpacing) / (2 * h) * (1 + 2 * (org.x() - 1))
            + (org.x() - 1) * squareSpacing;
    return QPoint(rx, ry);
}

void QSquarePanelWidget::tryLink()
{
    if(activateQueue.size() == 2)
    {
        QPoint first = activateQueue.dequeue();
        QPoint second = activateQueue.dequeue();
        QLinkSquare *firstSquare = squares[first.x()][first.y()];
        QLinkSquare *secondSquare = squares[second.x()][second.y()];
        if (isLinkable(first, second))
        {
//            for (QPoint &p : path) p = toRealPoint(p);
//            emit link(path);
            QLinkGameController::getInstance()->addScore(15);
            removeSquareAt(first);
            removeSquareAt(second);
        }
        else
        {
            firstSquare->reset();
            secondSquare->reset();
        }
    }
}



QSize QSquarePanelWidget::getSquareSize()
{
    int restHeight = (800 - (h - 1) * squareSpacing);
    return QSize(restHeight / h, restHeight / h);
}


