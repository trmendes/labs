#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "graph.h"

int32_t main() {
    graph_t * graph = graph_init(main_print);
    data_t * data = NULL;
    data_t * data_a = NULL;
    data_t * data_b = NULL;

    data_a = calloc(1, sizeof(*data_a));
    data_b = calloc(1, sizeof(*data_b));

    data = calloc(1, sizeof(*data));
    data->key = 1;
    graph_ins_vert(graph, data);

    data = calloc(1, sizeof(*data));
    data->key = 2;
    graph_ins_vert(graph, data);

    data = calloc(1, sizeof(*data));
    data->key = 3;
    graph_ins_vert(graph, data);

    data = calloc(1, sizeof(*data));
    data->key = 4;
    graph_ins_vert(graph, data);

    data = calloc(1, sizeof(*data));
    data->key = 5;
    graph_ins_vert(graph, data);

    /**********************************************/

    data_a->key = 1;
    data_b->key = 2;
    graph_ins_edge(graph, data_a, data_b);

    data_a->key = 1;
    data_b->key = 3;
    graph_ins_edge(graph, data_a, data_b);

    data_a->key = 2;
    data_b->key = 5;
    graph_ins_edge(graph, data_a, data_b);

    data_a->key = 2;
    data_b->key = 3;
    graph_ins_edge(graph, data_a, data_b);

    data_a->key = 4;
    data_b->key = 2;
    graph_ins_edge(graph, data_a, data_b);

    data_a->key = 4;
    data_b->key = 1;
    graph_ins_edge(graph, data_a, data_b);

    data_a->key = 4;
    data_b->key = 5;
    graph_ins_edge(graph, data_a, data_b);

    data_a->key = 5;
    data_b->key = 3;
    graph_ins_edge(graph, data_a, data_b);

    data_a->key = 3;
    data_b->key = 3;
    graph_ins_edge(graph, data_a, data_b);

    data_a->key = 20;
    data_b->key = 3;
    graph_ins_edge(graph, data_a, data_b);

    data_a->key = 1;
    graph_bfs(graph, data_a);

    graph_destroy(&graph);

    memset(data_a, 0x00, sizeof(*data_a));
    free(data_a);
    memset(data_b, 0x00, sizeof(*data_b));
    free(data_b);
    return EXIT_SUCCESS;
}

int32_t main_compare(const void * const key1, const void * const key2) {
    data_t * a = (data_t *)key1;
    data_t * b = (data_t *)key2;
    return a->key - b->key;
}

void main_destroy(void **data) {
    data_t *tmp = (data_t *) *data;
    printf("Removed: %d [destroy]\n", tmp->key);
    memset(tmp, 0x00, sizeof(*tmp));
    free(tmp);
    *data = NULL;
}

void main_print(const void * const data) {
    data_t * tmp = (data_t *) data;
    printf("%d ", tmp->key);
}
