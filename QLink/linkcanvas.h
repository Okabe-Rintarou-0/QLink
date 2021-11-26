#ifndef LINKCANVAS_H
#define LINKCANVAS_H
#include <QWidget>
#include <QTimer>
#include <QPainter>

class LinkCanvas: public QWidget
{
Q_OBJECT
public:
    LinkCanvas() = default;
    ~LinkCanvas() = default;

    /**
     * @brief 渲染连接线
     * @param linkPoints 连接线的点（仅包含拐点和初始点以及终点）
     */
    void renderLinkTrace(const QVector<QPoint> &linkPoints);

    /**
     * @brief 清除连线
     */
    void clearLinkTrace();

private:
    QVector<QPoint> linkPoints;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // LINKCANVAS_H
