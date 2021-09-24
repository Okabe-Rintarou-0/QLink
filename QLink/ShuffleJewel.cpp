#include "ShuffleJewel.h"

ShuffleJewel::ShuffleJewel(): QLinkGameItem(FileConstants::JEWEL_URL + "ShuffleJewel.png") {
}

void ShuffleJewel::takeEffect(int picker) {
    QLinkGameItem::takeEffect(picker);
    QSquarePanelWidget::getInstance()->shuffle();
}
