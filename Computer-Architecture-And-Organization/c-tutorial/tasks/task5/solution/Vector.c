#include <stdlib.h>

#include "Vector.h"

void vector_init(Vector *v) {
    if (v == NULL) {
        return;
    }

    v->data = NULL;
    v->size = 0;
    v->capacity = 0;

    v->data = malloc(8 * sizeof(*v->data));
    if (v->data != NULL) {
        v->capacity = 8;
    }
}

int vector_push(Vector *v, int value) {
    int *data;
    size_t new_capacity;

    if (v == NULL) {
        return 0;
    }

    if (v->data != NULL && v->size < v->capacity) {
        v->data[v->size] = value;
        ++v->size;
        return 1;
    }

    if (v->capacity > ((size_t) -1) / 2) {
        return 0;
    }

    if (v->capacity == 0) {
        new_capacity = 8;
    } else {
        new_capacity = v->capacity * 2;
    }

    if (new_capacity <= v->size || new_capacity > ((size_t) -1) / sizeof(int)) {
        return 0;
    }

    data = realloc(v->data, new_capacity * sizeof(*data));
    if (data == NULL) {
        return 0;
    }

    v->data = data;
    v->capacity = new_capacity;
    v->data[v->size] = value;
    ++v->size;

    return 1;
}

int vector_pop(Vector *v, int *out) {
    if (v == NULL || v->data == NULL || v->size == 0) {
        return 0;
    }

    --v->size;
    if (out != NULL) {
        *out = v->data[v->size];
    }

    return 1;
}

int vector_get(const Vector *v, size_t index, int *out) {
    if (v == NULL || v->data == NULL || out == NULL || index >= v->size) {
        return 0;
    }

    *out = v->data[index];

    return 1;
}

int vector_set(Vector *v, size_t index, int value) {
    if (v == NULL || v->data == NULL || index >= v->size) {
        return 0;
    }

    v->data[index] = value;

    return 1;
}

void vector_clear(Vector *v) {
    if (v == NULL) {
        return;
    }

    v->size = 0;
}

void vector_free(Vector *v) {
    if (v == NULL) {
        return;
    }

    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}