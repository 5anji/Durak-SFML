#pragma once
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
    uint8_t get_priority()const;
    uint8_t get_suit()const;
    std::string get_filename()const;
    bool operator<(Card const&)const;
};
