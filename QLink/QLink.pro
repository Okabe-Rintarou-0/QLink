QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FlashJewel.cpp \
    HintJewel.cpp \
    QCharacterManager.cpp \
    QLinkArchive.cpp \
    QPauseContinueButton.cpp \
    ShuffleJewel.cpp \
    TimeJewel.cpp \
    directionutil.cpp \
    imageUtil.cpp \
    main.cpp \
    mainwindow.cpp \
    qCharacterWidget.cpp \
    qLinkCanvas.cpp \
    qLinkGameController.cpp \
    qLinkSquare.cpp \
    qSquareImageManager.cpp \
    qSquarePanelWidget.cpp \
    qStyleSheetBuilder.cpp \
    qlinkgameitem.cpp \
    qlinkmenu.cpp \
    randomUtil.cpp

HEADERS += \
    FlashJewel.h \
    HintJewel.h \
    Jewels.h \
    QCharacterManager.h \
    QLinkArchive.h \
    QPauseContinueButton.h \
    ShuffleJewel.h \
    TimeJewel.h \
    directionutil.h \
    fileConstants.h \
    imageUtil.h \
    mainwindow.h \
    qCharacterWidget.h \
    qLinkCanvas.h \
    qLinkGameController.h \
    qLinkSquare.h \
    qSquareImageManager.h \
    qSquarePanelWidget.h \
    qStyleSheetBuilder.h \
    qlinkgameitem.h \
    qlinkmenu.h \
    randomUtil.h

FORMS += \
    mainwindow.ui \
    qlinkmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
