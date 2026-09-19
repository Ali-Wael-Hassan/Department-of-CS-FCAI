#pragma once

#include "lossless/dictionary/LZTuple.h"

#include <cstddef>
#include <cstdint>

namespace lossless {
namespace dict {

    /// @brief compresses @p data into LZ77 tuples (free result with std::free)
    ///
    /// @p search_bits and @p lookahead_bits only cap the maximum distance
    /// (2^bits - 1 bytes); serialization still uses the real field widths.
    /// @param data the input buffer to compress
    /// @param data_size the input buffer size in bytes
    /// @param out_tuple_count receives the number of emitted tuples
    /// @param search_bits bits capping the search window at 2^search_bits - 1 bytes
    /// @param lookahead_bits bits capping each match length at 2^lookahead_bits - 1 bytes
    /// @return a malloc'd array of one LZTuple per emitted token
    LZTuple* lz77_encode(const uint8_t* data, size_t data_size, size_t* out_tuple_count, int search_bits = 12, int lookahead_bits = 8);

    /// @brief replays @p tuples into exactly @p output_size bytes (free result with std::free)
    ///
    /// Overlapping matches (length > distance) decode by reading as they write.
    /// @param tuples the tuple array, as produced by @ref lz77_encode
    /// @param tuple_count number of tuples
    /// @param output_size expected decompressed size in bytes (decoding stops when reached)
    /// @return a malloc'd buffer of exactly @p output_size bytes, or nullptr when @p output_size is 0
    uint8_t* lz77_decode(const LZTuple* tuples, size_t tuple_count, size_t output_size);

    /// @brief writes @p tuples to @p filepath with minimal per-field bit widths
    ///
    /// Header: [distance bits][length bits][original size u32], then bit-packed
    /// tuples. Read back with @ref lz77_load.
    /// @param filepath the output file path
    /// @param tuples the tuples to serialize
    /// @param tuple_count number of tuples
    /// @param original_size the uncompressed byte count stored in the header
    /// @return true on success, false if the file could not be opened
    bool lz77_save(const char* filepath, const LZTuple* tuples, size_t tuple_count, size_t original_size);

    /// @brief reads a file written by @ref lz77_save back into tuples (free with std::free)
    ///
    /// Also returns the original size stored in the header via @p out_original_size.
    /// @param filepath the input file path
    /// @param out_tuple_count receives the number of loaded tuples
    /// @param out_original_size receives the uncompressed byte count from the header
    /// @return a malloc'd array of tuples, or nullptr on error or when empty
    LZTuple* lz77_load(const char* filepath, size_t* out_tuple_count, size_t* out_original_size);

}
}
