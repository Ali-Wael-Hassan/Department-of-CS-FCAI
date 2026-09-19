#include "lossless/dictionary/LZ77.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace {

    /// @brief bits needed to represent @p value (0 for zero), e.g. 16 for 65535
    int minimal_bit_width(uint16_t value) {
        int bits = 0;
        while (value > 0) {
            ++bits;
            value >>= 1;
        }
        return bits;
    }

    /// @brief appends @p bits of @p value into the packed byte stream, MSB first
    void write_bits(uint8_t* packed, size_t* byte_index, int* bit_in_byte, uint32_t value, int bits) {
        for (int b = bits - 1; b >= 0; --b) {
            if (value & (static_cast<uint32_t>(1) << b)) {
                packed[*byte_index] |= static_cast<uint8_t>(0x80u >> *bit_in_byte);
            }
            ++*bit_in_byte;
            if (*bit_in_byte == 8) {
                *bit_in_byte = 0;
                ++*byte_index;
            }
        }
    }

    /// @brief reads a @p bits-wide field back, MSB first
    uint32_t read_bits(const uint8_t* packed, size_t* bit_pos, int bits) {
        uint32_t value = 0;
        for (int b = 0; b < bits; ++b) {
            value = (value << 1) | ((packed[*bit_pos >> 3] >> (7 - (*bit_pos & 7))) & 1u);
            ++*bit_pos;
        }
        return value;
    }

    /// @brief longest match of @p candidate against the lookahead at @p pos
    ///
    /// Once a match passes its own distance it wraps onto the run being copied,
    /// so a short repetitive tile like "ab" encodes "abababa" as one tuple.
    size_t lz77_match_length(const uint8_t* data, size_t pos, size_t candidate, size_t point_size, size_t max_len) {
        const size_t distance = pos - candidate;
        const size_t limit = point_size - pos < max_len ? point_size - pos : max_len;
        size_t len = 0;

        while (len < limit) {
            const size_t src = len >= distance ? candidate + (len % distance) : candidate + len;
            if (data[src] != data[pos + len]) break;
            ++len;
        }

        return len;
    }
}

namespace lossless {
namespace dict {

    LZTuple* lz77_encode(const uint8_t* data, size_t data_size, size_t* out_tuple_count, int search_bits, int lookahead_bits) {
        const size_t max_distance = search_bits >= 16 ? 0xFFFFu : (search_bits > 0 ? static_cast<size_t>(1) << search_bits : 1u) - 1;
        const size_t max_length = lookahead_bits >= 16 ? 0xFFFFu : (lookahead_bits > 0 ? static_cast<size_t>(1) << lookahead_bits : 1u) - 1;

        LZTuple* tuples = static_cast<LZTuple*>(std::malloc(data_size * sizeof(LZTuple))); // worst case senario
        size_t count = 0;
        size_t pos = 0;

        while (pos < data_size) {
            size_t best_len = 0;
            size_t best_dist = 0;
            size_t window_start = (pos > max_distance) ? pos - max_distance : 0;

            for (size_t i = window_start; i < pos; ++i) {
                size_t len = lz77_match_length(data, pos, i, data_size, max_length);
                if (len > best_len) {
                    best_len = len;
                    best_dist = pos - i;
                    if (best_len == max_length || pos + best_len == data_size) break;
                }
            }

            tuples[count].distance = static_cast<uint16_t>(best_dist);
            tuples[count].length = static_cast<uint16_t>(best_len);
            tuples[count].next = (pos + best_len < data_size) ? data[pos + best_len] : 0;
            ++count;

            pos += best_len + 1;
        }

        *out_tuple_count = count;
        return tuples;
    }

    uint8_t* lz77_decode(const LZTuple* tuples, size_t tuple_count, size_t output_size) {
        if (output_size == 0) return nullptr;

        uint8_t* out = static_cast<uint8_t*>(std::malloc(output_size));
        size_t pos = 0;

        for (size_t i = 0; i < tuple_count && pos < output_size; ++i) {
            const LZTuple& tuple = tuples[i];

            if (tuple.length > 0 && tuple.distance > 0) {
                size_t start = pos - tuple.distance;
                for (size_t j = 0; j < tuple.length && pos < output_size; ++j) {
                    out[pos++] = out[start + j];
                }
            }

            if (pos < output_size) {
                out[pos++] = tuple.next;
            }
        }

        return out;
    }

