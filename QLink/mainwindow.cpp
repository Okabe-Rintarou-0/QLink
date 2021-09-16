#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSquarePanelWidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(nullptr));
    setGeometry(0, 0, 1920, 1080);

    QSquarePanelWidget *squarePanel = new QSquarePanelWidget;
    squarePanel->setParent(this);
    squarePanel->setSize(5, 5);
    squarePanel->render();

    QLabel *widthLabel = new QLabel(this);
    widthLabel->setGeometry(900, 940, 20, 20);
    widthLabel->setText("宽");
    widthSpinBox = new QSpinBox(this);
    widthSpinBox->setGeometry(920, 940, 40, 20);
    widthSpinBox->setValue(5);

    QLabel *heightLabel = new QLabel(this);
    heightLabel->setGeometry(970, 940, 20, 20);
    heightLabel->setText("高");
    heightSpinBox = new QSpinBox(this);
    heightSpinBox->setGeometry(990, 940, 40, 20);
    heightSpinBox->setValue(5);

    QPushButton *refreshButton = new QPushButton(this);
    refreshButton->setText("刷新");
    refreshButton->setGeometry(1050, 940, 50, 20);

    QApplication::connect(refreshButton, &QPushButton::clicked, this, [=](){
        int w = widthSpinBox->value();
        int h = heightSpinBox->value();
        squarePanel->resizeAndRender(w, h);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

