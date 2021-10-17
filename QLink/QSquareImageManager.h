#ifndef QSQUAREIMAGELOADER_H
#define QSQUAREIMAGELOADER_H

#include <QMap>
#include <QImage>
#include "FileConstants.h"

/**
 * @brief 本质上是参考Unity常用的对象池，放置多次无谓的创建
 */
class QSquareImageManager {
public:
    /**
     * @brief 单例模式
     */
    static QSquareImageManager *getInstance();

    /**
     * @brief 根据图标ID获取图标
     * @param iconIndex 图标ID
     * @return 图标QImage对象
     */
    QImage getIcon(int iconIndex);

private:
    static QSquareImageManager *instance;
    QMap<int, QImage> iconMap;

    QSquareImageManager();

    ~QSquareImageManager();
};

#endif // QSQUAREIMAGELOADER_H