    bool lz77_save(const char* filepath, const LZTuple* tuples, size_t tuple_count, size_t original_size) {
        uint16_t max_distance = 0;
        uint16_t max_length = 0;
        for (size_t i = 0; i < tuple_count; ++i) {
            if (tuples[i].distance > max_distance) max_distance = tuples[i].distance;
            if (tuples[i].length > max_length) max_length = tuples[i].length;
        }

        const int distance_bits = minimal_bit_width(max_distance);
        const int length_bits = minimal_bit_width(max_length);
        const size_t tuple_bits = static_cast<size_t>(distance_bits + length_bits + 8);

        std::FILE* file = std::fopen(filepath, "wb");
        if (!file) return false;

        std::fputc(distance_bits, file);
        std::fputc(length_bits, file);
        for (int b = 0; b < 4; ++b) {
            std::fputc((original_size >> (b * 8)) & 0xFF, file);
        }

        const size_t packed_bytes = (tuple_count * tuple_bits + 7) / 8;
        uint8_t* packed = static_cast<uint8_t*>(std::malloc(packed_bytes));
        if (packed_bytes > 0 && !packed) {
            std::fclose(file);
            return false;
        }
        std::memset(packed, 0, packed_bytes);

        size_t byte_index = 0;
        int bit_in_byte = 0;
        for (size_t i = 0; i < tuple_count; ++i) {
            write_bits(packed, &byte_index, &bit_in_byte, tuples[i].distance, distance_bits);
            write_bits(packed, &byte_index, &bit_in_byte, tuples[i].length, length_bits);
            write_bits(packed, &byte_index, &bit_in_byte, tuples[i].next, 8);
        }

        std::fwrite(packed, 1, packed_bytes, file);
        std::fclose(file);
        std::free(packed);
        return true;
    }

    LZTuple* lz77_load(const char* filepath, size_t* out_tuple_count, size_t* out_original_size) {
        *out_tuple_count = 0;
        *out_original_size = 0;

        std::FILE* file = std::fopen(filepath, "rb");
        if (!file) return nullptr;

        const int distance_bits = std::fgetc(file);
        const int length_bits = std::fgetc(file);
        if (distance_bits == EOF || length_bits == EOF) {
            std::fclose(file);
            return nullptr;
        }

        size_t original_size = 0;
        for (int b = 0; b < 4; ++b) {
            const int byte = std::fgetc(file);
            if (byte == EOF) {
                std::fclose(file);
                return nullptr;
            }
            original_size |= static_cast<size_t>(byte) << (b * 8);
        }

        std::fseek(file, 0, SEEK_END);
        const long end = std::ftell(file);
        std::fseek(file, 6, SEEK_SET);
        const long remaining = end - 6;
        if (remaining < 0) {
            std::fclose(file);
            return nullptr;
        }

        uint8_t* packed = static_cast<uint8_t*>(std::malloc(remaining));
        if (remaining > 0 && !packed) {
            std::fclose(file);
            return nullptr;
        }
        const size_t read = remaining > 0 ? std::fread(packed, 1, remaining, file) : 0;
        std::fclose(file);

        const size_t tuple_bits = static_cast<size_t>(distance_bits + length_bits + 8);
        const size_t tuple_count = (read * 8) / tuple_bits;

        LZTuple* tuples = static_cast<LZTuple*>(std::malloc(tuple_count * sizeof(LZTuple)));
        if (tuple_count > 0 && !tuples) {
            std::free(packed);
            return nullptr;
        }

        size_t bit_pos = 0;
        for (size_t i = 0; i < tuple_count; ++i) {
            tuples[i].distance = static_cast<uint16_t>(read_bits(packed, &bit_pos, distance_bits));
            tuples[i].length = static_cast<uint16_t>(read_bits(packed, &bit_pos, length_bits));
            tuples[i].next = static_cast<uint8_t>(read_bits(packed, &bit_pos, 8));
        }

        std::free(packed);
        *out_tuple_count = tuple_count;
        *out_original_size = original_size;
        return tuples;
    }

}
}
