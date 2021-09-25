#include "QLinkArchive.h"

QCharacterInfo::QCharacterInfo(const QPoint &pos, MoveMode moveMode) {
    this->pos = pos;
    this->moveMode = moveMode;
}

QJsonObject QCharacterInfo::parse() const {
    QJsonObject jsonObj;
    jsonObj.insert("pos", QJsonUtil::parseQPoint(pos));
    jsonObj.insert("moveMode", moveMode);
    return jsonObj;
}

QPlayerInfo::QPlayerInfo(const QVector<QCharacterInfo> &characters) {
    this->characters = characters;
}

QJsonObject QPlayerInfo::parse() const {
    QJsonObject jsonObj;
    QJsonArray characters;
    for (QCharacterInfo character : this->characters) {
        characters.append(character.parse());
    }
    jsonObj.insert("characters", characters);
    return jsonObj;
}

QSquareInfo::QSquareInfo(const QPoint &pos, int iconIndex) {
    this->pos = pos;
    this->iconIndex = iconIndex;
}

QJsonObject QSquareInfo::parse() const {
    QJsonObject jsonObj;
    jsonObj.insert("pos", QJsonUtil::parseQPoint(pos));
    jsonObj.insert("iconIndex", iconIndex);
    return jsonObj;
}

QSquarePanelInfo::QSquarePanelInfo(const QSize &size) {
    this->w = size.width();
    this->h = size.height();
}

QSquarePanelInfo::QSquarePanelInfo(const QSize &size, const QVector<QSquareInfo> &squareInfos) {
    this->w = size.width();
    this->h = size.height();
    this->squareInfos = squareInfos;
}

QJsonObject QSquarePanelInfo::parse() const {
    QJsonObject jsonObj;
    QJsonArray squareInfos;
    jsonObj.insert("w", w);
    jsonObj.insert("h", h);
    for (QSquareInfo squareInfo : this->squareInfos) {
        squareInfos.append(squareInfo.parse());
    }
    jsonObj.insert("squares", squareInfos);
    return jsonObj;
}

QGlobalInfo::QGlobalInfo(int restTime, int scores) {
    this->restTime = restTime;
    this->scores = scores;
}

QJsonObject QGlobalInfo::parse() const {
    QJsonObject jsonObj;
    jsonObj.insert("restTime", restTime);
    jsonObj.insert("scores", scores);
    return jsonObj;
}

QJewelInfo::QJewelInfo(JewelType jewelType, const QPoint &pos) {
    this->jewelType = jewelType;
    this->pos = pos;
}

QJsonObject QJewelInfo::parse() const {
    QJsonObject jsonObj;
    jsonObj.insert("pos", QJsonUtil::parseQPoint(pos));
    jsonObj.insert("jewelType", jewelType);
    return jsonObj;
}

QGameItemInfo::QGameItemInfo(const QVector<QJewelInfo> &jewels) {
    this->jewels = jewels;
}

void QGameItemInfo::addJewel(const QJewelInfo &jewel) {
    jewels.append(jewel);
}

QJsonObject QGameItemInfo::parse() const {
    QJsonObject jsonObj;
    QJsonArray jewels;
    for (QJewelInfo jewel : this->jewels) {
        jewels.append(jewel.parse());
    }
    jsonObj.insert("jewels", jewels);
    return jsonObj;
}

void QSquarePanelInfo::addSquareInfo(const QSquareInfo &squareInfo) {
    squareInfos.push_back(squareInfo);
}

QJsonObject QLinkArchive::parse() const {
    QJsonObject jsonObj;
    jsonObj.insert("playerInfo", playerInfo.parse());
    jsonObj.insert("squarePanelInfo", squarePanelInfo.parse());
    jsonObj.insert("gloabalInfo", globalInfo.parse());
    jsonObj.insert("gameItemInfo", gameItemInfo.parse());
    return jsonObj;
}

void QLinkArchive::buildPlayerPart(const QPlayerInfo &playerInfo) {
    this->playerInfo = playerInfo;
}

void QLinkArchive::buildSquarePart(const QSquarePanelInfo &squarePanelInfo) {
    this->squarePanelInfo = squarePanelInfo;
}

void QLinkArchive::buildGlobalPart(const QGlobalInfo &globalInfo) {
    this->globalInfo = globalInfo;
}

void QLinkArchive::buildGameItemPart(const QGameItemInfo &gameItemInfo) {
    this->gameItemInfo = gameItemInfo;
}
