#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    gameController = QLinkGameController::getInstance();
    characterManager = QCharacterManager::getInstance();

    setGeometry(0, 0, 1920, 1080);
    setWindowTitle("QLink");

    hintLabel = new QLabel(this);
    hintLabel->setText("按E激活方块");
    hintLabel->setGeometry(10, 10, 400, 60);
    hintLabel->setFont(QFont("Microsoft YaHei", 30, 75));

    linkStatusLabel = new QLabel(this);
    linkStatusLabel->setGeometry(10, 80, 200, 50);
    linkStatusLabel->setStyleSheet("color:red;");
    linkStatusLabel->setFont(QFont("Microsoft YaHei", 15, 50));

    scoreLabel = new QLabel(this);
    scoreLabel->setGeometry(960, 10, 200, 50);
    scoreLabel->setText("分数: 0");
    scoreLabel->setFont(QFont("Microsoft YaHei", 10, 75));

    squarePanel = QSquarePanelWidget::getInstance();
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

    testBtn = new QPushButton(this);
    testBtn->setText("存档");
    testBtn->setGeometry(1250, 930, 80, 40);
    QApplication::connect(testBtn, &QPushButton::clicked, this, [=](){
        QLinkArchiveManager::getInstance()->saveArchive();
    });

    characters = new QCharacterWidget *[2];

    countDownLCD = new QLCDNumber(this);
    countDownLCD->setGeometry(940, 50, 100, 40);
    countDownLCD->display(0);

//    pauseContinueButton = new QPauseContinueButton;
//    pauseContinueButton->setParent(this);
//    pauseContinueButton->setGeometry(250, 600, 150, 150);
//    pauseContinueButton->initAndShow();

//    QApplication::connect(pauseContinueButton, &QPauseContinueButton::clicked, gameController, &QLinkGameController::pauseOrContinue);

//    jewel = new HintJewel;
//    jewel->setParent(this);
//    jewel->setGeometry(50, 600, 50, 50);
//    jewel->connect(characters[0]);
//    jewel->stackUnder(characters[0]);
//    QApplication::connect(characters[0], &QCharacterWidget::moveTo, jewel, &QLinkGameItem::tryPick);

    setFocus();

    QApplication::connect(characterManager, SIGNAL(spawn(int, QPoint, MoveMode)), this, SLOT(spawnCharacter(int, QPoint, MoveMode)));
    QApplication::connect(gameController, SIGNAL(formJewel(QLinkGameItem *, QPoint)), this, SLOT(renderJewel(QLinkGameItem *, QPoint)));
    QApplication::connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);
    QApplication::connect(squarePanel, SIGNAL(link(QString)), linkStatusLabel, SLOT(setText(QString)));
    QApplication::connect(gameController, SIGNAL(timeChanged(int)), countDownLCD, SLOT(display(int)));
    QApplication::connect(gameController, SIGNAL(gameOver(QString)), this, SLOT(showGameOverTips(QString)));
    QApplication::connect(gameController, SIGNAL(scoreChanged(QString)), scoreLabel, SLOT(setText(QString)));


//    QLinkArchiveManager::getInstance()->loadArchive();
}

void MainWindow::spawnCharacter(int id, const QPoint &pos, MoveMode moveMode) {
//    qDebug() << "called " << id << " " << pos << " " << moveMode << endl;
    assert(id >= 0 && id <= 1);
    characters[id] = characterManager->getCharacter(id);
    characters[id]->setParent(this);
    characters[id]->setSize(squarePanel->getSquareSize());
    characters[id]->spawn(pos);
    characters[id]->setMoveMode(moveMode);
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

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (characters[0]->getMoveMode() == MoveMode::FLASH) {
            characters[0]->dash(event->pos());
        }
    }
}

void MainWindow::renderJewel(QLinkGameItem *jewel, const QPoint &pos) {
    qDebug() << "render jewel at pos: " << pos << endl;
    jewel->setGeometry(pos.x(), pos.y(), 50, 50);
    jewel->setParent(this);
    for (int i = 0; i < 1; ++i) {
        if (characters[i] != nullptr) {
            jewel->connect(characters[i]);
            jewel->stackUnder(characters[i]);
        }
    }
    jewel->show();
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        case Qt::Key_A:
            characters[0]->move(Direction::Left);
            break;
        case Qt::Key_D:
            characters[0]->move(Direction::Right);
            break;
        case Qt::Key_S:
            characters[0]->move(Direction::Down);
            break;
        case Qt::Key_W:
            characters[0]->move(Direction::Up);
            break;
        case Qt::Key_E:
            squarePanel->activate(characters[0]->center());
            break;
    }
    qDebug() << characters[0]->pos() << endl;
}
