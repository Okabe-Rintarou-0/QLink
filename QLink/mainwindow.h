#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QPaintEvent>
#include "qlinkgamecontroller.h"
#include "qLinkCanvas.h"
#include "qSquarePanelWidget.h"
#include "qCharacterWidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QCharacterWidget *characterWidget;
    QSquarePanelWidget *squarePanel;
    QLabel *scoreLabel;
    QLinkCanvas *linkCanvas;

    QLinkGameController *gameController;
protected:
    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
