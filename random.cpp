#include "random.h"
#include <random>

std::random_device rd;

int getRandom(int lower, int upper)
{
    std::uniform_int_distribution<int> dist(lower, upper);
    return dist(rd);
}











