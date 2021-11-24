#ifndef QUNITTEST_H
#define QUNITTEST_H

#include <QtTest/QtTest>
#include "QLinkSquare.h"
#include "QLinkArchive.h"
#include "QSquarePanelWidget.h"

class QSquarePanelWidget;

class QUnitTest : public QObject {
    Q_OBJECT
private:
    QSquarePanelWidget *squarePanel;

    /**
     * @brief 测试初始化工作
     */
    void init();

    /**
     * @brief 生成无法连接的地图
     */
    void formNotLinkableMap();

    /**
     * @brief 转换到map point
     * @note 实际上在连连看地图上，如果方格是N*M，那么可连线范围则是(N + 1)*(M + 1)，多了一个外围的区域
     * @note 所以实际上map point就是将(row, col)网格坐标映射到(row - 1, col - 1)的地图坐标
     * @param x 网格横坐标
     * @param y 网格纵坐标
     * @return 地图坐标mp
     */
    QPoint mp(int x, int y) const;

private slots:
    /**
     * @brief 测试横向直线连接
     */
    void testHorizontal();

    /**
     * @brief 测试纵向直线连接
     */
    void testVertical();

    /**
     * @brief 测试直线连接
     */
    void testStraightLine();

    /**
     * @brief 测试一个拐角连接
     */
    void testOneCorner();

    /**
     * @brief 测试两个拐角连接
     */
    void testTwoCorner();

    /**
     * @brief 测试整体连接判断
     */
    void testIsLinkable();

    /**
     * @brief testExistsLinkable
     */
    void testExistsLinkable();

public:
    QUnitTest();
};

#endif // QUNITTEST_H
