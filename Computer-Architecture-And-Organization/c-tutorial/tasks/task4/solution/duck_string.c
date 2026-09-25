#include "duck_string.h"

static int dest_after_src(const unsigned char *dest, const unsigned char *src, size_t n) {
    size_t i;

    for (i = 0; i < n; ++i) {
        if (dest == src + i) {
            return 1;
        }
    }

    return 0;
}

size_t duck_strlen(const char *str) {
    size_t length;

    length = 0;
    while (str[length] != '\0') {
        ++length;
    }

    return length;
}

char *duck_strcpy(char *dest, const char *src) {
    size_t i;

    i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';

    return dest;
}

char *duck_strncpy(char *dest, const char *src, size_t n) {
    size_t i;

    i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }

    while (i < n) {
        dest[i] = '\0';
        ++i;
    }

    return dest;
}

int duck_strcmp(const char *left, const char *right) {
    size_t i;
    unsigned char left_byte;
    unsigned char right_byte;

    i = 0;
    for (;;) {
        left_byte = (unsigned char) left[i];
        right_byte = (unsigned char) right[i];
        if (left_byte != right_byte) {
            return (int) left_byte - (int) right_byte;
        }
        if (left_byte == 0) {
            return 0;
        }
        ++i;
    }
}

int duck_strncmp(const char *left, const char *right, size_t n) {
    size_t i;
    unsigned char left_byte;
    unsigned char right_byte;

    for (i = 0; i < n; ++i) {
        left_byte = (unsigned char) left[i];
        right_byte = (unsigned char) right[i];
        if (left_byte != right_byte) {
            return (int) left_byte - (int) right_byte;
        }
        if (left_byte == 0) {
            return 0;
        }
    }

    return 0;
}

char *duck_strchr(const char *str, int c) {
    char *current;
    unsigned char target;

    current = (char *) str;
    target = (unsigned char) c;
    while (*current != '\0') {
        if ((unsigned char) *current == target) {
            return current;
        }
        ++current;
    }

    if (target == 0) {
        return current;
    }

    return NULL;
}

char *duck_strstr(const char *haystack, const char *needle) {
    size_t start;
    size_t offset;

    if (needle[0] == '\0') {
        return (char *) haystack;
    }

    for (start = 0; haystack[start] != '\0'; ++start) {
        offset = 0;
        while (needle[offset] != '\0' &&
               haystack[start + offset] != '\0' &&
               haystack[start + offset] == needle[offset]) {
            ++offset;
        }
        if (needle[offset] == '\0') {
            return (char *) &haystack[start];
        }
    }

    return NULL;
}

void *duck_memcpy(void *dest, const void *src, size_t n) {
    unsigned char *destination;
    const unsigned char *source;
    size_t i;

    destination = (unsigned char *) dest;
    source = (const unsigned char *) src;

    for (i = 0; i < n; ++i) {
        destination[i] = source[i];
    }

    return dest;
}

void *duck_memmove(void *dest, const void *src, size_t n) {
    unsigned char *destination;
    const unsigned char *source;
    size_t i;

    destination = (unsigned char *) dest;
    source = (const unsigned char *) src;

    if (dest_after_src(destination, source, n)) {
        for (i = n; i > 0; --i) {
            destination[i - 1] = source[i - 1];
        }
    } else {
        for (i = 0; i < n; ++i) {
            destination[i] = source[i];
        }
    }

    return dest;
}

void *duck_memset(void *dest, int c, size_t n) {
    unsigned char *destination;
    unsigned char value;
    size_t i;

    destination = (unsigned char *) dest;
    value = (unsigned char) c;

    for (i = 0; i < n; ++i) {
        destination[i] = value;
    }

    return dest;
}