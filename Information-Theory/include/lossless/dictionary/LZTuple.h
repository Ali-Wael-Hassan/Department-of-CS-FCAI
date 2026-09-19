#pragma once

#include <cinttypes>

namespace lossless {
namespace dict {

    /// @brief one LZ77 token: a back-reference plus a literal byte
    struct LZTuple {
        uint16_t distance; // bytes back to the match start
        uint16_t length;   // bytes copied from that match
        uint8_t next;      // literal byte emitted after the match
    };

}
}