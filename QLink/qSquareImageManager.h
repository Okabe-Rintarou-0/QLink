#ifndef QSQUAREIMAGELOADER_H
#define QSQUAREIMAGELOADER_H
#include <QMap>
#include <QImage>
#include "fileConstants.h"
class QSquareImageManager
{
public:
    static QSquareImageManager *getInstance();
    QImage getIcon(int iconIndex);
private:
    static QSquareImageManager *instance;
    QMap<int, QImage> iconMap;
    QSquareImageManager();
    ~QSquareImageManager();
};
#endif // QSQUAREIMAGELOADER_H
