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

    data = calloc(0, sizeof(*data));
    data->key = 'A';
    graph_ins_vert(graph, data);

    data = calloc(1, sizeof(*data));
    data->key = 'B';
    graph_ins_vert(graph, data);

    data = calloc(1, sizeof(*data));
    data->key = 'C';
    graph_ins_vert(graph, data);

    data = calloc(1, sizeof(*data));
    data->key = 'D';
    graph_ins_vert(graph, data);

    /* data = calloc(1, sizeof(*data)); */
    /* data->key = 'E'; */
    /* graph_ins_vert(graph, data); */

    /* data = calloc(1, sizeof(*data)); */
    /* data->key = 'F'; */
    /* graph_ins_vert(graph, data); */

    /**********************************************/

    data_a->key = 'A';
    data_b->key = 'B';
    graph_ins_edge(graph, data_a, data_b, 20, GRAPH_EDGE_NDUAL);

    data_a->key = 'B';
    data_b->key = 'C';
    graph_ins_edge(graph, data_a, data_b, 10, GRAPH_EDGE_NDUAL);

    data_a->key = 'C';
    data_b->key = 'D';
    graph_ins_edge(graph, data_a, data_b, 15, GRAPH_EDGE_NDUAL);

    data_a->key = 'D';
    data_b->key = 'A';
    graph_ins_edge(graph, data_a, data_b, 5, GRAPH_EDGE_NDUAL);

    /* data_a->key = 'C'; */
    /* data_b->key = 'F'; */
    /* graph_ins_edge(graph, data_a, data_b, 2, GRAPH_EDGE_NDUAL); */

    /* data_a->key = 'B'; */
    /* data_b->key = 'F'; */
    /* graph_ins_edge(graph, data_a, data_b, 6, GRAPH_EDGE_NDUAL); */

    /* data_a->key = 'D'; */
    /* data_b->key = 'F'; */
    /* graph_ins_edge(graph, data_a, data_b, 2, GRAPH_EDGE_NDUAL); */

    /* data_a->key = 'E'; */
    /* data_b->key = 'F'; */
    /* graph_ins_edge(graph, data_a, data_b, 1, GRAPH_EDGE_NDUAL); */

    data_a->key = 'A';
    graph_bfs(graph, data_a);
    graph_mst_prism(graph, data_a);
    graph_dijkstra(graph, data_a);

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
    printf("Removed: %c [destroy]\n", tmp->key);
    memset(tmp, 0x00, sizeof(*tmp));
    free(tmp);
    *data = NULL;
}

void main_print(const void * const data) {
    data_t * tmp = (data_t *) data;
    printf("%c ", tmp->key);
}
