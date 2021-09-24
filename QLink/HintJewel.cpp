#include "HintJewel.h"

HintJewel::HintJewel(): QLinkGameItem(FileConstants::JEWEL_URL + "HintJewel.png") {
}

void HintJewel::takeEffect(int picker) {
    QLinkGameItem::takeEffect(picker);
    QSquarePanelWidget::getInstance()->startHint();
}
