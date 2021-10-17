#include "ImageUtil.h"
#include <QDebug>

//Adjust the brightness of given image.
//Not stable, exists bugs, dont use.
void ImageUtil::adjustBrightness(QImage &image, int delta) {
    QImage newImage = QImage(image.width(), image.height(), QImage::Format_ARGB32);

    QColor oldColor;
    int r, g, b;
    int oldR, oldG, oldB;
    int w = newImage.width();
    int h = newImage.height();

    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            oldColor = QColor(image.pixel(x, y));
            oldR = oldColor.red();
            oldG = oldColor.green();
            oldB = oldColor.blue();
            if (oldR == 0 && oldG == 0 && oldB == 0)
                continue;
            r = qBound(0, oldR + delta, 255);
            b = qBound(0, oldB + delta, 255);
            g = qBound(0, oldG + delta, 255);
            newImage.setPixel(x, y, qRgb(r, g, b));
        }
    }
    image = newImage;
}

//Stable.
//Set image border.
void ImageUtil::setBorder(QImage &image, const QColor &color, int px) {
    QImage newImage = QImage(image.width(), image.height(), QImage::Format_ARGB32);
    QColor oldColor;
    int w = newImage.width();
    int h = newImage.height();
    int r = color.red();
    int g = color.green();
    int b = color.blue();

    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < px; ++y) {
            newImage.setPixel(x, y, qRgb(r, g, b));
        }
        for (int y = h - px; y < h; ++y) {
            newImage.setPixel(x, y, qRgb(r, g, b));
        }
    }

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < px; ++x) {
            newImage.setPixel(x, y, qRgb(r, g, b));
        }
        for (int x = w - px; x < w; ++x) {
            newImage.setPixel(x, y, qRgb(r, g, b));
        }
    }

    for (int x = px; x < w - px; ++x)
        for (int y = px; y < h - px; ++y)
            newImage.setPixel(x, y, image.pixel(x, y));
    image = newImage;
}
