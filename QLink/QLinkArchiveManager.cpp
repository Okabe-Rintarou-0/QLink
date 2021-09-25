#include "QLinkArchiveManager.h"

QLinkArchiveManager::QLinkArchiveManager(){
    instance = nullptr;
}

QLinkArchiveManager *QLinkArchiveManager::getInstance() {
    if (instance == nullptr) {
        instance = new QLinkArchiveManager;
    }
    return instance;
}

QLinkArchive QLinkArchiveManager::loadArchive() const {
    QLinkArchive archive;
//    archive.buildCharacterPart(QChara)
}

void QLinkArchiveManager::saveArchive() const {
    QLinkArchive archive;
    archive.buildPlayerPart(QCharacterManager::getInstance()->getPlayerInfo());
    archive.buildGlobalPart(QLinkGameController::getInstance()->getGlobalInfo());
    archive.buildGameItemPart(QLinkGameController::getInstance()->getGameItemInfo());
    archive.buildSquarePart(QSquarePanelWidget::getInstance()->getSquarePanelInfo());

    //open archive
    QString archiveUrl = FileConstants::ARCHIVE_URL;
    QFile file(archiveUrl);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() <<"File open successfully!";
    }

    QJsonObject jsonObj;

}

QLinkArchiveManager *QLinkArchiveManager::instance;
