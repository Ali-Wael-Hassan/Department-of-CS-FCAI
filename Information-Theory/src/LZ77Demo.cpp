#include "lossless/dictionary/LZ77.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

using lossless::dict::LZTuple;
using lossless::dict::lz77_encode;
using lossless::dict::lz77_decode;
using lossless::dict::lz77_save;
using lossless::dict::lz77_load;

uint8_t* read_whole_file(const char* path, size_t* size_out) {
    std::FILE* file = std::fopen(path, "rb");
    if (!file) return nullptr;

    std::fseek(file, 0, SEEK_END);
    long end = std::ftell(file);
    if (end < 0) {
        std::fclose(file);
        return nullptr;
    }
    std::fseek(file, 0, SEEK_SET);

    size_t length = static_cast<size_t>(end);
    uint8_t* buffer = static_cast<uint8_t*>(std::malloc(length > 0 ? length : 1));
    if (!buffer) {
        std::fclose(file);
        return nullptr;
    }
    size_t read = length > 0 ? std::fread(buffer, 1, length, file) : 0;
    std::fclose(file);

    *size_out = read;
    return buffer;
}

bool write_whole_file(const char* path, const uint8_t* data, size_t size) {
    std::FILE* file = std::fopen(path, "wb");
    if (!file) return false;
    bool ok = size > 0 ? std::fwrite(data, 1, size, file) == size : true;
    std::fclose(file);
    return ok;
}

long file_size_bytes(const char* path) {
    std::FILE* file = std::fopen(path, "rb");
    if (!file) return -1;
    std::fseek(file, 0, SEEK_END);
    long size = std::ftell(file);
    std::fclose(file);
    return size;
}

void strip_newline(char* line) {
    size_t n = std::strlen(line);
    while (n > 0 && (line[n - 1] == '\n' || line[n - 1] == '\r')) {
        line[--n] = '\0';
    }
}

void prompt_line(const char* prompt, char* buffer, size_t capacity) {
    std::printf("%s", prompt);
    if (std::fgets(buffer, static_cast<int>(capacity), stdin) != nullptr) {
        strip_newline(buffer);
    }
}

int read_int_default(const char* prompt, int dflt) {
    char line[64];
    std::printf("%s", prompt);
    if (std::fgets(line, sizeof(line), stdin) == nullptr) return dflt;
    int value;
    if (std::sscanf(line, "%d", &value) != 1) return dflt;
    return value;
}

void run_compress() {
    char in_path[1024];
    char out_path[1024];

    prompt_line("  input text file  : ", in_path, sizeof(in_path));
    prompt_line("  output file      : ", out_path, sizeof(out_path));
    int search_bits = read_int_default("  search bits (12)  : ", 12);
    int lookahead_bits = read_int_default("  lookahead bits (8): ", 8);

    size_t in_size = 0;
    uint8_t* data = read_whole_file(in_path, &in_size);
    if (!data) {
        std::printf("  failed to read '%s'\n", in_path);
        return;
    }

    size_t tuple_count = 0;
    LZTuple* tuples = lz77_encode(data, in_size, &tuple_count, search_bits, lookahead_bits);

    bool ok = tuples && lz77_save(out_path, tuples, tuple_count, in_size);
    long out_size = ok ? file_size_bytes(out_path) : -1;

    if (ok && out_size >= 0) {
        std::printf("  input   %zu bytes\n", in_size);
        std::printf("  tuples  %zu\n", tuple_count);
        std::printf("  output  %ld bytes (%.2f%% of input)\n", out_size,
                    in_size > 0 ? 100.0 * static_cast<double>(out_size) / static_cast<double>(in_size) : 0.0);
    } else {
        std::printf("  compression failed\n");
    }

    std::free(tuples);
    std::free(data);
}

void run_decompress() {
    char in_path[1024];
    char out_path[1024];

    prompt_line("  input file        : ", in_path, sizeof(in_path));
    prompt_line("  output file       : ", out_path, sizeof(out_path));

    size_t tuple_count = 0;
    size_t original_size = 0;
    LZTuple* tuples = lz77_load(in_path, &tuple_count, &original_size);
    if (!tuples) {
        std::printf("  failed to read '%s'\n", in_path);
        return;
    }

    uint8_t* data = lz77_decode(tuples, tuple_count, original_size);
    bool ok = data && original_size > 0 && write_whole_file(out_path, data, original_size);

    if (ok) {
        std::printf("  tuples %zu -> %zu bytes written to '%s'\n", tuple_count, original_size, out_path);
    } else {
        std::printf("  decompression failed\n");
    }

    std::free(data);
    std::free(tuples);
}

int main() {
    std::printf("=== LZ77 interactive demo ===\n");

    while (true) {
        std::printf("\n1. Compress a text file\n");
        std::printf("2. Decompress a file\n");
        std::printf("0. Exit\n");
        int choice = read_int_default("choice: ", -1);

        if (choice == 1) {
            run_compress();
        } else if (choice == 2) {
            run_decompress();
        } else if (choice == 0) {
            break;
        } else {
            std::printf("unknown choice\n");
        }
    }

    return 0;
}