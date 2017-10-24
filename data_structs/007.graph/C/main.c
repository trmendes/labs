#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "graph.h"

int32_t main() {
    graph_t * graph = graph_init(compare, destroy, print);
    data_t * data = NULL;
    data_t * dataB = NULL;
    dataB = calloc(1, sizeof(*data));

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

    data->key = 1;
    dataB->key = 2;
    graph_ins_edge(graph, data, dataB);

    data->key = 1;
    dataB->key = 3;
    graph_ins_edge(graph, data, dataB);

    data->key = 2;
    dataB->key = 5;
    graph_ins_edge(graph, data, dataB);

    data->key = 2;
    dataB->key = 3;
    graph_ins_edge(graph, data, dataB);

    data->key = 4;
    dataB->key = 2;
    graph_ins_edge(graph, data, dataB);

    data->key = 4;
    dataB->key = 1;
    graph_ins_edge(graph, data, dataB);

    data->key = 4;
    dataB->key = 5;
    graph_ins_edge(graph, data, dataB);

    data->key = 5;
    dataB->key = 3;
    graph_ins_edge(graph, data, dataB);

    data->key = 3;
    dataB->key = 3;
    graph_ins_edge(graph, data, dataB);

    /* FIXME: Still have to call free and destroy */
    return EXIT_SUCCESS;
}

int32_t compare(const void * const key1, const void * const key2) {
    data_t * a = (data_t *)key1;
    data_t * b = (data_t *)key2;
    return a->key - b->key;
}

void destroy(void **data) {
    data_t *tmp = (data_t *) *data;
    printf("Removed: %d [destroy]\n", tmp->key);
    memset(tmp, 0x00, sizeof(*tmp));
    free(tmp);
    *data = NULL;
}

void print(const void * const data) {
    data_t * tmp = (data_t *) data;
    printf("%d ", tmp->key);
}
