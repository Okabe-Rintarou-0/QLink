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
#include "QLinkCanvas.h"
#include "QSquarePanelWidget.h"
#include "QCharacterWidget.h"
#include "QCharacterManager.h"
#include "QPauseContinueButton.h"
#include "QLinkArchiveManager.h"
#include "MenuSelection.h"
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

    enum GameMode { ONE_PLAYER, TWO_PLAYER };

    void startGame(int w, int h, GameMode gameMode = ONE_PLAYER);

    void endGame();

private:
    Ui::MainWindow *ui;
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QCharacterWidget **characters;
    QSquarePanelWidget *squarePanel;
    QLabel *scoreLabel;
    QLinkCanvas *linkCanvas;
    QPushButton *retButton;
    QLabel *heightLabel;
    QLabel *widthLabel;
//    QLabel *hintLabel;
    QLabel *linkStatusLabel;
    QPushButton *saveBtn;
    QLCDNumber *countDownLCD;
    QPauseContinueButton *pauseContinueButton;
    QLinkGameItem *jewel;

    QLinkGameController *gameController;
    QCharacterManager *characterManager;

protected:
    void keyPressEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);
private slots:
    void showGameOverTips(const QString &tips);

    void renderJewel(QLinkGameItem *jewel, const QPoint &pos);

    void spawnCharacter(int id, const QPoint &pos, MoveMode moveMode);

signals:
    void selected(MenuSelection::Selection selection);
};
#endif // MAINWINDOW_H
