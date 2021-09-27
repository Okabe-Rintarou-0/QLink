#ifndef QJSONUTIL_H
#define QJSONUTIL_H
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPoint>

class QJsonUtil
{
public:
    static QJsonObject toJson(const QPoint &p);

    static QPoint toQPoint(const QJsonObject &jsonObj);
};

#endif // QJSONUTIL_H
