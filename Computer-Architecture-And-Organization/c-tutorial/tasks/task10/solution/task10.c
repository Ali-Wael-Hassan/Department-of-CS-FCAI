#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "duck_file.h"

static int fail(const char *name);
static int check_output(FILE *stream, const char *expected, const char *name);
static int write_lines(FILE *stream, int count);
static void make_expected(char *buffer, int first, int count);
static int test_cat(void);
static int test_copy_binary(void);
static int test_head(void);
static int test_tail(void);
static int test_eof_and_open_errors(void);

static int fail(const char *name)
{
    fprintf(stderr, "FAIL: %s\n", name);
    return 1;
}

static int check_output(FILE *stream, const char *expected, const char *name)
{
    unsigned char buffer[512];
    size_t length;

    rewind(stream);
    length = fread(buffer, 1, sizeof(buffer), stream);
    if (ferror(stream) || length != strlen(expected) ||
        memcmp(buffer, expected, length) != 0) {
        return fail(name);
    }

    return 0;
}

static int write_lines(FILE *stream, int count)
{
    int i;

    for (i = 0; i < count; ++i) {
        if (fprintf(stream, "line%02d\n", i) < 0) {
            return 0;
        }
    }

    return 1;
}

static void make_expected(char *buffer, int first, int count)
{
    int i;
    size_t used;

    buffer[0] = '\0';
    used = 0;
    for (i = 0; i < count; ++i) {
        sprintf(buffer + used, "line%02d\n", first + i);
        used += strlen(buffer + used);
    }
}

static int test_cat(void)
{
    FILE *left;
    FILE *right;
    FILE *out;
    int failures;

    left = tmpfile();
    right = tmpfile();
    out = tmpfile();
    if (left == NULL || right == NULL || out == NULL) {
        if (left != NULL) {
            fclose(left);
        }
        if (right != NULL) {
            fclose(right);
        }
        if (out != NULL) {
            fclose(out);
        }
        return fail("cat temporary files");
    }
    failures = 0;
    if (fputs("left", left) == EOF || fputs("right", right) == EOF) {
        failures += fail("cat input write");
    }
    rewind(left);
    rewind(right);
    duckcat(left, right, out);
    failures += check_output(out, "leftright", "cat contents");
    if (ferror(left) || ferror(right) || ferror(out)) {
        failures += fail("cat stream error");
    }
    if (fclose(left) == EOF || fclose(right) == EOF || fclose(out) == EOF) {
        failures += fail("cat close");
    }
    return failures;
}

static int test_copy_binary(void)
{
    FILE *src;
    FILE *dst;
    unsigned char input[32];
    unsigned char output[32];
    size_t length;
    size_t i;
    int failures;

    src = tmpfile();
    dst = tmpfile();
    if (src == NULL || dst == NULL) {
        if (src != NULL) {
            fclose(src);
        }
        if (dst != NULL) {
            fclose(dst);
        }
        return fail("copy temporary files");
    }
    length = 18;
    for (i = 0; i < length; ++i) {
        if (i == 10) {
            input[i] = 27;
        } else if (i == 11) {
            input[i] = 127;
        } else {
            input[i] = (unsigned char) (i + 1);
        }
    }
    if (fwrite(input, 1, length, src) != length) {
        fclose(src);
        fclose(dst);
        return fail("copy binary write");
    }
    rewind(src);
    duckcopy(dst, src);
    rewind(dst);
    if (fread(output, 1, length, dst) != length ||
        memcmp(input, output, length) != 0 || ferror(src) || ferror(dst)) {
        failures = fail("copy binary contents");
    } else {
        failures = 0;
    }
    if (fclose(src) == EOF || fclose(dst) == EOF) {
        failures += fail("copy binary close");
    }
    return failures;
}

