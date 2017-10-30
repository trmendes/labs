#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "main.h"
#include "list.h"
#include "queue.h"
#include "graph.h"

/* Private prototypes */
void    graph_destroy_element(void **);
int32_t graph_compare_element(const void * const data_a, const void * const data_b);
void    graph_print_element(const void * const data);

graph_t * graph_init(print_ft print) {
    graph_t * graph = calloc(1, sizeof(*graph));

    if (graph == NULL) {
	errno = GRAPH_FAIL_MALLOC;
	return NULL;
    }

    graph->vertexs = list_init();

    graph->api.print = print;

    if (graph->vertexs == NULL) {
	memset(graph, 0x00, sizeof(*graph));
	free(graph);
	errno = GRAPH_FAIL_MALLOC;
	return NULL;
    }

    errno = GRAPH_SUCCESS;
    return graph;
}

void graph_destroy(graph_t ** graph) {
    if (*graph == NULL) {
	errno = GRAPH_ARGS_NULL;
	return;
    }

    graph_vertex_t * vertex = NULL;

    while ((vertex = list_lookup_next((*graph)->vertexs, vertex, graph_compare_element)) != NULL) {
	list_destroy(&(vertex->adjacents), NULL);
    }

    list_destroy(&((*graph)->vertexs), graph_destroy_element);

    memset(*graph, 0x00, sizeof(**graph));
    free(*graph);
    *graph = NULL;
}

int8_t graph_ins_vert(graph_t * graph, const void * data) {
    if ((graph == NULL) || (data == NULL))
	return GRAPH_ARGS_NULL;

    int8_t retval;
    graph_vertex_t * new_vertex = calloc(1, sizeof(*new_vertex));
    new_vertex->v = (void *) data;

    /* We do not allow repeated elements */
    if (list_lookup(graph->vertexs, new_vertex, graph_compare_element) != NULL) {
	memset(new_vertex, 0x00, sizeof(*new_vertex));
	free(new_vertex);
	return GRAPH_VERTEX_EXISTS;
    }

    if (new_vertex == NULL)
	return GRAPH_FAIL_MALLOC;

    new_vertex->adjacents = list_init();

    if (new_vertex->adjacents == NULL) {
	memset(new_vertex, 0x00, sizeof(*new_vertex));
	free(new_vertex);
	return GRAPH_FAIL_MALLOC;
    }

    retval = list_ins_next(graph->vertexs, NULL, new_vertex, graph_compare_element);

    if (retval != LST_SUCCESS) {
	list_destroy(&(new_vertex->adjacents), NULL);
	memset(new_vertex, 0x00, sizeof(*new_vertex));
	free(new_vertex);
	return GRAPH_FAIL_MALLOC;
    }

    ++graph->vcounter;

    printf("Add [vert] ");
    graph->api.print(data);
    printf("\n");

    return GRAPH_SUCCESS;
}

int8_t graph_ins_edge(graph_t * graph, const void * data_a, const void * data_b) {
    if ((graph == NULL) || (data_a == NULL) || (data_b == NULL))
	return GRAPH_ARGS_NULL;

    int8_t retval;

    graph_vertex_t * element_tmp = NULL;
    graph_vertex_t * element_a = NULL;
    graph_vertex_t * element_b = NULL;

    element_tmp = calloc(1, sizeof(*element_tmp));
    element_tmp->v = (void *) data_a;

    element_a = list_lookup(graph->vertexs, element_tmp, graph_compare_element) ;

    if (element_a == NULL) {
	memset(element_tmp, 0x00, sizeof(*element_tmp));
	free(element_tmp);
	return GRAPH_VERTEX_NOT_FOUND;
    }

    element_tmp->v = (void *) data_b;

    element_b = list_lookup(graph->vertexs, element_tmp, graph_compare_element);

    memset(element_tmp, 0x00, sizeof(*element_tmp));
    free(element_tmp);

    if (element_b == NULL)
	return GRAPH_VERTEX_NOT_FOUND;

    if (list_lookup(element_a->adjacents, element_b, graph_compare_element) != NULL)
	return GRAPH_ADJ_EXISTS;

    retval = list_ins_next(element_a->adjacents, NULL, element_b, graph_compare_element);

    if (retval != LST_SUCCESS)
	return GRAPH_FAIL_MALLOC;

    ++graph->ecounter;

    printf("Add [edge] ");
    graph->api.print(data_a);
    printf("-> ");
    graph->api.print(data_b);
    printf("\n");

    return GRAPH_SUCCESS;
}

