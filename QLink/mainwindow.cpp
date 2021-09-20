#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameController = QLinkGameController::getInstance();
    setGeometry(0, 0, 1920, 1080);
    setWindowTitle("QLink");

    scoreLabel = new QLabel(this);
    scoreLabel->setGeometry(960, 10, 200, 50);
    scoreLabel->setText("分数: 0");
    scoreLabel->setFont(QFont("Microsoft YaHei", 10, 75));

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

    QApplication::connect(gameController, SIGNAL(scoreChanged(QString)), scoreLabel, SLOT(setText(QString)));
//    QApplication::connect(squarePanel, SIGNAL(link(QVector<QPoint>)), linkCanvas, SLOT(draw(QVector<QPoint>)));
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
