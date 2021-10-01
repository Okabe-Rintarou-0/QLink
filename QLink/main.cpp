#include <QApplication>
#include "QWindowManager.h"
#include "QUnitTest.h"

//#define TEST


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
#ifdef TEST
    QUnitTest unitTest;
    QTest::qExec(&unitTest);
#endif
    QWindowManager *windowManager = QWindowManager::getInstance();
//    GameWindow w;
//    w.show();
    return a.exec();
}
