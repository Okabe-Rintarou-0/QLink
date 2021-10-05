#ifndef GAMESETTINGDIALOG_H
#define GAMESETTINGDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "GameWindow.h"

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

signals:
    void startGame(int w, int h, GameMode gameMode);
};

#endif // GAMESETTINGDIALOG_H
