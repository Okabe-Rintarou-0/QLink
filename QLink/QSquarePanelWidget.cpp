#include "QSquarePanelWidget.h"
#include <QDebug>
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

void QSquarePanelWidget::setSize(int w, int h)
{
    this->w = w;
    this->h = h;
}

void QSquarePanelWidget::renderSquares()
{
    for (int i = 0; i < h; ++i)
    {
        squares.push_back(QVector<QLinkSquare *>(w));
        for (int j = 0; j < w; ++j)
        {
            QLinkSquare *square = new QLinkSquare;
            square->setSize(800 / h, 800 / h);
            square->setIcon(rand() % 40 + 1);
            squares[i][j] = square;
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
            gridLayout->removeWidget(squares[i][j]->getWidget());
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
