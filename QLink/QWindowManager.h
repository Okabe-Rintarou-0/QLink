#ifndef QWINDOWMANAGER_H
#define QWINDOWMANAGER_H

#include "GameWindow.h"
#include "QLinkArchiveManager.h"
#include "QLinkMenu.h"
#include "MenuSelection.h"
#include "GameSettingDialog.h"

typedef GameWindow::GameMode GameMode;

class QWindowManager : public QObject {
    Q_OBJECT
private:
    GameWindow *gameWindow;
    QLinkMenu *menu;
    GameSettingDialog *gameSettingDialog;
    static QWindowManager *instance;

    QWindowManager();

    /**
     * @brief 从存档中加载内容内容，是读取存档按键的响应
     */
    void loadArchive();

    /**
     * @brief 返回到菜单，是返回菜单按钮的响应
     */
    void returnMenu();

    /**
     * @brief 开启游戏，是点击单人/双人游戏之后的响应；弹出设置窗口，设置游戏模式
     * @param gameMode 游戏模式
     */
    void startGame(GameMode gameMode);

public:
    /**
     * @brief 单例模式
     */
    static QWindowManager *getInstance();

    ~QWindowManager();

private slots:
    void select(MenuSelection::Selection selection);
};

#endif // QWINDOWMANAGER_H
