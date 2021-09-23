#include "TimeJewel.h"

TimeJewel::TimeJewel(): QLinkGameItem(FileConstants::JEWEL_URL + "TimeJewel.png") {
}

void TimeJewel::takeEffect(int picker) {
    QLinkGameController::getInstance()->addTime(30);
}
