#ifndef QLINKMENU_H
#define QLINKMENU_H

#include <QWidget>

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
};

#endif // QLINKMENU_H
