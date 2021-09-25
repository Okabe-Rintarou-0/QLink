#include "QCharacterManager.h"

QCharacterManager::QCharacterManager() {
    characters = new QCharacterWidget *[2];
    for (int i = 0; i < 2; ++i)characters[i] = nullptr;
    instance = nullptr;
}

QCharacterManager *QCharacterManager::getInstance() {
    if (instance == nullptr) {
        instance = new QCharacterManager;
    }
    return instance;
}

QPlayerInfo QCharacterManager::getPlayerInfo() const {
    return QPlayerInfo(getCharacterInfos());
}

void QCharacterManager::addCharacter(QCharacterWidget *character) {
    if (characters[0] == nullptr)
        characters[0] = character;
    else characters[1] = character;
}

QCharacterWidget *QCharacterManager::getCharacter(int id) {
    return 0 <= id && id <= 1 ? characters[id] : nullptr;
}

QVector<QCharacterInfo> QCharacterManager::getCharacterInfos() const {
    QVector<QCharacterInfo> characterInfos(2);
    for (int i =0; i < 2; ++i) {
        QCharacterWidget *c = characters[i];
        characterInfos[i] = QCharacterInfo(c->pos(), c->getMoveMode());
    }
    return characterInfos;
}

void QCharacterManager::frozenAll() {
    for (int i = 0; i < 2; ++i) {
        if (characters[i] != nullptr) {
            characters[i]->setMoveMode(MoveMode::FROZEN);
        }
    }
}

void QCharacterManager::unfrozenAll() {
    for (int i = 0; i < 2; ++i) {
        if (characters[i] != nullptr) {
            characters[i]->setMoveMode(MoveMode::COMMON);
        }
    }
}

QCharacterManager *QCharacterManager::instance;