void * graph_lookup_next_vertex(graph_t * graph, void * data) {
    if (graph == NULL) {
	errno = GRAPH_ARGS_NULL;
	return NULL;
    }

    void * ret_data = NULL;
    graph_vertex_t * vertex = NULL;
    graph_vertex_t * ret_vertex = NULL;

    if (data == NULL) {
	ret_vertex = list_lookup_next(graph->vertexs, NULL, graph_compare_element);
    } else {
	vertex = calloc(1, sizeof(*vertex));

	if (vertex == NULL) {
	    errno = GRAPH_FAIL_MALLOC;
	    return NULL;
	}

	vertex->v = data;
	ret_vertex = list_lookup_next(graph->vertexs, vertex, graph_compare_element);
	memset(vertex, 0x00, sizeof(*vertex));
	free(vertex);
    }

    if (ret_vertex != NULL)
	ret_data = ret_vertex->v;

    errno = GRAPH_SUCCESS;
    return ret_data;
}

int8_t       graph_rem_vert (graph_t *, void **);
int8_t       graph_rem_edge (graph_t *, const void *, const void *);

int32_t      graph_vcount   (graph_t *);
int32_t      graph_ecount   (graph_t *);

int32_t graph_bfs(graph_t * graph, void * start_point) {
    if ((graph == NULL) || (start_point == NULL))
	return GRAPH_ARGS_NULL;

    queue_t * queue = NULL;

    graph_vertex_t * vertex = NULL;
    graph_vertex_t * reset = NULL;
    graph_vertex_t * adj = NULL;

    graph_vertex_t * vertex_tmp = calloc(1, sizeof(*vertex_tmp));

    int32_t longestpath = 0;

    if (vertex_tmp == NULL)
	return GRAPH_FAIL_MALLOC;

    vertex_tmp->v = start_point;

    vertex = list_lookup(graph->vertexs, vertex_tmp, graph_compare_element);

    memset(vertex_tmp, 0x00, sizeof(*vertex_tmp));
    free(vertex_tmp);

    if (vertex == NULL)
	return GRAPH_VERTEX_NOT_FOUND;

    while ((reset = list_lookup_next(graph->vertexs, reset, graph_compare_element)) != NULL) {
	reset->bfs.parent = NULL;
	reset->bfs.status = GRAPH_BFS_NVISITED;
	reset->bfs.distance = 0;
    }

    queue = queue_init();

    if (queue == NULL)
	return GRAPH_FAIL_MALLOC;

    vertex->bfs.status = GRAPH_BFS_VISTED;
    queue_add(queue, vertex);

    printf("------------------------------------------\n");
    printf("Paths from: ");
    graph_print_element(vertex);
    printf("\n------------------------------------------\n");

    while ((vertex = queue_get(queue)) != NULL) {
	adj = NULL;
	while ((adj = list_lookup_next(vertex->adjacents, adj, graph_compare_element)) != NULL) {
	    if (adj->bfs.status == GRAPH_BFS_NVISITED) {
		graph_print_element(adj);
		adj->bfs.parent = vertex;
		adj->bfs.distance = vertex->bfs.distance + 1;
		adj->bfs.status = GRAPH_BFS_VISTED;
		queue_add(queue, adj);

		if (longestpath < adj->bfs.distance)
		    longestpath = adj->bfs.distance;

		printf(" = distance: %d", adj->bfs.distance);
		printf("\n");
	    }
	}
    }

    queue_destroy(&queue, NULL);
    printf("------------------------------------------\n");
    return longestpath;
}

void graph_destroy_element(void ** data) {
    //FIXME: I don't know which approach would be the best one
    // to have access to the data from the first layer (main)
    graph_vertex_t *vertex = (graph_vertex_t *) *data;
    main_destroy(&(vertex->v));
    memset(vertex, 0x00, sizeof(*vertex));
    free(vertex);
    *data = NULL;
}

int32_t graph_compare_element(const void * const data_a, const void * const data_b) {
    //FIXME: I don't know which approach would be the best one
    // to have access to the data from the first layer (main)
    graph_vertex_t * vertex_a = (graph_vertex_t *) data_a;
    graph_vertex_t * vertex_b = (graph_vertex_t *) data_b;
    return main_compare(vertex_a->v, vertex_b->v);
}

void graph_print_element(const void * const data) {
    //FIXME: I don't know which approach would be the best one
    // to have access to the data from the first layer (main)
    graph_vertex_t * vertex = (graph_vertex_t *) data;
    main_print(vertex->v);
}
