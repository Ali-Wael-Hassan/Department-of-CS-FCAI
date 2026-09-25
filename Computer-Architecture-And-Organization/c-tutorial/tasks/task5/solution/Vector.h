#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector *v);
int vector_push(Vector *v, int value);
int vector_pop(Vector *v, int *out);
int vector_get(const Vector *v, size_t index, int *out);
int vector_set(Vector *v, size_t index, int value);
void vector_clear(Vector *v);
void vector_free(Vector *v);

#endif