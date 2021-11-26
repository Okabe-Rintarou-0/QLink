#include "linkcanvas.h"
#include <QDebug>
#include "QSquarePanelWidget.h"

void LinkCanvas::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPen pen;
    QColor color(147, 196, 125);
    pen.setColor(color);
    pen.setWidth(5);
    painter.setPen(pen);

    qDebug() << "called" << endl;

    int size = linkPoints.size();
    if (size < 2) return;
    for (int i = 0; i < size - 1; ++i) {
        qDebug() << "link " << linkPoints[i] << "to " << linkPoints[i + 1] << endl;
        painter.drawLine(linkPoints[i], linkPoints[i + 1]);
    }
}

void LinkCanvas::renderLinkTrace(const QVector<QPoint> &linkPoints) {
    for (const QPoint &point: linkPoints) {
        this->linkPoints.push_back(QSquarePanelWidget::getInstance()->toRealPoint(point));
    }
    update();

    QTimer::singleShot(700, this, &LinkCanvas::clearLinkTrace);
}

void LinkCanvas::clearLinkTrace() {
    this->linkPoints.clear();
    update();
}
