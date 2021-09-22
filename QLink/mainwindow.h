#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QMessageBox>
#include <QPaintEvent>
#include "QLinkGameController.h"
#include "QLinkCanvas.h"
#include "QSquarePanelWidget.h"
#include "QCharacterWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
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
    QPushButton *startButton;
    QLabel *heightLabel;
    QLabel *widthLabel;
    QLabel *hintLabel;
    QPushButton *testBtn;
    QLCDNumber *countDownLCD;

    QLinkGameController *gameController;

    void startGame();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void showGameOverTips(const QString &tips);
};
#endif // MAINWINDOW_H
