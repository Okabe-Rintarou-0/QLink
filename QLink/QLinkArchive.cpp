#include "QLinkArchive.h"

QCharacterInfo::QCharacterInfo(const QPoint &pos, MoveMode moveMode) {
    this->pos = pos;
    this->moveMode = moveMode;
}

QJsonObject QCharacterInfo::toJson() const {
    QJsonObject jsonObj;
    jsonObj.insert("pos", QJsonUtil::toJson(pos));
    jsonObj.insert("moveMode", moveMode);
    return jsonObj;
}

void QCharacterInfo::parse(const QJsonObject &jsonObj) {
    if (jsonObj.contains("pos") && jsonObj.contains("moveMode")) {
        pos = QJsonUtil::toQPoint(jsonObj["pos"].toObject());
        moveMode = static_cast<MoveMode>(jsonObj["moveMode"].toInt());
        qDebug() << "Parse: pos = " << pos << " moveMode = " << moveMode << endl;
    }
    else
        throw JsonParseException();
}

QPlayerInfo::QPlayerInfo(const QVector <QCharacterInfo> &characters) {
    this->characters = characters;
}

QJsonObject QPlayerInfo::toJson() const {
    QJsonObject jsonObj;
    QJsonArray characters;
    for (QCharacterInfo character : this->characters) {
        characters.append(character.toJson());
    }
    jsonObj.insert("characters", characters);
    return jsonObj;
}

void QPlayerInfo::parse(const QJsonObject &jsonObj) {
    if (jsonObj.contains("characters")) {
        QJsonArray characters = jsonObj["characters"].toArray();
        int len = characters.size();
        this->characters.clear();
        for (int i = 0; i < len; ++i) {
            QCharacterInfo characterInfo;
            characterInfo.parse(characters[i].toObject());
            this->characters.push_back(characterInfo);
        }
    }
    else
        throw JsonParseException();
}

QSquareInfo::QSquareInfo(const QPoint &pos, int iconIndex, int bonus) {
    this->pos = pos;
    this->iconIndex = iconIndex;
    this->bonus = bonus;
}

QJsonObject QSquareInfo::toJson() const {
    QJsonObject jsonObj;
    jsonObj.insert("pos", QJsonUtil::toJson(pos));
    jsonObj.insert("iconIndex", iconIndex);
    jsonObj.insert("bonus", bonus);
    return jsonObj;
}

void QSquareInfo::parse(const QJsonObject &jsonObj) {
    if (jsonObj.contains("pos") && jsonObj.contains("iconIndex") && jsonObj.contains("bonus")) {
        pos = QJsonUtil::toQPoint(jsonObj["pos"].toObject());
        iconIndex = jsonObj["iconIndex"].toInt();
        bonus = jsonObj["bonus"].toInt();
        qDebug() << "Parse: pos = " << pos << " iconIndex = " << iconIndex << " bonus = " << bonus << endl;
    }
    else
        throw JsonParseException();
}

QSquarePanelInfo::QSquarePanelInfo(const QSize &size) {
    this->w = size.width();
    this->h = size.height();
}

QSquarePanelInfo::QSquarePanelInfo(const QSize &size, const QVector <QSquareInfo> &squareInfos) {
    this->w = size.width();
    this->h = size.height();
    this->squareInfos = squareInfos;
}

void QSquarePanelInfo::addSquareInfo(const QSquareInfo &squareInfo) {
    squareInfos.push_back(squareInfo);
}

QJsonObject QSquarePanelInfo::toJson() const {
    QJsonObject jsonObj;
    QJsonArray squareInfos;
    jsonObj.insert("w", w);
    jsonObj.insert("h", h);
    for (QSquareInfo squareInfo : this->squareInfos) {
        squareInfos.append(squareInfo.toJson());
    }
    jsonObj.insert("squares", squareInfos);
    return jsonObj;
}

void QSquarePanelInfo::parse(const QJsonObject &jsonObj) {
    if (jsonObj.contains("w") && jsonObj.contains("h") && jsonObj.contains("squares")) {
        w = jsonObj["w"].toInt();
        h = jsonObj["h"].toInt();
        qDebug() << "Parse: w = " << w << " h = " << h << endl;
        QJsonArray squares = jsonObj["squares"].toArray();
        int len = squares.size();
        squareInfos.clear();
        for (int i = 0; i < len; ++i) {
            QSquareInfo squareInfo;
            squareInfo.parse(squares[i].toObject());
            squareInfos.push_back(squareInfo);
        }
    }
    else
        throw JsonParseException();
}

