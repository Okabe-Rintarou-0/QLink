#include "QLinkMenu.h"
#include "ui_QLinkMenu.h"
#include "QFile"
#include "FileConstants.h"

QLinkMenu::QLinkMenu(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::QLinkMenu) {
    ui->setupUi(this);

    QFile file(":/MenuButton.qss");
    file.open(QIODevice::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    onePlayerBtn = new QPushButton(this);
    onePlayerBtn->setObjectName("onePlayerBtn");
    onePlayerBtn->setGeometry(800, 300, 400, 60);
    onePlayerBtn->setText("单人游戏");
    onePlayerBtn->setFont(QFont("Microsoft YaHei", 10, 75));
    QApplication::connect(onePlayerBtn, &QPushButton::clicked, this, [&]() {
        emit selected(MenuSelection::ONE_PLAYER);
    });
    onePlayerBtn->setStyleSheet(styleSheet);

    twoPlayerBtn = new QPushButton(this);
    twoPlayerBtn->setGeometry(800, 400, 400, 60);
    twoPlayerBtn->setObjectName("twoPlayerBtn");
    twoPlayerBtn->setText("双人游戏");
    twoPlayerBtn->setFont(QFont("Microsoft YaHei", 10, 75));
    QApplication::connect(twoPlayerBtn, &QPushButton::clicked, this, [&]() {
        emit selected(MenuSelection::TWO_PLAYER);
    });
    twoPlayerBtn->setStyleSheet(styleSheet);

    loadArchiveBtn = new QPushButton(this);
    loadArchiveBtn->setGeometry(800, 500, 400, 60);
    loadArchiveBtn->setObjectName("loadArchiveBtn");
    loadArchiveBtn->setText("加载存档");
    loadArchiveBtn->setFont(QFont("Microsoft YaHei", 10, 75));
    QApplication::connect(loadArchiveBtn, &QPushButton::clicked, this, [&]() {
        emit selected(MenuSelection::LOAD_ARCHIVE);
    });
    loadArchiveBtn->setStyleSheet(styleSheet);

    quitBtn = new QPushButton(this);
    quitBtn->setGeometry(800, 600, 400, 60);
    quitBtn->setText("退出游戏");
    quitBtn->setObjectName("quitBtn");
    quitBtn->setFont(QFont("Microsoft YaHei", 10, 75));
    QApplication::connect(quitBtn, &QPushButton::clicked, this, [&]() {
        emit selected(MenuSelection::QUIT);
    });
    quitBtn->setStyleSheet(styleSheet);

    banner = new QWidget(this);
    banner->setGeometry(810, 60, 1500, 300);
    banner->setAutoFillBackground(true);
    banner->lower();
    QImage image;
    image.load(FileConstants::BANNER_URL + "QLink2.png");
    QPalette palette;
    palette.setBrush(banner->backgroundRole(), QBrush(image.scaled(banner->size())));
    banner->setPalette(palette);
}

QLinkMenu::~QLinkMenu() {
    delete ui;
}
