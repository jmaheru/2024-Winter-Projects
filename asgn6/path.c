#include "path.h"

#include "graph.h"
#include "stack.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->total_weight = 0;
    p->vertices = stack_create(capacity);

    return p;
}

void path_free(Path **pp) {
    if (*pp == NULL || pp == NULL) {
        return;
    }

    Path *p = *pp;
    stack_free(&(p->vertices));
    free(p);

    *pp = NULL;
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    uint32_t tops;

    if (stack_size(p->vertices) > 0) {
        stack_peek(p->vertices, &tops);
        p->total_weight += graph_get_weight(g, tops, val);
    }

    stack_push(p->vertices, val);
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t a;
    uint32_t b;

    if (stack_size(p->vertices) > 1) {
        stack_pop(p->vertices, &a);
        stack_peek(p->vertices, &b);
        p->total_weight -= graph_get_weight(g, b, a);
    } else {
        p->total_weight = 0;
        stack_pop(p->vertices, &a);
    }

    return a;
}

void path_copy(Path *dst, const Path *src) {
    dst->total_weight = src->total_weight;
    stack_copy(dst->vertices, src->vertices);
}

void path_print(const Path *p, FILE *f, const Graph *g) {
    if (stack_full(p->vertices) == false) {
        fprintf(f, "No path found! Alissa is lost!\n");
        return;
    }

    fprintf(f, "Alissa starts at:\n");

    char city[100];

    uint32_t inputval, limit = path_vertices(p);

    Stack *stacktemp = stack_create(limit);

    for (uint32_t i = 0; i < limit; i++) {
        stack_pop(p->vertices, &inputval);
        strcpy(city, graph_get_vertex_name(g, inputval));
        stack_push(stacktemp, inputval);
    }

    while (stack_size(stacktemp) > 0) {
        stack_pop(stacktemp, &inputval);
        strcpy(city, graph_get_vertex_name(g, inputval));
        fprintf(f, "%s\n", city);
    }

    stack_free(&stacktemp);

    fprintf(f, "Total Distance: %u\n", p->total_weight);
}
