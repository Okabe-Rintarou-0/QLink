#include "QSquarePanelWidget.h"
QSquarePanelWidget::QSquarePanelWidget()
{
    h = DEFAULT_H;
    w = DEFAULT_W;
    gridLayout = new QGridLayout;
}

QSquarePanelWidget::~QSquarePanelWidget()
{
    clear();
}

void QSquarePanelWidget::setSize(int h, int w)
{
    this->h = h;
    this->w = w;
}

void QSquarePanelWidget::renderSquares()
{
    for (int i = 0; i < h; ++i)
    {
        squares.push_back(QVector<QLinkSquare *>(w));
        for (int j = 0; j < w; ++j)
        {
            QLinkSquare *square = new QLinkSquare();
            squares[i].push_back(square);
            gridLayout->addWidget(square->getWidget(), i, j, 1, 1);
        }
    }
}

void QSquarePanelWidget::setUpGridLayout()
{
    gridLayout->setSpacing(5);
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
            delete squares[i][j];
        }
    }
    squares.clear();
}
