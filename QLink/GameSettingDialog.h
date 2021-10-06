#ifndef GAMESETTINGDIALOG_H
#define GAMESETTINGDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "GameWindow.h"
#include "MenuSelection.h"

typedef GameWindow::GameMode GameMode;
namespace Ui {
class GameSettingDialog;
}

class GameSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameSettingDialog(QWidget *parent = nullptr);
    ~GameSettingDialog();

    void setGameMode(GameMode gameMode);
private:
    GameMode gameMode;

    Ui::GameSettingDialog *ui;

    bool checkValidation();

    void checkAndStart();

    void returnToMenu();

signals:
    void startGame(int w, int h, GameMode gameMode);

    void selected(MenuSelection::Selection selection);
};

#endif // GAMESETTINGDIALOG_H
