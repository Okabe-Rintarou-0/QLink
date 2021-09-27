#include "QSquarePanelWidget.h"
#include <QDebug>
#include <QDateTime>

QSquarePanelWidget::QSquarePanelWidget() {
    h = 0;
    w = 0;
    squareSpacing = DEFAULT_SPACING;
    gridLayout = new QGridLayout;
    instance = nullptr;
}

QSquarePanelWidget::~QSquarePanelWidget() {
    clear();
}

QSquarePanelWidget *QSquarePanelWidget::getInstance() {
    if (instance == nullptr) {
        instance = new QSquarePanelWidget;
    }
    return instance;
}

void QSquarePanelWidget::setSize(int w, int h) {
    this->w = w;
    this->h = h;
}

void QSquarePanelWidget::renderSquares(const QVector<QSquareInfo> &squareInfos) {
    for (int i = 0; i < h; ++i) {
        squares.push_back(QVector<QLinkSquare *>(w, nullptr));
    }

    for (QSquareInfo squareInfo: squareInfos) {
        QLinkSquare *square = new QLinkSquare;
        int restHeight = (800 - (h - 1) * squareSpacing);
        square->setSize(restHeight / h, restHeight / h);
        square->setAndRenderIcon(squareInfo.iconIndex);
        int x = squareInfo.pos.x(), y = squareInfo.pos.y();
        squares[x][y] = square;
        gridLayout->addWidget(square->getWidget(), x, y, 1, 1);
    }
    restSquares = squareInfos.size();
}

void QSquarePanelWidget::loadFromArchive(const QSquarePanelInfo &squarePanelInfo) {
    clear();
    setSize(squarePanelInfo.w, squarePanelInfo.h);
    renderSquares(squarePanelInfo.squareInfos);
    setUpGridLayout();
    onRender();
}

QSquarePanelInfo QSquarePanelWidget::getSquarePanelInfo() const {
    QSquarePanelInfo squarePanelInfo(QSize(w, h));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (squares[i][j] != nullptr) {
                squarePanelInfo.addSquareInfo(QSquareInfo(QPoint(i, j), squares[i][j]->getIconIndex()));
            }
        }
    }
    return squarePanelInfo;
}

void QSquarePanelWidget::prepareRandom(QMap<int, int> &randomIconIdxToNum) {
    int totalNum = w * h;
    int maxCategoryNum = totalNum / 2;
    int randomSeed = RandomUtil::randomSeed();
    srand(randomSeed);
    int iconCategoryNum = qMin(maxCategoryNum, 40);
    int rest = (totalNum / 2) % iconCategoryNum;
    int iconNum = totalNum / 2 / iconCategoryNum;
    for (int i = 1; i <= iconCategoryNum; ++i) {
        int additional = 0;
        if (rest) {
            additional = RandomUtil::randRange(1, rest);
            rest -= additional;
        }
        randomIconIdxToNum.insert(i, (iconNum + additional) * 2);
    }
}

QPair <Direction, Direction> QSquarePanelWidget::getRelativeDirection(const QPoint &from, const QPoint &to) const {
    QPair <Direction, Direction> relativeDirection;
    QPoint diff = to - from;
    if (diff.x() < 0)
        relativeDirection.first = Direction::Up;
    else if (diff.x() > 0)
        relativeDirection.first = Direction::Down;
    else
        relativeDirection.first = Direction::None;
    if (diff.y() < 0)
        relativeDirection.second = Direction::Left;
    else if (diff.y() > 0)
        relativeDirection.second = Direction::Right;
    else
        relativeDirection.second = Direction::None;
    return relativeDirection;
}

void QSquarePanelWidget::renderSquares() {
    QMap<int, int> randomIconIdxToNum;
    prepareRandom(randomIconIdxToNum);

    for (int i = 0; i < h; ++i) {
        squares.push_back(QVector<QLinkSquare *>(w, nullptr));
        for (int j = 0; j < w; ++j) {
            QLinkSquare *square = new QLinkSquare;
            int restHeight = (800 - (h - 1) * squareSpacing);
            int randomId = RandomUtil::randRange(0, randomIconIdxToNum.size() - 1);
            auto it = randomIconIdxToNum.begin();
            for (int i = 0; i < randomId; ++i, ++it);
            square->setSize(restHeight / h, restHeight / h);
            square->setAndRenderIcon(it.key());
            squares[i][j] = square;
            gridLayout->addWidget(square->getWidget(), i, j, 1, 1);
            --it.value();
            if (it.value() == 0)
                randomIconIdxToNum.remove(it.key());
        }
    }
    restSquares = w * h;
}

