#ifndef QCHARACTERMANAGER_H
#define QCHARACTERMANAGER_H

#include "QCharacterWidget.h"
#include "QLinkArchive.h"
#include "QLinkArchive.h"

class QCharacterManager : public QObject {
    Q_OBJECT
public:
    /**
     * @brief 单例模式
     */
    static QCharacterManager *getInstance();

    /**
     * @brief 根据角色id获取角色组件
     * @param id 角色ID
     * @return 角色组件的指针
     */
    QCharacterWidget *getCharacter(int id);

    /**
     * @brief 添加角色
     * @param character 被添加的角色
     */
    void addCharacter(QCharacterWidget *character);

    /**
     * @brief 冻结所有玩家移动，对应于游戏暂停
     */
    void frozenAll();

    /**
     * @brief 解冻所有玩家，对应于游戏继续
     */
    void unfrozenAll();

    /**
     * @brief 从存档中加载的角色信息实例化角色
     * @param playerInfo 角色信息
     */
    void loadFromArchive(const QPlayerInfo &playerInfo);

    /**
     * @brief 获取角色信息（用于存档）
     * @return 角色信息
     */
    QPlayerInfo getPlayerInfo() const;

private:
    static QCharacterManager *instance;
    QCharacterWidget **characters;

    QCharacterManager();

    ~QCharacterManager();

    QVector <QCharacterInfo> getCharacterInfos() const;

signals:
    void spawn(int id, const QPoint &pos, MoveMode moveMode);
};

#endif // QCHARACTERMANAGER_H
