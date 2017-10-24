#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "graph.h"

int32_t main() {
    graph_t * graph = graph_init(compare, destroy, print);
    data_t * data = (data_t *) NULL;
    data_t * dataB = (data_t *) NULL;
    dataB = (data_t *) calloc(1, sizeof(data_t));

    data = (data_t *) calloc(1, sizeof(data_t));
    data->key = 1;
    graph_ins_vert(graph, data);

    data = (data_t *) calloc(1, sizeof(data_t));
    data->key = 2;
    graph_ins_vert(graph, data);

    data = (data_t *) calloc(1, sizeof(data_t));
    data->key = 3;
    graph_ins_vert(graph, data);

    data = (data_t *) calloc(1, sizeof(data_t));
    data->key = 4;
    graph_ins_vert(graph, data);

    data = (data_t *) calloc(1, sizeof(data_t));
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

    return EXIT_SUCCESS;
}

int32_t compare(const void * const key1, const void * const key2) {
    data_t * a = (data_t *)key1;
    data_t * b = (data_t *)key2;
    if (a->key == b->key)
	return 0;
    if (a->key < b->key)
	return -1;
    if (a->key > b->key)
	return 1;

    return 0;
}

void destroy(void **data) {
    data_t *tmp = (data_t *) *data;
    printf("Removed: %d [destroy]\n", tmp->key);
    memset(tmp, 0x00, sizeof(data_t));
    free(tmp);
    *data = (void *) NULL;
}

void print(const void * const data) {
    data_t * tmp = (data_t *) data;
    printf("%d ", tmp->key);
}
