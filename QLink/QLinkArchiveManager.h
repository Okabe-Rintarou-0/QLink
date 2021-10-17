#ifndef QLINKARCHIVEMANAGER_H
#define QLINKARCHIVEMANAGER_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "QLinkArchive.h"
#include "QCharacterManager.h"
#include "QLinkGameController.h"
#include "FileConstants.h"

/**
 * @brief 存档管理类
 */
class QLinkArchiveManager {
private:
    QLinkArchiveManager();

    static QLinkArchiveManager *instance;

public:
    ~QLinkArchiveManager();

    /**
     * @brief 单例模式
     */
    static QLinkArchiveManager *getInstance();

    /**
     * @brief 加载存档并更新相应组件
     * @return 若解析存档成功返回true；否则返回false
     */
    bool loadArchive() const;

    /**
     * @brief 保存存档到本地文件
     */
    void saveArchive() const;
};

#endif // QLINKARCHIVEMANAGER_H
