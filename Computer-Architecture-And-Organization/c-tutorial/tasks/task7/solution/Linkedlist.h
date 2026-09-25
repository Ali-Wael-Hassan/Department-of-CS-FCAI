#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
    size_t element_size;
} LinkedList;


void node_free(Node *node);

LinkedList *linkedlist_create(size_t element_size);

void linkedlist_free(LinkedList *list);

int linkedlist_push_front(LinkedList *list, const void *data);
int linkedlist_push_back(LinkedList *list, const void *data);
int linkedlist_pop_front(LinkedList *list, void *out);
int linkedlist_pop_back(LinkedList *list, void *out);

int linkedlist_get(const LinkedList *list, size_t index, void *out);
int linkedlist_set(LinkedList *list, size_t index, const void *data);

size_t linkedlist_size(const LinkedList *list);

int linkedlist_empty(const LinkedList *list);
void linkedlist_clear(LinkedList *list);

#endif