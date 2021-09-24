#ifndef QLINKARCHIVE_H
#define QLINKARCHIVE_H
#include <QVector>
#include <QPoint>
#include <QJsonArray>
#include "QLinkGameItem.h"
#include "QCharacterWidget.h"

typedef QCharacterWidget::MoveMode MoveMode;
typedef QLinkGameItem::JewelType JewelType;
class QCharacterInfo {
public:
    QCharacterInfo(const QPoint &pos, MoveMode moveMode);
    QCharacterInfo() = default;
    ~QCharacterInfo() = default;
    QPoint pos;
    MoveMode moveMode;
};

class QSquareInfo {
public:
    QSquareInfo(const QPoint &pos, int iconIndex);
    QSquareInfo() = default;
    ~QSquareInfo() = default;
    QPoint pos;
    int iconIndex;
};

class QGlobalInfo {
public:
    int restTime;
    int scores;
};

class QJewelInfo {
public:
    JewelType jewelType;
    QPoint pos;
};

class QSquarePanelInfo {
public:
    QSize size;
    QVector<QSquareInfo> squareInfos;

    QSquarePanelInfo(const QSize &size, const QVector<QSquareInfo> &squareInfos);

    QSquarePanelInfo(const QSize &size);

    void addSquareInfo(const QSquareInfo &squareInfo);
};

class QLinkArchive {
public:
//    QLinkArchive() = default;
    ~QLinkArchive() = default;
private:
    QVector<QCharacterInfo> characterInfos;
    QSquarePanelInfo squarePanelInfo;
    QGlobalInfo globalInfo;
    QJewelInfo jewelInfo;

    void buildCharacterPart(const QVector<QCharacterInfo> &characterInfos);

    void buildSquarePart(const QSquarePanelInfo &squarePanelInfo);
};

#endif // QLINKARCHIVE_H
