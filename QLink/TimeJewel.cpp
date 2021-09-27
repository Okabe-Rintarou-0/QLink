#include "TimeJewel.h"

TimeJewel::TimeJewel() : QLinkGameItem(FileConstants::JEWEL_URL + "TimeJewel.png") {
    jewelType = JewelType::TIME;
}

void TimeJewel::takeEffect(int picker) {
    QLinkGameItem::takeEffect(picker);
    QLinkGameController::getInstance()->addTime(30);
}
