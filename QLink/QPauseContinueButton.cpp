#include "QPauseContinueButton.h"

QPauseContinueButton::QPauseContinueButton() {
    continueIcon.addFile(FileConstants::ICON_URL + "continue.png");
    pauseIcon.addFile(FileConstants::ICON_URL + "pause.png");
    QApplication::connect(this, &QPushButton::clicked, this, &QPauseContinueButton::toggle);
}

void QPauseContinueButton::toggle() {
    paused = !paused;
    if (!paused){
        setIcon(pauseIcon);
    }
    else {
        setIcon(continueIcon);
    }
}

void QPauseContinueButton::initAndShow() {
    setIconSize(size());
    setIcon(pauseIcon);
    setFlat(true);
    paused = false;
    show();
}
