#include "QJsonUtil.h"

QJsonObject QJsonUtil::parseQPoint(const QPoint &p) {
    QJsonObject jsonObj;
    jsonObj.insert("x", p.x());
    jsonObj.insert("y", p.y());
    return jsonObj;
}
