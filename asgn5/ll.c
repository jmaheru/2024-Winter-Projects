#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LL *list_create() {
    LL *l = (LL *) malloc(sizeof(LL));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    return l;
}

bool list_add(LL *l, item *i) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return false;
    }
    n->data = *i;
    n->next = NULL;
    if (l->head == NULL) {
        l->head = n;
    } else {
        l->tail->next = n;
    }
    l->tail = n; // Update tail pointer
    return true;
}

item *list_find(LL *l, bool (*cmp)(item *, item *), item *i) {
    Node *n = l->head;
    while (n != NULL) {
        if (cmp(&n->data, i)) {
            return &n->data;
        }
        n = n->next;
    }
    return NULL;
}

void list_destroy(LL **l) {
    if (*l == NULL) {
        return;
    }

    Node *current = (*l)->head;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(*l);
    *l = NULL;
}

void list_remove(LL *h, bool (*cmp)(item *, item *), item *i) {
    if (h == NULL || h->head == NULL)
        return;

    Node *x = h->head;
    Node *b = NULL;

    while (x != NULL) {
        if (cmp(&x->data, i)) {
            if (b == NULL) {
                h->head = x->next;
            } else {
                b->next = x->next;
            }

            if (x == h->tail) {
                h->tail = b;
            }

            free(x);
            return;
        }
        b = x;
        x = x->next;
    }
}
