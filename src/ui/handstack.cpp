#include "handstack.h"

#include <iostream>

handstack::handstack(uint8_t max, sf::Vector2<uint32_t> size)
        : limit_set_by_rules(max)
        , window_size(size) {}

void handstack::operator+=(Card const& source) {
    Button_With_Image temp(&(const_cast<Card&>(source)),
                           window_size,
                           sf::Vector2f{window_size.x / 4, window_size.y - 300});
    cards.push_back(temp);
}

Button_With_Image handstack::operator[](uint8_t index) {
    return cards[index];
}

void handstack::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto&& i : cards) {
        target.draw(i, states);
    }
}
