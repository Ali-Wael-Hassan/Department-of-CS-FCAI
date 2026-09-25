#include <stdlib.h>
#include <string.h>

#include "Vector.h"

void vector_init(Vector *v, size_t element_size) {
    if (v == NULL) {
        return;
    }

    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    v->element_size = element_size;

    if (element_size == 0 || element_size > ((size_t) -1) / 8) {
        return;
    }

    v->data = malloc(8 * element_size);
    if (v->data != NULL) {
        v->capacity = 8;
    }
}

int vector_push(Vector *v, const void *value) {
    void *data;
    size_t new_capacity;
    size_t offset;

    if (v == NULL || value == NULL || v->element_size == 0) {
        return 0;
    }

    if (v->size > ((size_t) -1) / v->element_size) {
        return 0;
    }

    if (v->data != NULL && v->size < v->capacity) {
        offset = v->size * v->element_size;
        memcpy((unsigned char *) v->data + offset, value, v->element_size);
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

    if (new_capacity <= v->size ||
        new_capacity > ((size_t) -1) / v->element_size) {
        return 0;
    }

    data = realloc(v->data, new_capacity * v->element_size);
    if (data == NULL) {
        return 0;
    }

    v->data = data;
    v->capacity = new_capacity;
    offset = v->size * v->element_size;
    memcpy((unsigned char *) v->data + offset, value, v->element_size);
    ++v->size;

    return 1;
}

int vector_pop(Vector *v, void *out) {
    size_t offset;

    if (v == NULL || v->data == NULL || v->element_size == 0 ||
        v->size == 0) {
        return 0;
    }

    --v->size;
    if (out != NULL) {
        offset = v->size * v->element_size;
        memcpy(out, (unsigned char *) v->data + offset, v->element_size);
    }

    return 1;
}

int vector_get(const Vector *v, size_t index, void *out) {
    size_t offset;

    if (v == NULL || v->data == NULL || out == NULL || v->element_size == 0 || index >= v->size) {
        return 0;
    }

    offset = index * v->element_size;
    memcpy(out, (unsigned char *) v->data + offset, v->element_size);

    return 1;
}

int vector_set(Vector *v, size_t index, const void *value) {
    size_t offset;

    if (v == NULL || v->data == NULL || value == NULL || v->element_size == 0 || index >= v->size) {
        return 0;
    }

    offset = index * v->element_size;
    memcpy((unsigned char *) v->data + offset, value, v->element_size);

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