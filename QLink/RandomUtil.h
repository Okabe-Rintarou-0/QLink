#ifndef RANDOMUTIL_H
#define RANDOMUTIL_H

#include <random>

class RandomUtil {
public:
    static int randRange(int min, int max);
    static int randomSeed();
};

#endif // RANDOMUTIL_H
