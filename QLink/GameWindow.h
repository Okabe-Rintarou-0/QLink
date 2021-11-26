#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QMessageBox>
#include <QMouseEvent>
#include "QLinkGameController.h"
#include "QSquarePanelWidget.h"
#include "QCharacterWidget.h"
#include "QCharacterManager.h"
#include "QPauseContinueButton.h"
#include "QLinkArchiveManager.h"
#include "MenuSelection.h"
#include "linkcanvas.h"
#include "Jewels.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef QCharacterWidget::MoveMode MoveMode;

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);

    ~GameWindow();

    enum GameMode {
        ONE_PLAYER, TWO_PLAYER
    };

    /**
     * @brief 初始化工作
     */
    void init();

    /**
     * @brief 开启游戏
     * @param w 方块面板宽度
     * @param h 方块面板高度
     * @param gameMode 游戏模式
     */
    void startGame(int w, int h, GameMode gameMode = ONE_PLAYER);

    /**
     * @brief 结束游戏
     */
    void endGame();

private:
    Ui::MainWindow *ui;
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QCharacterWidget **characters;
    QSquarePanelWidget *squarePanel;
    QLabel *scoreLabels;
    QPushButton *retButton;
    QLabel *heightLabel;
    QLabel *widthLabel;
    QLabel *linkStatusLabel;
    QPushButton *saveBtn;
    QLCDNumber *countDownLCD;
    QPauseContinueButton *pauseContinueButton;
    QLinkGameItem *jewel;

    LinkCanvas *canvas;

    QLinkGameController *gameController;
    QCharacterManager *characterManager;

protected:
    void keyPressEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);

private slots:
    /**
     * @brief 以MessageBox的形式显示游戏结束信息
     */
    void showGameOverTips(const QString &tips);

    /**
     * @brief 渲染珠宝
     * @param jewel 待渲染的珠宝
     * @param pos 渲染位置
     */
    void renderJewel(QLinkGameItem *jewel, const QPoint &pos);

    /**
     * @brief 生成角色
     * @param id 角色ID
     * @param pos 角色生成位置
     * @param moveMode 当前游戏模式
     */
    void spawnCharacter(int id, const QPoint &pos, MoveMode moveMode);

signals:
    void selected(MenuSelection::Selection selection);
};

#endif // MAINWINDOW_H
