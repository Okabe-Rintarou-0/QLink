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
#include "JsonParseException.h"

typedef QCharacterWidget::MoveMode MoveMode;
typedef QLinkGameItem::JewelType JewelType;

/**
 *  @file     QLinkArchive.h
 *  @brief    该类存储所有和存档相关的对象。
 *  @details  每个对象都存在两个函数toJson和parse
 *
 *  @fn       toJson
 *  @brief    把当前对象转换成QJsonObject对象
 *  @return   QJsonObject对象
 *
 *  @fn       parse
 *  @brief    解析QJsonObject对象
 *  @param    jsonObj QJsonObject对象
 */

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
    QSquareInfo(const QPoint &pos, int iconIndex, int bonus);

    QSquareInfo() = default;

    ~QSquareInfo() = default;

    QJsonObject toJson() const;

    void parse(const QJsonObject &jsonObj);

    QPoint pos;
    int iconIndex;
    int bonus;
};

class QGlobalInfo {
public:
    QGlobalInfo(int restTime, int fstScores, int secScores);

    QGlobalInfo() = default;

    ~QGlobalInfo() = default;

    QJsonObject toJson() const;

    void parse(const QJsonObject &jsonObj);

    int restTime;
    int scores[2];
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
