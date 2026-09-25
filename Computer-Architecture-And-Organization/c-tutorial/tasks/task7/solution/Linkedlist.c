#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Linkedlist.h"

LinkedList *linkedlist_create(size_t element_size) {
    LinkedList *root = malloc(sizeof(*root));

    if (root == NULL)
        return NULL;

    root->head = NULL;
    root->size = 0;
    root->element_size = element_size;

    return root;
}

void node_free(Node *node) {
    if (node->data != NULL)
        free(node->data);

    free(node);
}

void linkedlist_free(LinkedList *list) {
    if (list == NULL)
        return;

    linkedlist_clear(list);
    free(list);
}

int linkedlist_push_front(LinkedList *list, const void *data) {
    Node *node;

    if (list == NULL || data == NULL)
        return 0;

    node = malloc(sizeof(*node));

    if (node == NULL)
        return 0;

    node->data = malloc(list->element_size);

    if (node->data == NULL) {
        free(node);
        return 0;
    }

    memcpy(node->data, data, list->element_size);

    node->next = list->head;
    list->head = node;
    list->size++;

    return 1;
}

int linkedlist_push_back(LinkedList *list, const void *data) {
    Node *node = list->head;
    Node *new_node;
    size_t i;

    if (list == NULL || data == NULL)
        return 0;

    new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
        return 0;

    new_node->data = malloc(list->element_size);

    if (new_node->data == NULL) {
        free(new_node);
        return 0;
    }

    memcpy(new_node->data, data, list->element_size);

    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        for (i = 0; i < list->size - 1; ++i)
            node = node->next;

        node->next = new_node;
    }

    list->size++;

    return 1;
}

int linkedlist_pop_front(LinkedList *list, void *out) {
    Node *node;

    if (list == NULL || list->head == NULL || out == NULL)
        return 0;

    node = list->head;

    memcpy(out, node->data, list->element_size);

    list->head = node->next;
    list->size--;

    node_free(node);

    return 1;
}

int linkedlist_pop_back(LinkedList *list, void *out) {
    Node *node;
    size_t i;

    if (list == NULL || list->head == NULL || out == NULL)
        return 0;

    node = list->head;

    if (list->size == 1) {
        memcpy(out, node->data, list->element_size);

        list->head = NULL;
        list->size--;

        node_free(node);

        return 1;
    }

    for (i = 0; i < list->size - 2; ++i)
        node = node->next;

    memcpy(out, node->next->data, list->element_size);

    node_free(node->next);
    node->next = NULL;

    list->size--;

    return 1;
}

int linkedlist_get(const LinkedList *list, size_t index, void *out) {
    Node *node;
    size_t i;

    if (list == NULL || out == NULL || index >= list->size)
        return 0;

    node = list->head;

    for (i = 0; i < index; ++i)
        node = node->next;

    memcpy(out, node->data, list->element_size);

    return 1;
}

int linkedlist_set(LinkedList *list, size_t index, const void *data) {
    Node *node;
    size_t i;

    if (list == NULL || data == NULL || index >= list->size)
        return 0;

    node = list->head;

    for (i = 0; i < index; ++i)
        node = node->next;

    memcpy(node->data, data, list->element_size);

    return 1;
}

size_t linkedlist_size(const LinkedList *list) {
    if (list == NULL)
        return 0;

    return list->size;
}

int linkedlist_empty(const LinkedList *list) {
    if (list == NULL)
        return 0;

    return list->size == 0;
}

void linkedlist_clear(LinkedList *list) {
    Node *node;
    Node *next;

    if (list == NULL)
        return;

    node = list->head;

    while (node != NULL) {
        next = node->next;
        node_free(node);
        node = next;
    }

    list->head = NULL;
    list->size = 0;
}