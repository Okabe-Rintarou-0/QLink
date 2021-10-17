#ifndef QLINKGAMECONTROLLER_H
#define QLINKGAMECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QSet>
#include <QTimerEvent>
#include "RandomUtil.h"
#include "QLinkGameItem.h"
#include "Jewels.h"
#include "QLinkArchive.h"
#include "QSquarePanelWidget.h"
#include "QCharacterManager.h"

typedef QLinkGameItem::JewelType JewelType;

class QLinkGameController : public QObject {
    Q_OBJECT
public:
    static QLinkGameController *getInstance();

    /**
     * @brief 重置游戏，包括得分，剩余时间；关闭计时器
     */
    void reset();

    /**
     * @brief 重置，打开计时器，开启游戏。
     * */
    void startGame();

    /**
     * @brief 增加游戏得分
     * @param increment 增量
     * */
    void addScore(int increment);

    /**
     * @brief 设置剩余方块数
     * @param restSquares 剩余方块数
     * */
    void setRestSquares(int restSquares);

    /**
     * @brief 增加剩余时间
     * @param sec 增量（秒）
     * */
    void addTime(int sec);

    /**
     * @brief 暂停游戏(关闭计时器)
     */
    void pauseGame();

    /**
     * @brief 继续游戏，和pauseGame作用相反。
     */
    void continueGame();

    /**
     * @brief 结束游戏，重置。
     */
    void endGame();

    /**
     * @brief 对应于按下暂停/继续键的响应。如果已暂停那就开启，反之类似。
     */
    void pauseOrContinue();

    /**
     * @brief 从存档中读取数据，加载时间、得分等数据
     * @param globalInfo 时间、得分等全局数据
     */
    void loadFromArchive(const QGlobalInfo &globalInfo);

    /**
     * @brief 从存档中读取游戏物品信息，比如hintJewel在哪里？
     * @param gameItemInfo 游戏物品信息
     */
    void loadFromArchive(const QGameItemInfo &gameItemInfo);

    /**
     * @brief 为写入存档服务，根据当前状态生成游戏物品信息
     * @return 游戏物品信息
     */
    QGameItemInfo getGameItemInfo() const;

    /**
     * @brief 为写入存档服务，根据当前状态生成游戏全局数据信息（时间、得分等等）
     * @return 全局数据信息
     */
    QGlobalInfo getGlobalInfo() const;

private:
    bool paused = true;
    int score;
    int restSquares;
    int restTime;
    int countDownTimer = -1;
    QSet<QLinkGameItem *> jewels;

    static QLinkGameController *instance;

    QLinkGameController();

    ~QLinkGameController();

    /**
     * @brief 辅助函数，获取游戏物品随机生成位置
     * @return 游戏物品随机生成位置
     */
    QPoint getRandomSpawnPoint();

    /**
     * @brief 开启倒计时（开启时钟）
     */
    void startCountDown();

    /**
     * @brief 倒计时
     */
    void countDown();

    /**
     * @brief 获取指定类型的游戏道具（珠宝）
     * @param jewelType 珠宝类型
     * @return 获取对应的珠宝
     * @warning 由new生成，需要自行delete释放
     */
    QLinkGameItem *getJewel(JewelType jewelType);

    /**
     * @brief 在指定位置生成指定珠宝
     * @param jewelType 珠宝类型
     * @param pos 生成位置
     */
    void spawnJewel(JewelType jewelType, const QPoint &pos);

    /**
     *  @brief 随机生成珠宝
     */
    void randomSpawnJewel();

protected:
    /**
     * @brief 时间相关handler，在该方法内实现时间倒计时
     */
    void timerEvent(QTimerEvent *event) override;

signals:
    void timeChanged(int sec);

    void scoreChanged(const QString &);

    void gameOver(const QString &);

    void spawnJewel(QLinkGameItem *jewel, const QPoint &pos);

private slots:
    void update(int bonus, int restSquares);
};

#endif // QLINKGAMECONTROLLER_H
