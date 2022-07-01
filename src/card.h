#pragma once
#include <cstdint>
#include <string>

class Card {
    const char* priority[9];
    const char* suit[4];
    const char* assets_directory;

    bool is_trump;
    uint8_t priority_i;
    uint8_t suit_i;

public:
    Card(uint8_t, uint8_t, bool);
    uint8_t get_priority();
    uint8_t get_suit();
    std::string get_filename();
    bool operator<(Card&);
};
