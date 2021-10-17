#ifndef GAMESETTINGDIALOG_H
#define GAMESETTINGDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "GameWindow.h"
#include "MenuSelection.h"

/**
 * @brief 游戏菜单窗口
 */
typedef GameWindow::GameMode GameMode;
namespace Ui {
    class GameSettingDialog;
}

class GameSettingDialog : public QDialog {
    Q_OBJECT

public:
    explicit GameSettingDialog(QWidget *parent = nullptr);

    ~GameSettingDialog();

    /**
     * @brief 设置游戏模式
     * @param gameMode
     */
    void setGameMode(GameMode gameMode);

private:
    GameMode gameMode;

    Ui::GameSettingDialog *ui;

    /**
     * @brief 判断玩家选项是否有效
     * @return 如果有效返回true；否则返回false
     */
    bool checkValidation();

    /**
     * @brief 判断并开启游戏
     */
    void checkAndStart();

    /**
     * @brief 返回菜单
     */
    void returnToMenu();

signals:
    void startGame(int w, int h, GameMode gameMode);

    void selected(MenuSelection::Selection selection);
};

#endif // GAMESETTINGDIALOG_H
