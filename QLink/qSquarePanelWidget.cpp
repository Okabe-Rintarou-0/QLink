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

void QSquarePanelWidget::renderSquares()
{
    QMap<int, int> randomIconIdxToNum;
    int totalNum = w * h;
    int randomSeed = QDateTime::currentDateTime().toTime_t();
    randomSeed = RandomUtil::randRange(0, randomSeed) + randomSeed;
    srand(randomSeed);
    int randomNum = RandomUtil::randRange(totalNum / 8, totalNum / 16);
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
        randomIconIdxToNum.insert(randomIdx, iconNum + additional);
    }

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

void QSquarePanelWidget::setUpGridLayout()
{
    gridLayout->setSpacing(squareSpacing);
    gridLayout->setMargin(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
}

void QSquarePanelWidget::render()
{
    renderSquares();
    setUpGridLayout();
    setLayout(gridLayout);
    setGeometry(980 - (800 * w / h) / 2, 100, 800 * w / h, 800);
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

void QSquarePanelWidget::tryLink()
{
    if(activateQueue.size() == 2)
    {
        QPoint first = activateQueue.dequeue();
        QPoint second = activateQueue.dequeue();
        QLinkSquare *firstSquare = squares[first.x()][first.y()];
        QLinkSquare *secondSquare = squares[second.x()][second.y()];
        qDebug()<<"first "<<first<<endl;
        qDebug()<<"second "<<second<<endl;
        if (firstSquare->equals(*secondSquare))
        {
            qDebug()<<" called "<<endl;
            firstSquare->getWidget()->setParent(nullptr);
            secondSquare->getWidget()->setParent(nullptr);
            gridLayout->removeWidget(firstSquare->getWidget());
            gridLayout->removeWidget(secondSquare->getWidget());
            delete firstSquare;
            delete secondSquare;
            squares[first.x()][first.y()] = squares[second.x()][second.y()] = nullptr;
        }
        else
        {
            qDebug() << "Not equal, so reset" << endl;
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
