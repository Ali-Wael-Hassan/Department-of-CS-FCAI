#ifndef DUCK_STRING_H
#define DUCK_STRING_H

#include <stddef.h>

size_t duck_strlen(const char *str);
char *duck_strcpy(char *dest, const char *src);
char *duck_strncpy(char *dest, const char *src, size_t n);
int duck_strcmp(const char *left, const char *right);
int duck_strncmp(const char *left, const char *right, size_t n);
char *duck_strchr(const char *str, int c);
char *duck_strstr(const char *haystack, const char *needle);
void *duck_memcpy(void *dest, const void *src, size_t n);
void *duck_memmove(void *dest, const void *src, size_t n);
void *duck_memset(void *dest, int c, size_t n);

#endif