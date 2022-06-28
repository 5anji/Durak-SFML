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
    
    // for (size_t i = 0; i < 36; i++) {
    //     std::cout << i + 1 << ") " << pack[i].get_filename() << " \t" << static_cast<int>(pack[i].get_priority()) << std::endl;
    // }
}

inline void Cards::randomize() {
    std::random_shuffle(pack.begin(), pack.end());
}