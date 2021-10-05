#ifndef QWINDOWMANAGER_H
#define QWINDOWMANAGER_H
#include "GameWindow.h"
#include "QLinkArchiveManager.h"
#include "QLinkMenu.h"
#include "MenuSelection.h"
#include "GameSettingDialog.h"

typedef GameWindow::GameMode GameMode;
class QWindowManager: public QObject
{
    Q_OBJECT
private:
    GameWindow *gameWindow;
    QLinkMenu *menu;
    GameSettingDialog *gameSettingDialog;
    static QWindowManager *instance;

    QWindowManager();

    void loadArchive();

    void returnMenu();

    void startGame(GameMode gameMode);

public:
    static QWindowManager *getInstance();
    ~QWindowManager();

private slots:
    void select(MenuSelection::Selection selection);
};

#endif // QWINDOWMANAGER_H
