#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSquarePanelWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setGeometry(0, 0, 1920, 1080);

    QSquarePanelWidget *squarePanel = new QSquarePanelWidget;
    squarePanel->setParent(this);
    squarePanel->setSize(5, 5);
    squarePanel->render();
}

MainWindow::~MainWindow()
{
    delete ui;
}

