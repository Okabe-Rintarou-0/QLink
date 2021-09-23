#include "ShuffleJewel.h"

ShuffleJewel::ShuffleJewel(): QLinkGameItem(FileConstants::JEWEL_URL + "ShuffleJewel.png") {
}

void ShuffleJewel::takeEffect(int picker) {
    QSquarePanelWidget::getInstance()->shuffle();
}
