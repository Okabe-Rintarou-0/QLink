#ifndef QSQUAREPANELWIDGET_H
#define QSQUAREPANELWIDGET_H

#include <QWidget>
#include <QQueue>
#include <QVector>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
#include <QTimer>
#include "QLinkGameController.h"
#include "RandomUtil.h"
#include "QLinkArchive.h"
#include "QLinkSquare.h"
#include "DirectionUtil.h"
#include "QUnitTest.h"

class QSquarePanelWidget : public QWidget {
    Q_OBJECT
private:
    enum RunMode {
        COMMON, HINT
    } runMode = COMMON;
    static int next[4][2];
    int h;
    int w;
    int squareSpacing;
    int restSquares;
    static const QPair <QPoint, QPoint> INVALID_PAIR;
    static const int DEFAULT_SPACING = 5;
    static const int DEFAULT_H = 10;
    static const int DEFAULT_W = 20;
    static const QColor DEFAULT_LINE_COLOR;
    QVector <QPoint> path;
    QVector <QVector<QLinkSquare *>> squares;
    QGridLayout *gridLayout;
    QVector <QQueue<QPoint>> activateQueue;
    QVector <QQueue<QPoint>> selectQueue;
    QVector <QVector<int>> squareMap;
    QMap<int, QVector<QPoint>> squarePosMap;
    QPair <QPoint, QPoint> linkablePairCache = qMakePair(QPoint(-1, -1), QPoint(-1, -1));

    QSquarePanelWidget();

    /****************************************************
     *                  UI Concerned                    *
     ****************************************************/
    /**
     * @brief 普通情况下渲染方块
     */
    void renderSquares();

    /**
     * @brief 根据存档中获取并解析的方块信息渲染方块
     * @param squareInfos 存档中获取并解析的方块信息
     */
    void renderSquares(const QVector <QSquareInfo> &squareInfos);

    /**
     * @brief 配置gridlayout
     */
    void setUpGridLayout();

    /**
     * @brief 高亮对应位置的方块（开启hint模式之后的效果）
     * @param p 方块的坐标
     */
    void highlightAt(const QPoint &p);

    /**
     * @brief 可以在里面放一些渲染后做的工作，比如初始化
     */
    void onRender();

    /****************************************************
     *                  Operations                      *
     ****************************************************/
    /**
     * @brief 提示下一个（吃了hint道具之后）
     */
    void hintNext();

    /**
     * @brief 搜索是否当前存在着可以连接的方块
     * @return 若存在返回true；否则返回false。
     */
    bool searchLinkableSquare();

    /**
     * @brief 尝试连接
     * @param idx对应于activateQueue[idx] 每个玩家对应一个激活方块队列
     */
    void tryLink(int idx);

    /**
     * @brief 连接两个方块（对应check成功的情况）
     * @return 两个方块的坐标p1, p2。
     */
    void link(const QPoint &p1, const QPoint &p2);

    /**
     * @brief 取消连接（对应check失败的情况）
     * @param 两个方块的坐标p1, p2。
     */
    void cancelLink(const QPoint &p1, const QPoint &p2);

    /****************************************************
     *                  Aux function                    *
     ****************************************************/
    /**
     * @brief 初始化squarePosMap squarePosMap存放相同种类的方块的坐标，为检测是否可连接方块提供便利
     */
    void initSquarePosMap();

    /**
     * @brief 初始化squareMap，为连接检测做准备。
     */
    void initSquareMap();

    /**
     * @brief 生成玩家可到达的方块数组
     * @param reachablePoints 玩家可到达的方块
     */
    void fetchReachable(QVector<QVector<bool>> &reachable);

    /**
     * @brief 移除方块
     * @param 方块坐标(x, y)
     */
    void removeSquareAt(int x, int y);

    /**
     * @brief 移除方块
     * @param 方块坐标QPoint(x, y)
     */
    void removeSquareAt(QPoint);

    /**
     * @brief 更新缓存（缓存是用来存储可连接的方块对的，如果检测过存在方块可连接，并且没有被消除的话就没有必要再次搜索）
     * @param 两个方块的坐标p1, p2
     */
    void updateCache(const QPoint &p1, const QPoint &p2);

    /**
     * @brief 边界检测
     * @param squareMap中的坐标p
     * @return 判断是否越界，若越界返回true；否则返回false。
     */
    bool outOfBound(const QPoint &p) const;

    /**
     * @brief 判断是否坐标p是可以通过的（连连看的连线可以通过）
     * @param squareMap中的坐标p
     * @return 如果可以经过那就返回true；否则返回false。
     */
    bool canPassBy(const QPoint &p) const;

    /**
     * @brief 为生成随机地图做的准备工作
     * @param 两个map分别存储生成的随机方块数量和随机奖励 即<index, num> & <index, bonus>
     */
    void prepareRandom(QMap<int, int> &, QMap<int, int> &);

    /**
     * @brief 将消除的方块周围的方块加入squarePosMap（因为这些方块都变为可达到的）
     * @param p 消除的方块坐标
     */
    void expandReachable(const QPoint &p);

