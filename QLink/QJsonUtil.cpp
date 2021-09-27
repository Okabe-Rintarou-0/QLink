#include "QJsonUtil.h"

QJsonObject QJsonUtil::toJson(const QPoint &p) {
    QJsonObject jsonObj;
    jsonObj.insert("x", p.x());
    jsonObj.insert("y", p.y());
    return jsonObj;
}

QPoint QJsonUtil::toQPoint(const QJsonObject &jsonObj) {
    QPoint p;
    if (jsonObj.contains("x") && jsonObj.contains("y")) {
        p.setX(jsonObj["x"].toInt());
        p.setY(jsonObj["y"].toInt());
    }
    return p;
}