static int test_head(void)
{
    FILE *src;
    FILE *out;
    char expected[128];
    int failures;

    src = tmpfile();
    out = tmpfile();
    if (src == NULL || out == NULL) {
        if (src != NULL) {
            fclose(src);
        }
        if (out != NULL) {
            fclose(out);
        }
        return fail("head temporary files");
    }
    failures = 0;
    if (!write_lines(src, 15)) {
        failures += fail("head input write");
    }
    rewind(src);
    duckhead(src, out);
    make_expected(expected, 0, 10);
    failures += check_output(out, expected, "head first ten lines");

    fclose(src);
    fclose(out);

    src = tmpfile();
    out = tmpfile();
    if (src == NULL || out == NULL) {
        if (src != NULL) {
            fclose(src);
        }
        if (out != NULL) {
            fclose(out);
        }
        return failures + fail("head short temporary files");
    }
    if (!write_lines(src, 3)) {
        failures += fail("head short input write");
    }
    rewind(src);
    duckhead(src, out);
    make_expected(expected, 0, 3);
    failures += check_output(out, expected, "head short file");
    fclose(src);
    fclose(out);
    return failures;
}

static int test_tail(void)
{
    FILE *src;
    FILE *out;
    char expected[128];
    int failures;

    src = tmpfile();
    out = tmpfile();
    if (src == NULL || out == NULL) {
        if (src != NULL) {
            fclose(src);
        }
        if (out != NULL) {
            fclose(out);
        }
        return fail("tail temporary files");
    }
    failures = 0;
    if (!write_lines(src, 15)) {
        failures += fail("tail input write");
    }
    rewind(src);
    ducktail(src, out);
    make_expected(expected, 5, 10);
    failures += check_output(out, expected, "tail last ten lines");

    fclose(src);
    fclose(out);

    src = tmpfile();
    out = tmpfile();
    if (src == NULL || out == NULL) {
        if (src != NULL) {
            fclose(src);
        }
        if (out != NULL) {
            fclose(out);
        }
        return failures + fail("tail short temporary files");
    }
    if (!write_lines(src, 3)) {
        failures += fail("tail short input write");
    }
    rewind(src);
    ducktail(src, out);
    make_expected(expected, 0, 3);
    failures += check_output(out, expected, "tail short file");
    fclose(src);
    fclose(out);

    src = tmpfile();
    out = tmpfile();
    if (src == NULL || out == NULL) {
        if (src != NULL) {
            fclose(src);
        }
        if (out != NULL) {
            fclose(out);
        }
        return failures + fail("tail unterminated temporary files");
    }
    if (fputs("line00\nline01\nline02", src) == EOF) {
        failures += fail("tail unterminated input write");
    }
    rewind(src);
    ducktail(src, out);
    failures += check_output(out, "line00\nline01\nline02",
                             "tail unterminated file");
    fclose(src);
    fclose(out);
    return failures;
}

static int test_eof_and_open_errors(void)
{
    FILE *src;
    FILE *out;
    FILE *missing;
    long position;
    int failures;

    failures = 0;
    missing = fopen("__duck_task10_missing_input__", "rb");
    if (missing != NULL) {
        fclose(missing);
        failures += fail("missing file opens");
    }

    src = tmpfile();
    out = tmpfile();
    if (src == NULL || out == NULL) {
        if (src != NULL) {
            fclose(src);
        }
        if (out != NULL) {
            fclose(out);
        }
        return failures + fail("EOF temporary files");
    }
    duckcopy(out, src);
    rewind(out);
    if (fgetc(out) != EOF || ferror(out) != 0 || !feof(out)) {
        failures += fail("empty file EOF");
    }
    if (fseek(src, 0, SEEK_END) != 0) {
        failures += fail("fseek end");
    }
    position = ftell(src);
    if (position != 0 || fseek(src, position, SEEK_SET) != 0) {
        failures += fail("ftell and seek set");
    }
    duckcopy(out, src);
    if (ferror(src) || ferror(out)) {
        failures += fail("copy at EOF");
    }
    fclose(src);
    fclose(out);
    return failures;
}

int main(void)
{
    int failures;

    failures = 0;
    failures += test_cat();
    failures += test_copy_binary();
    failures += test_head();
    failures += test_tail();
    failures += test_eof_and_open_errors();

    if (failures == 0) {
        printf("file utility: all tests passed\n");
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "file utility: %d test(s) failed\n", failures);
    return EXIT_FAILURE;
}