QGlobalInfo::QGlobalInfo(int restTime, int fstScores, int secScores) {
    this->restTime = restTime;
    this->scores[0] = fstScores;
    this->scores[1] = secScores;
}

QJsonObject QGlobalInfo::toJson() const {
    QJsonObject jsonObj;
    jsonObj.insert("restTime", restTime);
    jsonObj.insert("fstScores", scores[0]);
    jsonObj.insert("secScores", scores[1]);
    return jsonObj;
}

void QGlobalInfo::parse(const QJsonObject &jsonObj) {
    if (jsonObj.contains("restTime") && jsonObj.contains("fstScores") && jsonObj.contains("secScores")) {
        restTime = jsonObj["restTime"].toInt();
        scores[0] = jsonObj["fstScores"].toInt();
        scores[1] = jsonObj["secScores"].toInt();
        qDebug() << "Parse: scores = " << scores[0] << " and " << scores[1] << " restTime = " << restTime << endl;
    }
    else
        throw JsonParseException();
}

QJewelInfo::QJewelInfo(JewelType jewelType, const QPoint &pos) {
    this->jewelType = jewelType;
    this->pos = pos;
}

QJsonObject QJewelInfo::toJson() const {
    QJsonObject jsonObj;
    jsonObj.insert("pos", QJsonUtil::toJson(pos));
    jsonObj.insert("jewelType", jewelType);
    return jsonObj;
}

void QJewelInfo::parse(const QJsonObject &jsonObj) {
    if (jsonObj.contains("pos") && jsonObj.contains("jewelType")) {
        pos = QJsonUtil::toQPoint(jsonObj["pos"].toObject());
        jewelType = static_cast<JewelType>(jsonObj["jewelType"].toInt());
        qDebug() << "Parse: pos = " << pos << " jewelType = " << jewelType << endl;
    }
    else
        throw JsonParseException();
}

QGameItemInfo::QGameItemInfo(const QVector <QJewelInfo> &jewels) {
    this->jewels = jewels;
}

void QGameItemInfo::addJewel(const QJewelInfo &jewel) {
    jewels.append(jewel);
}

QJsonObject QGameItemInfo::toJson() const {
    QJsonObject jsonObj;
    QJsonArray jewels;
    for (QJewelInfo jewel : this->jewels) {
        jewels.append(jewel.toJson());
    }
    jsonObj.insert("jewels", jewels);
    return jsonObj;
}

void QGameItemInfo::parse(const QJsonObject &jsonObj) {
    if (jsonObj.contains("jewels")) {
        QJsonArray jewels = jsonObj["jewels"].toArray();
        int len = jewels.size();
        this->jewels.clear();
        for (int i = 0; i < len; ++i) {
            QJewelInfo jewelInfo;
            jewelInfo.parse(jewels[i].toObject());
            this->jewels.push_back(jewelInfo);
        }
    }
    else
        throw JsonParseException();
}

QJsonObject QLinkArchive::toJson() const {
    QJsonObject jsonObj;
    jsonObj.insert("playerInfo", playerInfo.toJson());
    jsonObj.insert("squarePanelInfo", squarePanelInfo.toJson());
    jsonObj.insert("globalInfo", globalInfo.toJson());
    jsonObj.insert("gameItemInfo", gameItemInfo.toJson());
    return jsonObj;
}

void QLinkArchive::parse(const QJsonObject &jsonObj) {
    if (jsonObj.contains("playerInfo") && jsonObj.contains("squarePanelInfo") && jsonObj.contains("globalInfo") &&
        jsonObj.contains("gameItemInfo")) {
        playerInfo.parse(jsonObj["playerInfo"].toObject());
        squarePanelInfo.parse(jsonObj["squarePanelInfo"].toObject());
        globalInfo.parse(jsonObj["globalInfo"].toObject());
        gameItemInfo.parse(jsonObj["gameItemInfo"].toObject());
    }
    else
        throw JsonParseException();
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
