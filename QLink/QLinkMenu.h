#ifndef QLINKMENU_H
#define QLINKMENU_H

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include "MenuSelection.h"

namespace Ui {
class QLinkMenu;
}

class QLinkMenu : public QWidget
{
    Q_OBJECT

public:
    explicit QLinkMenu(QWidget *parent = nullptr);
    ~QLinkMenu();

private:
    Ui::QLinkMenu *ui;

    QPushButton *onePlayerBtn;

    QPushButton *twoPlayerBtn;

    QPushButton *loadArchiveBtn;

    QPushButton *quitBtn;

signals:
    void selected(MenuSelection::Selection selection);
};

#endif // QLINKMENU_H
