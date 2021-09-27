#include "ShuffleJewel.h"

ShuffleJewel::ShuffleJewel() : QLinkGameItem(FileConstants::JEWEL_URL + "ShuffleJewel.png") {
    jewelType = JewelType::SHUFFLE;
}

void ShuffleJewel::takeEffect(int picker) {
    QLinkGameItem::takeEffect(picker);
    QSquarePanelWidget::getInstance()->shuffle();
}
