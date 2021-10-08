#ifndef QLINKARCHIVEMANAGER_H
#define QLINKARCHIVEMANAGER_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "QLinkArchive.h"
#include "QCharacterManager.h"
#include "QLinkGameController.h"
#include "FileConstants.h"

class QLinkArchiveManager {
private:
    QLinkArchiveManager();

    static QLinkArchiveManager *instance;

public:
    ~QLinkArchiveManager();

    bool loadArchive() const;

    void saveArchive() const;

    static QLinkArchiveManager *getInstance();
};

#endif // QLINKARCHIVEMANAGER_H
