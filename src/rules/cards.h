#pragma once
#include "card.h"

#include <vector>

struct Cards {
    uint8_t trump;
    uint64_t seed;
    std::vector<Card> pack;
    Cards(uint8_t, uint64_t);
    Card& operator[](uint8_t);

    inline void randomize();
};
