#include "cards.h"

#include <algorithm>
#include <iostream>
#include <random>

Cards::Cards(uint8_t trump, uint64_t seed)
        : trump(trump)
        , seed(seed) {
    for (uint8_t i = 0; i < 9; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            Card temp(i, j, (j == trump));
            pack.push_back(temp);
        }
    }

    // randomize();

    std::default_random_engine engine(seed);
    std::shuffle(pack.begin(), pack.end(), engine);
}

Card& Cards::operator[](uint8_t index) {
    return pack[index];
}

// inline void Cards::randomize() {
// }
