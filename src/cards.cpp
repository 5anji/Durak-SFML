#include "cards.h"

#include <algorithm>
#include <iostream>
#include <random>

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
    auto engine = [] (int limit) {
        std::random_device generator;
        std::uniform_int_distribution distribution(0, limit);

        return distribution(generator);
    };
    std::random_shuffle(pack.begin(), pack.end(), engine);
}