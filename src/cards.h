#pragma once
#include "card.h"

#include <vector>

class Cards {
    std::vector<Card> pack;
    uint8_t trump;

public:
    Cards(uint8_t);
    inline void randomize();
};
