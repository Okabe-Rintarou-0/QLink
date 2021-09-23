#ifndef SHUFFLEJEWEL_H
#define SHUFFLEJEWEL_H
#include "QSquarePanelWidget.h"
#include "QLinkGameItem.h"

class ShuffleJewel: public QLinkGameItem
{
public:
    ShuffleJewel();

    void takeEffect(int picker) override;
};

#endif // SHUFFLEJEWEL_H
