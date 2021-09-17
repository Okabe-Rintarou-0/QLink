#include "randomUtil.h"

int RandomUtil::randRange(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
