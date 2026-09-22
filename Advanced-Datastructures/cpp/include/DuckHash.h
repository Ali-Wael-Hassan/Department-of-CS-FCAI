#pragma once

#include <cinttypes>
#include <string>

namespace duck {

    template <typename T>
    size_t duck_hash(const T& elem, size_t size) {
        return 0;
    }

    template <>
    size_t duck_hash<std::string>(const std::string& elem, size_t size) {
        constexpr size_t base = 31;
        size_t value = 0;

        for (char c : elem)
            value = (value * base + static_cast<unsigned char>(c)) % size;

        return value;
    }

    template <>
    size_t duck_hash<int>(const int& elem, size_t size) {
        uint32_t x = static_cast<uint32_t>(elem);
        
        x ^= x >> 16;
        x *= 0x85ebca6b;
        x ^= x >> 13;
        x *= 0xc2b2ae35;
        x ^= x >> 16;

        return static_cast<size_t>(x) % size;
    }

}
