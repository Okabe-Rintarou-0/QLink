#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    gameController = QLinkGameController::getInstance();
    setGeometry(0, 0, 1920, 1080);
    setWindowTitle("QLink");

    hintLabel = new QLabel(this);
    hintLabel->setText("按E激活方块");
    hintLabel->setGeometry(10, 10, 400, 60);
    hintLabel->setFont(QFont("Microsoft YaHei", 30, 75));

    scoreLabel = new QLabel(this);
    scoreLabel->setGeometry(960, 10, 200, 50);
    scoreLabel->setText("分数: 0");
    scoreLabel->setFont(QFont("Microsoft YaHei", 10, 75));

    squarePanel = new QSquarePanelWidget;
    squarePanel->setParent(this);
    squarePanel->setSize(8, 8);

    widthLabel = new QLabel(this);
    widthLabel->setGeometry(900, 940, 20, 20);
    widthLabel->setText("宽");
    widthSpinBox = new QSpinBox(this);
    widthSpinBox->setGeometry(920, 940, 40, 20);
    widthSpinBox->setValue(8);

    heightLabel = new QLabel(this);
    heightLabel->setGeometry(970, 940, 20, 20);
    heightLabel->setText("高");
    heightSpinBox = new QSpinBox(this);
    heightSpinBox->setGeometry(990, 940, 40, 20);
    heightSpinBox->setValue(8);

    startButton = new QPushButton(this);
    startButton->setText("开始游戏");
    startButton->setGeometry(1050, 930, 80, 40);

//    testBtn = new QPushButton(this);
//    testBtn->setText("重新布局");
//    testBtn->setGeometry(1250, 930, 80, 40);

    characterWidget = new QCharacterWidget;
    characterWidget->setParent(this);
    characterWidget->setSize(squarePanel->getSquareSize());
    characterWidget->spawn();

    countDownLCD = new QLCDNumber(this);
    countDownLCD->setGeometry(940, 50, 100, 40);
    countDownLCD->display(0);

    setFocus();

    QApplication::connect(gameController, SIGNAL(timeChanged(int)), countDownLCD, SLOT(display(int)));
    QApplication::connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);
    QApplication::connect(gameController, SIGNAL(gameOver(QString)), this, SLOT(showGameOverTips(QString)));
    QApplication::connect(gameController, SIGNAL(scoreChanged(QString)), scoreLabel, SLOT(setText(QString)));
}

void MainWindow::startGame()
{
    int w = widthSpinBox->value();
    int h = heightSpinBox->value();
    if (h % 2 && w % 2)
    {
        QMessageBox::warning(this, "警告", "宽和高必须有一个是偶数！");
        return;
    }
    gameController->startGame();
    squarePanel->resizeAndRender(w, h);
}

void MainWindow::showGameOverTips(const QString &tips)
{
    QMessageBox::information(this, "提示", tips);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
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
}
