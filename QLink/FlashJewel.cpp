#include "FlashJewel.h"

FlashJewel::FlashJewel():QLinkGameItem(FileConstants::JEWEL_URL + "FlashJewel.png") {
}

void FlashJewel::connect(QCharacterWidget *character) {
    QApplication::connect(this, &QLinkGameItem::picked, character, &QCharacterWidget::startDash);
}

void FlashJewel::takeEffect(int picker) {
    emit picked(picker);
}
