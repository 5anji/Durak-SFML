#include "card.h"

Card::Card(uint8_t priority, uint8_t suit, bool is_trump)
        : priority{"6", "7", "8", "9", "10", "jack", "queen", "king", "ace"}
        , suit{"hearts", "diamonds", "clubs", "spades"}
        , assets_directory("assets/cards/")
        , is_trump(is_trump)
        , priority_i(priority)
        , suit_i(suit) {}

uint8_t Card::get_priority() {
    return priority_i + 6 + is_trump * 9;
}

uint8_t Card::get_suit() {
    return suit_i;
}

std::string Card::get_filename() {
    std::string str;
    str = assets_directory;
    str += priority[priority_i];
    str += "_of_";
    str += suit[suit_i];
    str += ".png";
    return str;
}

sf::Packet& operator<<(sf::Packet& packet, const Card& card) {
    packet << card.priority;
    packet << card.suit;
    packet << card.assets_directory;
    packet << card.is_trump;
    packet << card.priority_i;
    packet << card.suit_i;

    return packet;
}

bool Card::operator<(Card& copy) {
    return get_priority() < copy.get_priority();
}
