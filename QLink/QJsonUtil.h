#ifndef QJSONUTIL_H
#define QJSONUTIL_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPoint>

class QJsonUtil {
public:
    /**
     * @brief 将QPoint 对象转换为QJsonObject对象
     * @param p QPoint对象
     * @return QJsonObject对象
     */
    static QJsonObject toJson(const QPoint &p);

    /**
     * @brief 将QJsonObject对象转换为QPoint对象
     * @param jsonObj
     * @return QPoint对象
     */
    static QPoint toQPoint(const QJsonObject &jsonObj);
};

#endif // QJSONUTIL_H
