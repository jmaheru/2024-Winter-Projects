#include "pq.h"

#include "node.h"

#include <stdio.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};

struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    //Allocate a PriorityQueue object and return a pointer to it. If there’s an error, return NULL.
    PriorityQueue *pq = calloc(1, sizeof(PriorityQueue));

    if (pq == NULL) {
        exit(1);
    }

    return pq;
}

void pq_free(PriorityQueue **q) {
    //Call free() on *q, and then set *q = NULL.
    if (*q != NULL) {
        free(*q);
        *q = NULL;
    }
}

bool pq_is_empty(PriorityQueue *q) {
    //We indicate an empty queue by storing NULL in the queue’s list field. Return true if that’s the case.
    if (q->list == NULL) {
        return true;
    } else {
        return false;
    }
}

bool pq_size_is_1(PriorityQueue *q) {
    //If the Priority Queue contains a single element, then return true. Otherwise return false
    if (q->list == NULL) {
        return false;
    } else if (q->list->next == NULL) {
        return true;
    } else {
        return false;
    }
}

bool pq_less_than(ListElement *e1, ListElement *e2) {
    if (e1->tree->weight < e2->tree->weight) {
        return true;
    } else if (e1->tree->weight == e2->tree->weight) {

        if (e1->tree->symbol < e2->tree->symbol) {
            return true;
        } else {
            return false;
        }

    } else {
        return false;
    }
}

void enqueue(PriorityQueue *q, Node *tree) {
    //Insert a tree into the priority queue. Keep the tree with the lowest weight at the head (that is, next	to bedequeued). There are three possibilities to consider:
    //• The queue currently is empty.
    //• The new element will become the new first element of the queue.
    //• The new element will be placed after an existing element.
    ListElement *element = calloc(1, sizeof(ListElement));
    element->tree = tree;

    if (pq_is_empty(q) == true) {
        q->list = element;
    } else if (pq_less_than(element, q->list) == true) {
        element->next = q->list;
        q->list = element;
    } else {
        ListElement *t = q->list;

        while (t->next != NULL && !pq_less_than(element, t->next)) {
            t = t->next;
        }

        element->next = t->next;
        t->next = element;
    }
}

Node *dequeue(PriorityQueue *q) {
    //Remove the queue element with the lowest weight and return it. If the queue is empty, then report a fatal error.
    //CHECKING FOR ERROR FIRST
    if (pq_is_empty(q) == true) {
        exit(1);
    } else {
        ListElement *remove = q->list;
        Node *r_node = remove->tree;
        q->list = q->list->next;
        free(remove);
        return r_node;
    }
}

void pq_print(PriorityQueue *q) {
    //DOC
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;

    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree);
        e = e->next;
    }

    printf("=============================================\n");
}