    /****************************************************
    *                 Checking logic                   *
    ****************************************************/

    /**
     * @brief 测试竖直连接
     * @param p1, p2待测连接方块的坐标
     * @return 如果可连接，返回true；否则返回false。
     */
    bool checkVertical(const QPoint &p1, const QPoint &p2) const;

    /**
     * @brief 测试水平连接
     * @param p1, p2待测连接方块的坐标
     * @return 如果可连接，返回true；否则返回false。
     */
    bool checkHorizontal(const QPoint &p1, const QPoint &p2) const;

    /**
     * @brief 测试直线情况 即 checkVertical(p1, p2) || checkHorizontal(p1, p2)
     * @param p1, p2待测连接方块的坐标
     * @return 如果可连接，返回true；否则返回false。
     */
    bool checkStraightLine(const QPoint &p1, const QPoint &p2) const;

    /**
     * @brief 测试一个拐角的情况
     * @param p1, p2待测连接方块的坐标
     * @return 如果可连接，返回true；否则返回false。
     */
    bool checkOneCorner(const QPoint &p1, const QPoint &p2) const;

    /**
     * @brief 测试两个拐角的情况
     * @param p1, p2待测连接方块的坐标
     * @return 如果可连接，返回true；否则返回false。
     */
    bool checkTwoCorner(const QPoint &p1, const QPoint &p2) const;

    /**
     * @brief 测试两个方块是否是可连接的
     * @param p1, p2待测连接方块的坐标
     * @return 如果可连接，返回true；否则返回false。
     */
    bool isLinkable(const QPoint &p1, const QPoint &p2) const;

    /**
     * @brief 是否存在可以连接的方块
     * @return 如果存在返回true，若不存在返回false。
     */
    bool existsLinkableSquare();

    /****************************************************
     *                 Point Transform                  *
     ****************************************************/

    /**
     * @brief 面板中的坐标(x, y) => squareMap中的坐标(mx, my)
     * @param 面板中的坐标(x, y)
     * @return squareMap中的坐标QPoint(mx, my)
     */
    QPoint toMapPoint(int x, int y) const;

    /**
     * @return toMapPoint(p.x(), p.y())
     */
    QPoint toMapPoint(const QPoint &p) const;

    /**
     * @brief 在gamewindow的位置p => 在方块面板中的坐标
     * @param p 在gamewindow的位置p
     * @return 在方块面板中的坐标
     */
    QPoint toGridPos(const QPoint &p) const;

    static QSquarePanelWidget *instance;
public:
    friend class QUnitTest;

    /**
     * @brief 单例模式
     */
    static QSquarePanelWidget *getInstance();

    ~QSquarePanelWidget();

    /**
     * @brief 尝试激活方块 先选中 再次靠近激活
     * @param idx 玩家对应的索引，玩家0为0，玩家1为1
     */
    void tryActivate(int idx, const QPoint &fromPos);

    /**
     * @brief 激活方块
     * @param idx 玩家对应的索引，玩家0为0，玩家1为1
     * @param gridPos 在面板上的坐标
     */
    void activate(int idx, const QPoint &gridPos);

    /**
     * @brief 设置面板大小
     * @param w 新的宽度
     * @param h 新的高度
     */
    void setSize(int h, int w);

    /**
     * @brief 渲染
     */
    void render();

    /**
     * @brief 清除面板
     */
    void clear();

    /**
     * @brief 修改面板大小并重新渲染
     * @param w 新的宽度
     * @param h 新的高度
     */
    void resizeAndRender(int w, int h);

    /**
     * @brief 根据存档内容生成方块面板
     * @param squarePanelInfo 从存档中读取并解析出来的方块面板信息
     */
    void loadFromArchive(const QSquarePanelInfo &squarePanelInfo);

    /**
     * @brief 打乱所有方块
     */
    void shuffle();

    /**
     * @brief 判断是否指定位置存在方块，若存在则不可通过。
     * @param pos 指定位置
     * @return 若存在，返回true；反之返回false。
     */
    bool existsSquare(const QPoint &pos);

    /**
     * @brief 返回面板信息供存档使用
     * @return 存档信息
     */
    QSquarePanelInfo getSquarePanelInfo() const;

    void startHint();

    /****************************************************
     *                Getter and Setter                 *
     ****************************************************/
    /**
     * @brief 返回方块大小 w*h
     * @return 方块大小 QSize(w, h)
     */
    QSize getSquareSize() const;

    /**
     * @brief 返回面板大小 w*h
     * @return 面板大小 QSize(w, h)
     */
    QSize getSize() const;

    /**
     * @brief 返回指定方块的奖励
     * @param p 方块的在面板的坐标
     * @return 指定方块的奖励
     */
    int getBonus(const QPoint &p);

    signals:
            void tryLink(
    const QString &status
    );

    void linked(int bonus, int restSquares);
};

#endif // QSQUAREPANELWIDGET_H
