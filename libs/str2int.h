#pragma once
#include <cstdint>

// Convert string to int
constexpr uint16_t str2int(const char* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}