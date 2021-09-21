#include "QLinkCanvas.h"

void QLinkCanvas::paintEvent(QPaintEvent *event) {
    qDebug() << "called pe" << endl;
    if (!needPaint) return;
    event->accept();
    QPainter painter(this);
    for (int i = 0; i < pointsToLink.size() - 1; ++i) {
        drawLink(pointsToLink[i], pointsToLink[i + 1], painter, DEFAULT_LINE_COLOR, 4);
    }
    needPaint = false;
}

void QLinkCanvas::draw(QVector <QPoint> points) {
    pointsToLink = points;
    needPaint = true;
    qDebug() << "called" << endl;
    repaint();
}

void QLinkCanvas::drawLink(QPoint p1, QPoint p2, QPainter &painter, QColor linkColor, int width) {
    qDebug() << "draw from " << p1 << " to " << p2 << endl;
    painter.setBrush(QBrush(linkColor));
    QPoint topLeft = p1.x() < p2.x() ?
                     QPoint(p1.x(), p1.y() - width / 2) : QPoint(p2.x(), p2.y() - width / 2);
    QPoint bottomRight = p1.x() < p2.x() ?
                         QPoint(p2.x(), p2.y() + width / 2) : QPoint(p1.x(), p1.y() + width / 2);
    QRect rect(topLeft, bottomRight);
    painter.drawRect(rect);
}

const QColor QLinkCanvas::DEFAULT_LINE_COLOR = Qt::black;
