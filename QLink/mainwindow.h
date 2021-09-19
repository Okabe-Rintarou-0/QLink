#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QPaintEvent>
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
    static const QColor DEFAULT_LINE_COLOR;
    QVector<QPoint> pointsToLink;
    bool needPaint = false;
    Ui::MainWindow *ui;
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QCharacterWidget *characterWidget;
    QSquarePanelWidget *squarePanel;
    void drawLink(QPoint p1, QPoint p2, QPainter &painter, QColor linkColor, int width);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void draw(QVector<QPoint> points);
};
#endif // MAINWINDOW_H
