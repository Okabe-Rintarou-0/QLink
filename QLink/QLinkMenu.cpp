#include "QLinkMenu.h"
#include "ui_qlinkmenu.h"

QLinkMenu::QLinkMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QLinkMenu)
{
    ui->setupUi(this);
}

QLinkMenu::~QLinkMenu()
{
    delete ui;
}
