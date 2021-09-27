#ifndef FLASHJEWEL_H
#define FLASHJEWEL_H

#include "QLinkGameItem.h"

class FlashJewel : public QLinkGameItem {
public:
    FlashJewel();

    void connect(QCharacterWidget *character) override;

    void takeEffect(int picker) override;
};

#endif // FLASHJEWEL_H