void QSquarePanelWidget::initSquareMap() {
    squareMap.clear();
    for (int i = 0; i <= h + 1; ++i) {
        QVector<int> row(w + 2, 0);
        squareMap.push_back(row);
    }

    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            if (squares[i - 1][j - 1] != nullptr)
                squareMap[i][j] = 1;
        }
    }
}

void QSquarePanelWidget::activate(const QPoint &fromPos) {
    int fromX = fromPos.x();
    int fromY = fromPos.y();
    int col = (fromX - pos().x()) / ((800 - (h - 1) * squareSpacing) / h + squareSpacing);
    int row = (fromY - pos().y()) / ((800 - (h - 1) * squareSpacing) / h + squareSpacing);

    if (0 <= row && row < h && 0 <= col && col < w) {
        QLinkSquare *targetSquare = squares[row][col];
        if (targetSquare != nullptr && !targetSquare->isActivated()) {
            targetSquare->activate();
            activateQueue.enqueue(QPoint(row, col));
            tryLink();
        }
    }
}

void QSquarePanelWidget::removeSquareAt(int x, int y) {
    QLinkSquare *targetSquare = squares[x][y];
    if (targetSquare != nullptr) {
//        targetSquare->getWidget()->setParent(nullptr);
//        gridLayout->removeWidget(targetSquare->getWidget());
//        delete targetSquare;
        targetSquare->clearIcon();
        squares[x][y] = nullptr;
        squareMap[x + 1][y + 1] = 0;
    }
}

void QSquarePanelWidget::removeSquareAt(QPoint p) {
    removeSquareAt(p.x(), p.y());
}

