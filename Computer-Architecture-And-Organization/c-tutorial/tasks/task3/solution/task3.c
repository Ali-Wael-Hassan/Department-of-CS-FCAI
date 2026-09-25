#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_lines(FILE *stream);
size_t count_words(FILE *stream);
size_t count_characters(FILE *stream);

size_t count_lines(FILE *stream) {
    size_t lines;
    int character;

    lines = 0;
    while ((character = fgetc(stream)) != EOF) {
        if (character == '\n') {
            ++lines;
        }
    }

    return lines;
}

size_t count_words(FILE *stream) {
    size_t words;
    int character;
    int in_word;

    words = 0;
    in_word = 0;

    while ((character = fgetc(stream)) != EOF) {
        if (isspace((unsigned char) character)) {
            in_word = 0;
        } else if (in_word == 0) {
            ++words;
            in_word = 1;
        }
    }

    return words;
}

size_t count_characters(FILE *stream) {
    size_t characters;
    int character;

    characters = 0;
    while ((character = fgetc(stream)) != EOF) {
        ++characters;
    }

    return characters;
}

int main(int argc, char *argv[]) {
    FILE *input;
    size_t lines;
    size_t words;
    size_t characters;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = fopen(argv[1], "r");
    if (input == NULL) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    lines = count_lines(input);
    if (ferror(input) != 0) {
        fprintf(stderr, "Error reading \"%s\".\n", argv[1]);
        fclose(input);
        return EXIT_FAILURE;
    }
    rewind(input);

    words = count_words(input);
    if (ferror(input) != 0) {
        fprintf(stderr, "Error reading \"%s\".\n", argv[1]);
        fclose(input);
        return EXIT_FAILURE;
    }
    rewind(input);

    characters = count_characters(input);
    if (ferror(input) != 0) {
        fprintf(stderr, "Error reading \"%s\".\n", argv[1]);
        fclose(input);
        return EXIT_FAILURE;
    }

    if (fclose(input) == EOF) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    printf("Lines:      %lu\n", (unsigned long) lines);
    printf("Words:      %lu\n", (unsigned long) words);
    printf("Characters: %lu\n", (unsigned long) characters);

    return EXIT_SUCCESS;
}