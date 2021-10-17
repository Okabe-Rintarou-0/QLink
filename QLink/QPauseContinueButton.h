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

    /**
     * @brief 初始化并渲染
     */
    void initAndShow();

private slots:
    /**
     * @brief 翻转状态
     */
    void toggle();
};

#endif // QPAUSECONTINUEBUTTON_H
