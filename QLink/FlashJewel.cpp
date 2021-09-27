#include "FlashJewel.h"

FlashJewel::FlashJewel() : QLinkGameItem(FileConstants::JEWEL_URL + "FlashJewel.png") {
    jewelType = JewelType::FLASH;
}

void FlashJewel::connect(QCharacterWidget *character) {
    QLinkGameItem::connect(character);
    QApplication::connect(this, &QLinkGameItem::picked, character, &QCharacterWidget::startDash);
}

void FlashJewel::takeEffect(int picker) {
    QLinkGameItem::takeEffect(picker);
}
