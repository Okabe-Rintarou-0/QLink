#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(nullptr));
    setGeometry(0, 0, 1920, 1080);
    setWindowTitle("QLink");

    squarePanel = new QSquarePanelWidget;
    squarePanel->setParent(this);
    squarePanel->setSize(10, 10);
    squarePanel->render();

    QLabel *widthLabel = new QLabel(this);
    widthLabel->setGeometry(900, 940, 20, 20);
    widthLabel->setText("宽");
    widthSpinBox = new QSpinBox(this);
    widthSpinBox->setGeometry(920, 940, 40, 20);
    widthSpinBox->setValue(10);

    QLabel *heightLabel = new QLabel(this);
    heightLabel->setGeometry(970, 940, 20, 20);
    heightLabel->setText("高");
    heightSpinBox = new QSpinBox(this);
    heightSpinBox->setGeometry(990, 940, 40, 20);
    heightSpinBox->setValue(10);

    QPushButton *refreshButton = new QPushButton(this);
    refreshButton->setText("刷新");
    refreshButton->setGeometry(1050, 940, 50, 20);

    QApplication::connect(refreshButton, &QPushButton::clicked, this, [=](){
        int w = widthSpinBox->value();
        int h = heightSpinBox->value();
        if (h % 2 && w % 2)
        {
            QMessageBox::warning(this, "警告", "宽和高必须有一个是偶数！");
            return;
        }
        squarePanel->resizeAndRender(w, h);
    });

    characterWidget = new QCharacterWidget;
    characterWidget->setParent(this);
    characterWidget->setSize(squarePanel->getSquareSize());
    characterWidget->spawn();

    setFocus();


    QApplication::connect(squarePanel, SIGNAL(link(QVector<QPoint>)), this, SLOT(draw(QVector<QPoint>)));
}

void MainWindow::draw(QVector<QPoint> points)
{
    pointsToLink = points;
    needPaint = true;
    qDebug() << "called" << endl;
    repaint();
}

void MainWindow::drawLink(QPoint p1, QPoint p2, QPainter &painter, QColor linkColor, int width)
{
    qDebug() << "draw from " << p1 << " to " << p2 <<endl;
    painter.setBrush(QBrush(linkColor));
    QPoint topLeft = p1.x() < p2.x() ?
                QPoint(p1.x(), p1.y() - width / 2) : QPoint(p2.x(), p2.y() - width / 2);
    QPoint bottomRight = p1.x() < p2.x() ?
                QPoint(p2.x(), p2.y() + width / 2) : QPoint(p1.x(), p1.y() + width / 2);
    QRect rect(topLeft, bottomRight);
    painter.drawRect(rect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        case Qt::Key_A:
            characterWidget->moveLeft();
            break;
        case Qt::Key_D:
            characterWidget->moveRight();
            break;
        case Qt::Key_S:
            characterWidget->moveDown();
            break;
        case Qt::Key_W:
            characterWidget->moveUp();
            break;
        case Qt::Key_E:
            squarePanel->activate(characterWidget->center());
            break;
    }
    //qDebug() << characterWidget->center() << endl;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if (!needPaint) return;
    event->accept();
    QPainter painter(this);
    for (int i = 0; i < pointsToLink.size() - 1; ++i)
    {
        drawLink(pointsToLink[i], pointsToLink[i + 1], painter, DEFAULT_LINE_COLOR, 4);
    }
    needPaint = false;
}

const QColor MainWindow::DEFAULT_LINE_COLOR = Qt::black;
