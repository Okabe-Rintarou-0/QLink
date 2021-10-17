#ifndef QCHARACTERWIDGET_H
#define QCHARACTERWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include "FileConstants.h"
#include "DirectionUtil.h"

typedef DirectionUtil::Direction Direction;

class QCharacterWidget : public QWidget {
    Q_OBJECT
public:
    QCharacterWidget(int id);

    enum MoveMode {
        COMMON, FLASH, FROZEN
    };
    /****************************************************
     *                Getter and Setter                 *
     ****************************************************/
    /**
     * @brief 获取当前移动模式
     * @return 当前移动模式
     */
    MoveMode getMoveMode() const;

    /**
    * @brief 设置宽度
    * @param w
    */
    void setWidth(int w);

    /**
     * @brief 设置高度
     * @param h
     */
    void setHeight(int h);

    /**
     * @brief 设置大小
     * @param w 宽度
     * @param h 高度
     */
    void setSize(int w, int h);

    /**
     * @brief 设置大小
     * @param size 大小
     */
    void setSize(const QSize &size);

    /**
     * @brief 设置移动模式
     * @param moveMode 移动模式
     */
    void setMoveMode(MoveMode moveMode);

    /****************************************************
     *                     Action                       *
     ****************************************************/
    /**
     * @brief 在指定位置生成角色
     * @param pos 指定位置
     */
    void spawn(const QPoint &pos);

    /**
     * @brief 朝指定方向移动
     * @param direction 指定方向
     */
    void move(Direction direction);

    /**
     * @brief 获取角色中心点坐标
     * @return 中心点坐标
     */
    QPoint center() const;

    /**
     * @brief 玩家瞬移到目标位置
     * @param targetPos 目标位置
     */
    void dash(const QPoint &targetPos);

protected:
    /**
     * @brief 处理时间相关操作，这里用于处理角色移动速度
     * @param event 时间事件
     */
    void timerEvent(QTimerEvent *event) override;

private:
    QImage character;
    int id;
    int w;
    int h;
    int moveSpeed = 25;

    int moveTimer;

    int notMoveCnt = 10;
    int speedX;
    int speedY;

    MoveMode moveMode = FLASH;

    static constexpr int DEFAULT_MOVE_SPEED = 12;

    /**
     * @brief 限制移动位置并尝试激活身边的方块
     * @param x 下一“帧”即将移动到的点的横坐标
     * @param y 下一“帧”即将移动到的点的纵坐标
     */
    void constrainAndTryActivate(int &x, int &y);

    /**
     * @brief 向上移动
     */
    void moveUp();

    /**
     * @brief 向下移动
     */
    void moveDown();

    /**
     * @brief 向左移动
     */
    void moveLeft();

    /**
     * @brief 向右移动
     */
    void moveRight();

public slots:
    /**
     * @brief 开启dash模式
     * @param id 开启者id
     */
    void startDash(int id);

signals:
    void moveTo(int, const QPoint &);
};

#endif // QCHARACTERWIDGET_H
