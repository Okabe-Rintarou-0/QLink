#ifndef HINTJEWEL_H
#define HINTJEWEL_H
#include "QLinkGameItem.h"
#include "QSquarePanelWidget.h"

class HintJewel: public QLinkGameItem
{
public:
    HintJewel();

    void takeEffect(int picker) override;
};

#endif // HINTJEWEL_H
