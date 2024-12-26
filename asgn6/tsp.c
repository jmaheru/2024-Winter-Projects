#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HELPMESSAGE                                                                                  \
    "Usage: tsp [options]\n\n-i infile    Specify the input file path containing the cities and "    \
    "edges\n             of a graph. If not provided, the default input is\n             set as "    \
    "stdin.\n\n-o outfile   Specify the output file path to print to. If not provided,\n         "   \
    "    the default output will be set to stdout.\n\n-d           Treats all graphs as "            \
    "directed. Remember that the default is to assume an undirected graph, which\n             "     \
    "means that any edge (i, j) that is specified should be added as both (i, j) and (j, i). So "    \
    "if -d is\n             specified, then (i, j) will be added, but (j, i) won’t. \n\n-h       " \
    "    Prints out a help message.\n"

Path *dfs(uint32_t v, Graph *g, Path *p, Path *c) {
    graph_visit_vertex(g, v);
    path_add(p, v, g);

    for (uint32_t j = 0; graph_vertices(g) > j; j++) {
        if (graph_get_weight(g, v, j)) {
            if (!graph_visited(g, j)) {
                dfs(j, g, p, c);
            }

            if (path_vertices(p) == graph_vertices(g)
                && graph_get_vertex_name(g, 0) == graph_get_vertex_name(g, j)) {
                path_add(p, j, g);

                if (path_distance(p) < path_distance(c) || path_distance(c) == 0) {
                    path_copy(c, p);
                }

                path_remove(p, g);
            }
        }
    }

    graph_unvisit_vertex(g, path_remove(p, g));
    return c;
}

int main(int argc, char **argv) {
    FILE *input_file = stdin;
    FILE *output_file = stdout;

    char options[] = "i:o:dh";
    int user_input;
    bool d = false;

    while (-1 != (user_input = getopt(argc, argv, options))) {
        switch (user_input) {
        case 'i':
            if (NULL == (input_file = fopen(optarg, "r"))) {
                exit(1);
            } else {
                break;
            }

        case 'o':
            if (NULL == (output_file = fopen(optarg, "w"))) {
                return 1;
            }
            break;

        case 'd': d = true; break;

        case 'h': fprintf(stdout, HELPMESSAGE); return 31;
        }
    }

    uint32_t num_ofvert;
    if (1 != fscanf(input_file, "%u\n", &num_ofvert)) {
        return 909;
    };

    char city[100];
    Graph *g = graph_create(num_ofvert, d);
    uint32_t paths, st, end, weight;

    for (uint32_t j = 0; num_ofvert > j; j++) {
        if (NULL == fgets(city, 80, input_file)) {
            return 20;
        };
        city[strcspn(city, "\n")] = '\0';
        graph_add_vertex(g, city, j);
    }

    if (1 != fscanf(input_file, "%u\n", &paths)) {
        return 60;
    };

    for (uint32_t loopval = 0; paths > loopval; loopval++) {
        if (3 != fscanf(input_file, "%u %u %u\n", &st, &end, &weight)) {
            return 3213;
        };
        graph_add_edge(g, st, end, weight);
    }

    Path *p = path_create(num_ofvert + 1), *c = path_create(num_ofvert + 1);

    //print

    Path *final = dfs(0, g, p, c);
    path_print(final, output_file, g);

    //close
    fclose(output_file);
    fclose(input_file);

    //free mem so no leaks
    path_free(&c);
    path_free(&p);
    graph_free(&g);

    return 0;
}
