#include "mainwindow.h"

#include <QApplication>
#include "QUnitTest.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    MainWindow w;

    QUnitTest unitTest;
    QTest::qExec(&unitTest);

//    w.show();
    return a.exec();
}
