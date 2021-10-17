#ifndef IMAGEUTIL_H
#define IMAGEUTIL_H

#include <QImage>

/**
 * @brief 图像工具类
 */
class ImageUtil {
public:
    /**
     * @brief 增加当前图片亮度
     * @param image 待处理图片
     * @param delta 亮度变化值
     */
    static void adjustBrightness(QImage &image, int delta);

    /**
     * @brief 添加边框
     * @param image 待处理图片
     * @param color 边框颜色
     * @param px 边框宽度
     */
    static void setBorder(QImage &image, const QColor &color, int px);
};

#endif // IMAGEUTIL_H
