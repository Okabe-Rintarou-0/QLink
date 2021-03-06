#include "QLinkArchiveManager.h"

QLinkArchiveManager::QLinkArchiveManager() {
    instance = nullptr;
}

QLinkArchiveManager *QLinkArchiveManager::getInstance() {
    if (instance == nullptr) {
        instance = new QLinkArchiveManager;
    }
    return instance;
}

QLinkArchiveManager::~QLinkArchiveManager() {
    delete instance;
}

bool QLinkArchiveManager::loadArchive() const {
    QLinkArchive archive;
    QJsonDocument jdoc;
    //打开文件
    QFile file(FileConstants::ARCHIVE_URL);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() << "File open successfully!";
    }
    QJsonParseError *error = new QJsonParseError;
    jdoc = QJsonDocument::fromJson(file.readAll(), error);

    //判断文件是否完整
    if (error->error != QJsonParseError::NoError) {
        qDebug() << "parseJson:" << error->errorString();
        return false;
    }

//    qDebug() << jdoc.toJson() << endl;
    try {
        archive.parse(jdoc.object());
        QLinkGameController::getInstance()->loadFromArchive(archive.globalInfo);
        QSquarePanelWidget::getInstance()->loadFromArchive(archive.squarePanelInfo);
        QCharacterManager::getInstance()->loadFromArchive(archive.playerInfo);
        QLinkGameController::getInstance()->loadFromArchive(archive.gameItemInfo);
    } catch (JsonParseException e) {
        qDebug() << e.what() << endl;
        return false;
    }
    return true;
}

void QLinkArchiveManager::saveArchive() const {
    QLinkArchive archive;
    archive.buildPlayerPart(QCharacterManager::getInstance()->getPlayerInfo());
    archive.buildGlobalPart(QLinkGameController::getInstance()->getGlobalInfo());
    archive.buildGameItemPart(QLinkGameController::getInstance()->getGameItemInfo());
    archive.buildSquarePart(QSquarePanelWidget::getInstance()->getSquarePanelInfo());

    QJsonObject jsonObj = archive.toJson();

    QJsonDocument jdoc;
    jdoc.setObject(jsonObj);

    //open archive
    QFile file(FileConstants::ARCHIVE_URL);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() << "File open successfully!";
        file.write(jdoc.toJson(QJsonDocument::Indented));
        qDebug() << "write: " << jdoc.toJson(QJsonDocument::Indented) << endl;
        file.close();
    }
}

QLinkArchiveManager *QLinkArchiveManager::instance;
