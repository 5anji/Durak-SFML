#include "card.h"

#include <spdlog/fmt/fmt.h>

Card::Card(uint8_t priority, uint8_t suit, bool is_trump)
        : priority{"6", "7", "8", "9", "10", "jack", "queen", "king", "ace"}
        , suit{"hearts", "diamonds", "clubs", "spades"}
        , assets_directory("assets/cards/")
        , is_trump(is_trump)
        , priority_i(priority)
        , suit_i(suit) {}

uint8_t Card::get_priority() const {
    return priority_i + 6 + is_trump * 9;
}

uint8_t Card::get_suit() const {
    return suit_i;
}

std::string Card::get_filename() const {
    return fmt::format("{}{}_of_{}.png",
                       assets_directory,
                       priority[priority_i],
                       suit[suit_i]);
}

bool Card::operator<(Card const& copy) const {
    return get_priority() < copy.get_priority();
}
