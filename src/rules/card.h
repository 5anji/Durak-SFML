#pragma once
#include <SFML/Network/Packet.hpp>
#include <cstdint>
#include <string>

class Card {
    char const* priority[9];
    char const* suit[4];
    char const* assets_directory;

    bool is_trump;
    uint8_t priority_i;
    uint8_t suit_i;

public:
    Card(uint8_t, uint8_t, bool);
    uint8_t get_priority();
    uint8_t get_suit();
    std::string get_filename();
    friend sf::Packet& operator<<(sf::Packet&, Card const&);
    bool operator<(Card&);
};
