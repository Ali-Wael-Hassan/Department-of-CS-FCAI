#include "duck_file.h"

void duckcat(FILE *left, FILE *right, FILE *out) {
    int c;

    while ((c = fgetc(left)) != EOF)
        fputc(c, out);

    while ((c = fgetc(right)) != EOF)
        fputc(c, out);
}

void duckcopy(FILE *dst, FILE *src) {
    int c;

    while ((c = fgetc(src)) != EOF)
        fputc(c, dst);
}

void duckhead(FILE *src, FILE *out) {
    int c, lines = 0;

    while (lines < 10 && (c = fgetc(src)) != EOF) {
        fputc(c, out);

        if (c == '\n')
            ++lines;
    }
}

void ducktail(FILE *src, FILE *out) {
    long end;
    long pos;
    long start;
    int c;
    int lines = 0;
    int required_newlines;
    int ends_with_newline;

    if (fseek(src, 0, SEEK_END) != 0)
        return;

    end = ftell(src);
    if (end < 0)
        return;

    pos = end;
    ends_with_newline = 0;
    if (pos > 0) {
        if (fseek(src, pos - 1, SEEK_SET) != 0)
            return;

        ends_with_newline = fgetc(src) == '\n';
    }

    required_newlines = ends_with_newline ? 11 : 10;

    while (pos > 0 && lines < required_newlines) {
        --pos;

        if (fseek(src, pos, SEEK_SET) != 0)
            return;

        c = fgetc(src);

        if (c == '\n')
            ++lines;
    }

    if (lines < required_newlines)
        start = 0;
    else
        start = pos + 1;

    if (fseek(src, start, SEEK_SET) != 0)
        return;

    while ((c = fgetc(src)) != EOF)
        fputc(c, out);
}