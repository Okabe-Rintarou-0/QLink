#ifndef QJSONUTIL_H
#define QJSONUTIL_H
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPoint>

class QJsonUtil
{
public:
    static QJsonObject parseQPoint(const QPoint &p);
};

#endif // QJSONUTIL_H
