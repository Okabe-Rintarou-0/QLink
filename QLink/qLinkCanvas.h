#ifndef QLINKCANVAS_H
#define QLINKCANVAS_H

#include <QWidget>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

class QLinkCanvas : public QWidget {
    Q_OBJECT
public:
    QLinkCanvas() = default;

protected:
    void paintEvent(QPaintEvent *event);

private:
    bool needPaint = false;
    QVector <QPoint> pointsToLink;
    static const QColor DEFAULT_LINE_COLOR;

    void drawLink(QPoint p1, QPoint p2, QPainter &painter, QColor linkColor, int width);

private slots:
    void draw(QVector < QPoint > points);
};

#endif // QLINKCANVAS_H
