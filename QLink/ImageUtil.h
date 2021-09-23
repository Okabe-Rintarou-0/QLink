#ifndef IMAGEUTIL_H
#define IMAGEUTIL_H

#include <QImage>

class ImageUtil {
public:
    static void adjustBrightness(QImage &image, int delta);

    static void setBorder(QImage &image, QColor color, int px);
};

#endif // IMAGEUTIL_H
