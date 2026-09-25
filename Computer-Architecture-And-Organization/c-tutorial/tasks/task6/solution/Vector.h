#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} Vector;

void vector_init(Vector *v, size_t element_size);
int vector_push(Vector *v, const void *value);
int vector_pop(Vector *v, void *out);
int vector_get(const Vector *v, size_t index, void *out);
int vector_set(Vector *v, size_t index, const void *value);
void vector_clear(Vector *v);
void vector_free(Vector *v);

#endif