void QSquarePanelWidget::setUpGridLayout() {
    setGeometry(980 - (800 * w / h) / 2, 100, 800 * w / h, 800);
    gridLayout->setSpacing(squareSpacing);
    gridLayout->setMargin(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(gridLayout);
}

void QSquarePanelWidget::render() {
    renderSquares();
    setUpGridLayout();
}

void QSquarePanelWidget::clear() {
    int curH = squares.size();
    int curW = curH ? squares[0].size() : 0;
    for (int i = 0; i < curH; ++i) {
        for (int j = 0; j < curW; ++j) {
            if (squares[i][j] == nullptr) continue;
            gridLayout->removeWidget(squares[i][j]->getWidget());
            squares[i][j]->getWidget()->setParent(nullptr);
            delete squares[i][j];
        }
    }
    squares.clear();
    linkablePairCache = INVALID_PAIR;
}

void QSquarePanelWidget::onRender() {
    initSquareMap();
    initSquarePosMap();
}

void QSquarePanelWidget::resizeAndRender(int w, int h) {
    clear();
    setSize(w, h);
    render();
    onRender();
}

QPoint QSquarePanelWidget::moveTowards(const QPoint &p, Direction direction) const {
    return QPoint(p.x() + next[direction][0], p.y() + next[direction][1]);
}

bool QSquarePanelWidget::canPassBy(const QPoint &p) const {
    return !outOfBound(p) && squareMap[p.x()][p.y()] == 0;
}

bool QSquarePanelWidget::outOfBound(const QPoint &p) const {
    return p.x() < 0 || p.x() > h + 1 || p.y() < 0 || p.y() > w + 1;
}

//deprecated
//using dfs, not so efficient
void QSquarePanelWidget::searchForLinkPath(bool &found, QPoint curP, QPoint tgtP, int lineCnt, Direction lastDire,
                                           QVector <QVector<bool>> &visited) {
    if (lineCnt > 3) return;
    if (curP == tgtP) {
        path.push_back(tgtP);
        found = true;
        return;
    }
    QPair <Direction, Direction> relativeDirection = getRelativeDirection(curP, tgtP);

    QVector <Direction> directions = {Direction::Left, Direction::Right, Direction::Up, Direction::Down};

    if (relativeDirection.first != Direction::None)
        qSwap(directions[0], directions[relativeDirection.first]);

    if (relativeDirection.second != Direction::None)
        qSwap(directions[1], directions[relativeDirection.second]);

    Direction curDire;
    QPoint nextP;
    int curCnt;

    for (int i = 0; i < 4; ++i) {
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

//deprecated
//bool QSquarePanelWidget::isLinkable(const QPoint &p1, const QPoint &p2) {
//    QLinkSquare *firstSquare = squares[p1.x()][p1.y()];
//    QLinkSquare *secondSquare = squares[p2.x()][p2.y()];
//    bool found = false;
//    if (firstSquare->equals(secondSquare)) {
//        QVector <QVector<bool>> visited(h + 2, QVector<bool>(w + 2, false));
//        QPoint from = toMapPoint(p1);
//        QPoint to = toMapPoint(p2);
//        path.clear();
//        searchForLinkPath(found, from, to, 0, None, visited);
//    }
//    return found;
//}

bool QSquarePanelWidget::isLinkable(const QPoint &p1, const QPoint &p2) const {
    QLinkSquare *first = squares[p1.x()][p1.y()];
    QLinkSquare *second = squares[p2.x()][p2.y()];
    return first->equals(second) && (checkStraightLine(p1, p2) || checkOneCorner(p1, p2) || checkTwoCorner(p1, p2));
}

QPoint QSquarePanelWidget::toRealPoint(const QPoint &org) const {
    int rx = pos().x()
             + (800 - (h - 1) * squareSpacing) / (2 * h) * (1 + 2 * (org.y() - 1))
             + (org.y() - 1) * squareSpacing;
    int ry = pos().y()
             + (800 - (h - 1) * squareSpacing) / (2 * h) * (1 + 2 * (org.x() - 1))
             + (org.x() - 1) * squareSpacing;
    return QPoint(rx, ry);
}

bool QSquarePanelWidget::searchLinkabelSquare() {
    for (const QVector <QPoint> &points: squarePosMap) {
        int size = points.size();
        for (int i = 0; i < size; ++i)
            for (int j = i + 1; j < size; ++j)
                if (isLinkable(points[i], points[j])) {
                    linkablePairCache = qMakePair(points[i], points[j]);
                    qDebug() << "Can link :" << points[i] << " to " << points[j] << endl;
                    return true;
                }
    }
    return false;
}

bool QSquarePanelWidget::existsLinkableSquare() {
    if (linkablePairCache != INVALID_PAIR) {
        qDebug() << "cached " << linkablePairCache << endl;
        return true;
    }

    qDebug() << "cannot link!" << endl;
    return searchLinkabelSquare();
}

void QSquarePanelWidget::updateCache(const QPoint &p1, const QPoint &p2) {
    int iconIndex = squares[p1.x()][p1.y()]->getIconIndex();
    if (linkablePairCache.first == p1 || linkablePairCache.second == p1 || linkablePairCache.first == p2 ||
        linkablePairCache.second == p2)
        linkablePairCache = INVALID_PAIR;
    QVector <QPoint> &points = squarePosMap[iconIndex];
    points.removeOne(p1);
    points.removeOne(p2);
}

void QSquarePanelWidget::hintNext() {
    if (linkablePairCache == INVALID_PAIR) {
        searchLinkabelSquare();
    }
    highlightAt(linkablePairCache.first);
    highlightAt(linkablePairCache.second);
}

void QSquarePanelWidget::link(const QPoint &p1, const QPoint &p2) {
    emit link("消除");
    updateCache(p1, p2);
    removeSquareAt(p1);
    removeSquareAt(p2);
    QLinkGameController *gameController = QLinkGameController::getInstance();
    restSquares -= 2;
    gameController->addScore(15);
    gameController->setRestSquares(restSquares);
    if (!existsLinkableSquare()) {
        shuffle();
    }
    if (runMode == RunMode::HINT) {
        hintNext();
    }
}

void QSquarePanelWidget::highlightAt(const QPoint &p) {
    squares[p.x()][p.y()]->highlight();
}

void QSquarePanelWidget::cancelLink(const QPoint &p1, const QPoint &p2) {
    emit link("不可消除");
    squares[p1.x()][p1.y()]->reset();
    squares[p2.x()][p2.y()]->reset();
}

void QSquarePanelWidget::tryLink() {
    if (activateQueue.size() == 2) {
        QPoint first = activateQueue.dequeue();
        QPoint second = activateQueue.dequeue();
        if (isLinkable(first, second)) {
            link(first, second);
        } else {
            cancelLink(first, second);
        }
    }
}

QSize QSquarePanelWidget::getSquareSize() const {
    int restHeight = (800 - (h - 1) * squareSpacing);
    return QSize(restHeight / h, restHeight / h);
}

QPoint QSquarePanelWidget::toMapPoint(const QPoint &p) const {
    return QPoint(p.x() + 1, p.y() + 1);
}

QPoint QSquarePanelWidget::toMapPoint(int x, int y) const {
    return QPoint(x + 1, y + 1);
}

void QSquarePanelWidget::shuffle() {
    qDebug() << "Shuffle" << endl;

    QVector <QPoint> points;
    QVector<int> icons;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (squares[i][j] != nullptr) {
                icons.push_back(squares[i][j]->getIconIndex());
                points.push_back(QPoint(i, j));
            }
        }
    }
    std::random_shuffle(points.begin(), points.end());
    for (int i = 0; i < points.size(); ++i) {
        int x = points[i].x();
        int y = points[i].y();
        squares[x][y]->setAndRenderIcon(icons[i]);
    }

    initSquarePosMap();
}

//check if it's blocked
bool QSquarePanelWidget::checkVertical(const QPoint &p1, const QPoint &p2) const {
    int x1 = p1.x(), y1 = p1.y(), x2 = p2.x();
    if (x1 == x2) return false;
//    qDebug() << "check vertical: " << "p1: " << p1 << "p2: " << p2 << endl;
    int minX = qMin(x1, x2);
    int maxX = qMax(x1, x2);
    for (int x = minX + 1; x < maxX; ++x)
        if (squareMap[x][y1] != 0)
            return false;
//    qDebug() << "vertical check passed" << endl;
    return true;
}

bool QSquarePanelWidget::checkHorizontal(const QPoint &p1, const QPoint &p2) const {
    int x1 = p1.x(), y1 = p1.y(), y2 = p2.y();
    if (y1 == y2) return false;
//    qDebug() << "check horizontal: " << "p1: " << p1 << "p2: " << p2 << endl;
    int minY = qMin(y1, y2);
    int maxY = qMax(y1, y2);
    for (int y = minY + 1; y < maxY; ++y)
        if (squareMap[x1][y] != 0)
            return false;
//    qDebug() << "horizontal check passed" << endl;
    return true;
}

bool QSquarePanelWidget::checkStraightLine(const QPoint &p1, const QPoint &p2) const {
    QPoint mp1 = toMapPoint(p1), mp2 = toMapPoint(p2);
    return (mp1.y() == mp2.y() && checkVertical(mp1, mp2)) || (mp1.x() == mp2.x() && checkHorizontal(mp1, mp2));
}

bool QSquarePanelWidget::checkOneCorner(const QPoint &p1, const QPoint &p2) const {
//    qDebug() << "check one corner: " << "p1: " << p1 << "p2: " << p2 << endl;
    QPoint mp1 = toMapPoint(p1), mp2 = toMapPoint(p2);
    QPoint corner_1 = toMapPoint(p2.x(), p1.y());
    QPoint corner_2 = toMapPoint(p1.x(), p2.y());
    bool ret = (canPassBy(corner_1) && checkVertical(mp1, corner_1) && checkHorizontal(corner_1, mp2)) ||
               (canPassBy(corner_2) && checkHorizontal(mp1, corner_2) && checkVertical(corner_2, mp2));
    if (ret) qDebug() << "one corner check passed" << endl;
    return ret;
}

bool QSquarePanelWidget::checkTwoCorner(const QPoint &p1, const QPoint &p2) const {
//    qDebug() << "check two corner: " << "p1: " << p1 << "p2: " << p2 << endl;
    QPoint mp1 = toMapPoint(p1), mp2 = toMapPoint(p2);
    int mx1 = mp1.x(), mx2 = mp2.x();
    for (int j = 0; j <= w + 1; ++j) {
        QPoint corner_1(mx1, j);
        QPoint corner_2(mx2, j);
        if (!canPassBy(corner_1) || !canPassBy(corner_2)) continue;
        if (checkVertical(corner_1, corner_2) && checkHorizontal(mp1, corner_1) && checkHorizontal(mp2, corner_2)) {
            qDebug() << "two corner check passed" << endl;
            return true;
        }
    }

    int my1 = mp1.y(), my2 = mp2.y();
    for (int i = 0; i <= h + 1; ++i) {
        QPoint corner_1(i, my1);
        QPoint corner_2(i, my2);
        if (!canPassBy(corner_1) || !canPassBy(corner_2)) continue;
        if (checkHorizontal(corner_1, corner_2) && checkVertical(mp1, corner_1) && checkVertical(mp2, corner_2)) {
            qDebug() << "two corner check passed" << endl;
            return true;
        }
    }

    return false;
}

void QSquarePanelWidget::startHint() {
    qDebug() << "start hint" << endl;
    runMode = RunMode::HINT;
    hintNext();
    QTimer::singleShot(10000, this, [&](){
        runMode = RunMode::COMMON;
        qDebug() << "end hint after 10s" << endl;
    });
}

void QSquarePanelWidget::initSquarePosMap() {
    squarePosMap.clear();
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (squares[i][j] == nullptr) continue;
            int index = squares[i][j]->getIconIndex();
            if (!squarePosMap.contains(index))
                squarePosMap.insert(index, QVector<QPoint>());
            squarePosMap[index].push_back(QPoint(i, j));
        }
    }
}

const QPair<QPoint, QPoint> QSquarePanelWidget::INVALID_PAIR = qMakePair(QPoint(-1, -1), QPoint(-1, -1));
QSquarePanelWidget *QSquarePanelWidget::instance;

