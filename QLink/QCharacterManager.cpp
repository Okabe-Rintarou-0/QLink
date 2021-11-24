#include "QCharacterManager.h"

QCharacterManager::QCharacterManager() {
    characters = new QCharacterWidget *[2];
    for (int i = 0; i < 2; ++i) characters[i] = nullptr;
    instance = nullptr;
}

QCharacterManager *QCharacterManager::getInstance() {
    if (instance == nullptr) {
        instance = new QCharacterManager;
    }
    return instance;
}

QCharacterManager::~QCharacterManager() {
    delete instance;
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
    assert(id >= 0 && id <= 1);
    if (characters[id] == nullptr)
        characters[id] = new QCharacterWidget(id);
    return characters[id];
}

QVector <QCharacterInfo> QCharacterManager::getCharacterInfos() const {
    QVector <QCharacterInfo> characterInfos;
    for (int i = 0; i < 2; ++i) {
        QCharacterWidget *c = characters[i];
        if (c != nullptr)
            characterInfos.push_back(QCharacterInfo(c->pos(), c->getMoveMode()));
    }
    return characterInfos;
}

void QCharacterManager::loadFromArchive(const QPlayerInfo &playerInfo) {
    assert(playerInfo.characters.size() <= 2);
    for (int i = 0; i < playerInfo.characters.size(); ++i) {
        emit spawn(i, playerInfo.characters[i].pos, playerInfo.characters[i].moveMode);
        qDebug() << "spawn: "<< endl;
    }
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

