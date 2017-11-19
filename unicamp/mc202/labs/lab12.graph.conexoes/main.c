#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "graph.h"

int32_t main() {

    int32_t i, j;
    int32_t a, b, w;
    int32_t ret;
    adj_list_t * short_path = NULL;

    graph_t * graph;
    data_t * data = NULL;
    data_t * data_a = NULL;
    data_t * data_b = NULL;

    data_a = calloc(1, sizeof(*data_a));
    data_b = calloc(1, sizeof(*data_b));

    while (1) {
	ret = scanf("%d", &i);

	if ((ret == EOF) || (i == 0))
	    break;

	graph = graph_init(main_print);
	for (j = 0; j <= i; ++j) {
	    data = calloc(1, sizeof(*data));
	    data->key = j;
	    graph_ins_vert(graph, data);
	}

	for (j = 0; j < i; ++j) {
	    ret = scanf("%d %d %d", &a, &b, &w);

	    if (ret == EOF)
		break;

	    data_a->key = a;
	    data_b->key = b;

	    graph_ins_edge(graph, data_a, data_b, w, GRAPH_EDGE_DUAL);

	}

	data_a->key = 0;
	//graph_mst_prism(graph, data_a);
	graph_dijkstra(graph, data_a, short_path);
	list_destroy(&short_path, NULL);
	//graph_destroy(&graph);
    }

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
    memset(tmp, 0x00, sizeof(*tmp));
    free(tmp);
    *data = NULL;
}

void main_print(const void * const data) {
    data_t * tmp = (data_t *) data;
    printf("%d ", tmp->key);
}
