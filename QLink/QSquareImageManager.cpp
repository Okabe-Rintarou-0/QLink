#include "QSquareImageManager.h"

QSquareImageManager::QSquareImageManager()
{
    instance = nullptr;
}

QSquareImageManager::~QSquareImageManager()
{
    delete instance;
}

QSquareImageManager *QSquareImageManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new QSquareImageManager();
    }
    return instance;
}

QImage QSquareImageManager::getIcon(int iconIndex)
{
    if (!iconMap.contains(iconIndex))
    {
        QImage image;
        QString urlFormat = "%1%2.png";
        image.load(urlFormat.arg(FileConstants::ICON_URL).arg(iconIndex));
        iconMap.insert(iconIndex, image);
    }
    return iconMap[iconIndex];
}

QSquareImageManager *QSquareImageManager::instance;
