#ifndef TIMEJEWEL_H
#define TIMEJEWEL_H

#include <QPainter>
#include "QLinkGameItem.h"
#include "QLinkGameController.h"

class TimeJewel : public QLinkGameItem {
public:
    TimeJewel();

    void takeEffect(int picker) override;
};

#endif // TIMEJEWEL_H
