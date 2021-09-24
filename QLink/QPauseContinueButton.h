#ifndef QPAUSECONTINUEBUTTON_H
#define QPAUSECONTINUEBUTTON_H
#include <QPushButton>
#include <QApplication>
#include "FileConstants.h"

class QPauseContinueButton: public QPushButton
{
private:
    QIcon continueIcon;

    QIcon pauseIcon;

    bool paused = false;
public:
    QPauseContinueButton();

    void initAndShow();

private slots:
    void toggle();
};

#endif // QPAUSECONTINUEBUTTON_H
