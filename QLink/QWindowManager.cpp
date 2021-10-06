#include "QWindowManager.h"

QWindowManager::QWindowManager() {
    gameWindow = new GameWindow;
    menu = new QLinkMenu;
    gameSettingDialog = new GameSettingDialog;

    menu->show();

    instance = nullptr;

    QApplication::connect(gameSettingDialog, &GameSettingDialog::startGame, gameWindow, &GameWindow::startGame);
    QApplication::connect(gameWindow, &GameWindow::selected, this, &QWindowManager::select);
    QApplication::connect(gameSettingDialog, &GameSettingDialog::selected, this, &QWindowManager::select);
    QApplication::connect(menu, &QLinkMenu::selected, this, &QWindowManager::select);
}

void QWindowManager::loadArchive() {
    menu->hide();
    gameWindow->show();
    QLinkArchiveManager::getInstance()->loadArchive();
}

void QWindowManager::returnMenu() {
    gameWindow->hide();
    gameSettingDialog->hide();
    QLinkGameController::getInstance()->endGame();
    menu->show();
}

void QWindowManager::startGame(GameMode gameMode) {
    menu->hide();
    gameSettingDialog->show();
    gameSettingDialog->setGameMode(gameMode);
}

void QWindowManager::select(MenuSelection::Selection selection) {
    switch (selection) {
        case MenuSelection::ONE_PLAYER:
            startGame(GameMode::ONE_PLAYER);
            break;
        case MenuSelection::TWO_PLAYER:
            startGame(GameMode::TWO_PLAYER);
            break;
        case MenuSelection::LOAD_ARCHIVE:
            loadArchive();
            break;
        case MenuSelection::QUIT:
            QApplication::quit();
            break;
        case MenuSelection::RET:
            returnMenu();
            break;
    }
}

QWindowManager *QWindowManager::getInstance() {
    if (instance == nullptr)
        instance = new QWindowManager;
    return instance;
}

QWindowManager::~QWindowManager() {
    delete gameWindow;
    delete menu;
    delete gameSettingDialog;
    delete instance;
}

QWindowManager* QWindowManager::instance;
