#include "QLinkArchive.h"

QCharacterInfo::QCharacterInfo(const QPoint &pos, MoveMode moveMode) {
    this->pos = pos;
    this->moveMode = moveMode;
}

QSquareInfo::QSquareInfo(const QPoint &pos, int iconIndex) {
    this->pos = pos;
    this->iconIndex = iconIndex;
}

QSquarePanelInfo::QSquarePanelInfo(const QSize &size) {
    this->size = size;
}

QSquarePanelInfo::QSquarePanelInfo(const QSize &size, const QVector<QSquareInfo> &squareInfos) {
    this->size = size;
    this->squareInfos = squareInfos;
}

void QSquarePanelInfo::addSquareInfo(const QSquareInfo &squareInfo) {
    squareInfos.push_back(squareInfo);
}

void QLinkArchive::buildCharacterPart(const QVector<QCharacterInfo> &characterInfos) {
    this->characterInfos = characterInfos;
}

void QLinkArchive::buildSquarePart(const QSquarePanelInfo &squarePanelInfo) {
    this->squarePanelInfo = squarePanelInfo;
}
