#include "QLinkMenu.h"
#include "ui_QLinkMenu.h"


QLinkMenu::QLinkMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QLinkMenu)
{
    ui->setupUi(this);

    onePlayerBtn = new QPushButton(this);
    onePlayerBtn->setGeometry(800, 300, 400, 60);
    onePlayerBtn->setText("单人游戏");
    onePlayerBtn->setFont(QFont("Microsoft YaHei", 10, 75));
    QApplication::connect(onePlayerBtn, &QPushButton::clicked, this, [&](){
        emit selected(MenuSelection::ONE_PLAYER);
    });

    twoPlayerBtn = new QPushButton(this);
    twoPlayerBtn->setGeometry(800, 400, 400, 60);
    twoPlayerBtn->setText("双人游戏");
    twoPlayerBtn->setFont(QFont("Microsoft YaHei", 10, 75));
    QApplication::connect(twoPlayerBtn, &QPushButton::clicked, this, [&](){
        emit selected(MenuSelection::TWO_PLAYER);
    });

    loadArchiveBtn = new QPushButton(this);
    loadArchiveBtn->setGeometry(800, 500, 400, 60);
    loadArchiveBtn->setText("加载存档");
    loadArchiveBtn->setFont(QFont("Microsoft YaHei", 10, 75));
    QApplication::connect(loadArchiveBtn, &QPushButton::clicked, this, [&](){
        emit selected(MenuSelection::LOAD_ARCHIVE);
    });

    quitBtn = new QPushButton(this);
    quitBtn->setGeometry(800, 600, 400, 60);
    quitBtn->setText("退出游戏");
    quitBtn->setFont(QFont("Microsoft YaHei", 10, 75));
    QApplication::connect(quitBtn, &QPushButton::clicked, this, [&](){
        emit selected(MenuSelection::QUIT);
    });
}

QLinkMenu::~QLinkMenu()
{
    delete ui;
}
