#include "cards.h"

#include <algorithm>
#include <iostream>

Cards::Cards(uint8_t trump)
        : trump(trump) {
    for (uint8_t i = 0; i < 9; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            Card temp(i, j, (j == trump));
            pack.push_back(temp);
        }
    }

    randomize();
}

Card Cards::operator[](uint8_t index) {
    return pack[index];
}

inline void Cards::randomize() {
    std::random_shuffle(pack.begin(), pack.end());
}