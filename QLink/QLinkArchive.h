#ifndef QLINKARCHIVE_H
#define QLINKARCHIVE_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVector>
#include <QPoint>
#include <QJsonArray>
#include "QLinkGameItem.h"
#include "QCharacterWidget.h"
#include "QJsonUtil.h"

typedef QCharacterWidget::MoveMode MoveMode;
typedef QLinkGameItem::JewelType JewelType;

class QCharacterInfo {
public:
    QCharacterInfo(const QPoint &pos, MoveMode moveMode);

    QCharacterInfo() = default;

    ~QCharacterInfo() = default;

    QPoint pos;
    MoveMode moveMode;

    QJsonObject toJson() const;

    void parse(const QJsonObject &jsonObj);
};

class QPlayerInfo {
public:
    QPlayerInfo(const QVector <QCharacterInfo> &characters);

    QPlayerInfo() = default;

    ~QPlayerInfo() = default;

    QVector <QCharacterInfo> characters;

    QJsonObject toJson() const;

    void parse(const QJsonObject &jsonObj);
};

class QSquareInfo {
public:
    QSquareInfo(const QPoint &pos, int iconIndex);

    QSquareInfo() = default;

    ~QSquareInfo() = default;

    QJsonObject toJson() const;

    void parse(const QJsonObject &jsonObj);

    QPoint pos;
    int iconIndex;
};

class QGlobalInfo {
public:
    QGlobalInfo(int restTime, int scores);

    QGlobalInfo() = default;

    ~QGlobalInfo() = default;

    QJsonObject toJson() const;

    void parse(const QJsonObject &jsonObj);

    int restTime;
    int scores;
};

class QJewelInfo {
public:
    QJewelInfo(JewelType jewelType, const QPoint &pos);

    QJewelInfo() = default;

    ~QJewelInfo() = default;

    QJsonObject toJson() const;

    void parse(const QJsonObject &jsonObj);

    JewelType jewelType;
    QPoint pos;
};

class QGameItemInfo {
public:
    QGameItemInfo(const QVector <QJewelInfo> &jewels);

    QGameItemInfo() = default;

    ~QGameItemInfo() = default;

    void addJewel(const QJewelInfo &jewel);

    QJsonObject toJson() const;

    void parse(const QJsonObject &jsonObj);

    QVector <QJewelInfo> jewels;
};

class QSquarePanelInfo {
public:
    int w;
    int h;
    QVector <QSquareInfo> squareInfos;

    QSquarePanelInfo() = default;

    QSquarePanelInfo(const QSize &size, const QVector <QSquareInfo> &squareInfos);

    QSquarePanelInfo(const QSize &size);

    QJsonObject toJson() const;

    void parse(const QJsonObject &jsonObj);

    void addSquareInfo(const QSquareInfo &squareInfo);
};

class QLinkArchive {
public:
    QLinkArchive() = default;

    ~QLinkArchive() = default;

    void buildPlayerPart(const QPlayerInfo &playerInfo);

    void buildSquarePart(const QSquarePanelInfo &squarePanelInfo);

    void buildGlobalPart(const QGlobalInfo &globalInfo);

    void buildGameItemPart(const QGameItemInfo &gameItemInfo);

    QJsonObject toJson() const;

    void parse(const QJsonObject &jsonObj);

    QPlayerInfo playerInfo;
    QSquarePanelInfo squarePanelInfo;
    QGlobalInfo globalInfo;
    QGameItemInfo gameItemInfo;
};

#endif // QLINKARCHIVE_H
