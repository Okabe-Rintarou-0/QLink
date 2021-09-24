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
#include "Jewels.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef QCharacterWidget::MoveMode MoveMode;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QCharacterWidget **characters;
    QSquarePanelWidget *squarePanel;
    QLabel *scoreLabel;
    QLinkCanvas *linkCanvas;
    QPushButton *startButton;
    QLabel *heightLabel;
    QLabel *widthLabel;
    QLabel *hintLabel;
    QLabel *linkStatusLabel;
    QPushButton *testBtn;
    QLCDNumber *countDownLCD;
    QPauseContinueButton *pauseContinueButton;
    QLinkGameItem *jewel;

    QLinkGameController *gameController;

    void startGame();
protected:
    void keyPressEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);
private slots:
    void showGameOverTips(const QString &tips);

    void renderJewel(QLinkGameItem *jewel, const QPoint &pos);
};
#endif // MAINWINDOW_H
