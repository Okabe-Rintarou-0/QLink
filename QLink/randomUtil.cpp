#include "RandomUtil.h"
#include "time.h"

int RandomUtil::randRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int RandomUtil::randomSeed(){
    int timestamp = time(nullptr);
    return timestamp - randRange(0, timestamp);
}
