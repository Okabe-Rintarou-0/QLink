#include "GameWindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    gameController = QLinkGameController::getInstance();
    characterManager = QCharacterManager::getInstance();

    setGeometry(0, 0, 1920, 1080);
    setWindowTitle("QLink");

    hintLabel = new QLabel(this);
    hintLabel->setText("玩家一按E激活方块，玩家2按P激活方块");
    hintLabel->setGeometry(10, 10, 400, 60);
    hintLabel->setFont(QFont("Microsoft YaHei", 15, 75));

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

//    widthLabel = new QLabel(this);
//    widthLabel->setGeometry(900, 940, 20, 20);
//    widthLabel->setText("宽");
//    widthSpinBox = new QSpinBox(this);
//    widthSpinBox->setGeometry(920, 940, 40, 20);
//    widthSpinBox->setValue(8);

//    heightLabel = new QLabel(this);
//    heightLabel->setGeometry(970, 940, 20, 20);
//    heightLabel->setText("高");
//    heightSpinBox = new QSpinBox(this);
//    heightSpinBox->setGeometry(990, 940, 40, 20);
//    heightSpinBox->setValue(8);

    retButton = new QPushButton(this);
    retButton->setText("返回菜单");
    retButton->setGeometry(900, 930, 80, 40);

    saveBtn = new QPushButton(this);
    saveBtn->setText("存档");
    saveBtn->setGeometry(1000, 930, 80, 40);
    QApplication::connect(saveBtn, &QPushButton::clicked, this, [=](){
        QLinkArchiveManager::getInstance()->saveArchive();
    });

    characters = new QCharacterWidget *[2];

    countDownLCD = new QLCDNumber(this);
    countDownLCD->setGeometry(940, 50, 100, 40);
    countDownLCD->display(0);

    pauseContinueButton = new QPauseContinueButton;
    pauseContinueButton->setParent(this);
    pauseContinueButton->setGeometry(1800, 40, 80, 80);

    QApplication::connect(pauseContinueButton, &QPauseContinueButton::clicked, gameController, &QLinkGameController::pauseOrContinue);

//    jewel = new HintJewel;
//    jewel->setParent(this);
//    jewel->setGeometry(50, 600, 50, 50);
//    jewel->connect(characters[0]);
//    jewel->stackUnder(characters[0]);
//    QApplication::connect(characters[0], &QCharacterWidget::moveTo, jewel, &QLinkGameItem::tryPick);

    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    QApplication::connect(characterManager, SIGNAL(spawn(int, QPoint, MoveMode)), this, SLOT(spawnCharacter(int, QPoint, MoveMode)));
    QApplication::connect(gameController, SIGNAL(formJewel(QLinkGameItem *, QPoint)), this, SLOT(renderJewel(QLinkGameItem *, QPoint)));
    QApplication::connect(retButton, &QPushButton::clicked, this, [&](){
        emit selected(MenuSelection::RET);
    });
    QApplication::connect(squarePanel, SIGNAL(tryLink(QString)), linkStatusLabel, SLOT(setText(QString)));
    QApplication::connect(gameController, SIGNAL(timeChanged(int)), countDownLCD, SLOT(display(int)));
    QApplication::connect(gameController, SIGNAL(gameOver(QString)), this, SLOT(showGameOverTips(QString)));
    QApplication::connect(gameController, SIGNAL(scoreChanged(QString)), scoreLabel, SLOT(setText(QString)));


//    QLinkArchiveManager::getInstance()->loadArchive();
}

void GameWindow::spawnCharacter(int id, const QPoint &pos, MoveMode moveMode) {
//    qDebug() << "called " << id << " " << pos << " " << moveMode << endl;
    assert(id >= 0 && id <= 1);
    characters[id] = characterManager->getCharacter(id);
    characters[id]->setParent(this);
    characters[id]->setSize(squarePanel->getSquareSize());
    characters[id]->spawn(pos);
    characters[id]->setMoveMode(moveMode);
}

void GameWindow::startGame(int w, int h, GameMode gameMode)
{
    pauseContinueButton->initAndShow();
    show();
    spawnCharacter(0, QPoint(200, 200), MoveMode::COMMON);

    if (gameMode == TWO_PLAYER)
       spawnCharacter(1, QPoint(250, 200), MoveMode::COMMON);
    gameController->startGame();

    squarePanel->resizeAndRender(w, h);
}

void GameWindow::showGameOverTips(const QString &tips)
{
    QMessageBox::information(this, "提示", tips);
}

GameWindow::~GameWindow() {
    delete ui;
}

void GameWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (characters[0]->getMoveMode() == MoveMode::FLASH) {
            characters[0]->dash(event->pos());
        }
    }
}

void GameWindow::renderJewel(QLinkGameItem *jewel, const QPoint &pos) {
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

void GameWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        if(characters[0] != nullptr){
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
            squarePanel->activate(0, characters[0]->center());
            break;
        }
        if(characters[1] != nullptr){
        case Qt::Key_Left:
            characters[1]->move(Direction::Left);
            break;
        case Qt::Key_Right:
            characters[1]->move(Direction::Right);
            break;
        case Qt::Key_Down:
            characters[1]->move(Direction::Down);
            break;
        case Qt::Key_Up:
            characters[1]->move(Direction::Up);
            break;
        case Qt::Key_P:
            squarePanel->activate(1, characters[1]->center());
            break;
        }
    }
}