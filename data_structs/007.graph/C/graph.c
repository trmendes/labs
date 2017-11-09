#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "main.h"
#include "list.h"
#include "queue.h"
#include "heap.h"
#include "graph.h"

/* Private prototypes */
void    graph_destroy_vertex(void **);
int32_t graph_compare_vertex(const void * const data_a, const void * const data_b);
void    graph_destroy_edge(void **);
int32_t graph_compare_edge(const void * const data_a, const void * const data_b);
void    graph_print_vertex(const void * const data);
void    graph_print_edge(const void * const data);

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

    while ((vertex = list_lookup_next((*graph)->vertexs, vertex, graph_compare_vertex)) != NULL) {
	list_destroy(&(vertex->edges), graph_destroy_edge);
    }

    list_destroy(&((*graph)->vertexs), graph_destroy_vertex);

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
    if (list_lookup(graph->vertexs, new_vertex, graph_compare_vertex) != NULL) {
	memset(new_vertex, 0x00, sizeof(*new_vertex));
	free(new_vertex);
	return GRAPH_VERTEX_EXISTS;
    }

    if (new_vertex == NULL)
	return GRAPH_FAIL_MALLOC;

    new_vertex->edges = list_init();

    if (new_vertex->edges == NULL) {
	memset(new_vertex, 0x00, sizeof(*new_vertex));
	free(new_vertex);
	return GRAPH_FAIL_MALLOC;
    }

    retval = list_ins_next(graph->vertexs, NULL, new_vertex, graph_compare_vertex);

    if (retval != LST_SUCCESS) {
	list_destroy(&(new_vertex->edges), NULL);
	memset(new_vertex, 0x00, sizeof(*new_vertex));
	free(new_vertex);
	return GRAPH_FAIL_MALLOC;
    }

    printf("Add [vert] ");
    graph->api.print(data);
    printf("\n");

    return GRAPH_SUCCESS;
}

int8_t graph_ins_edge(graph_t * graph, const void * data_a, const void * data_b, int32_t cost) {
    if ((graph == NULL) || (data_a == NULL) || (data_b == NULL))
	return GRAPH_ARGS_NULL;

    graph_vertex_t * element_tmp = NULL;
    graph_vertex_t * element_a = NULL;
    graph_vertex_t * element_b = NULL;
    graph_edge_t   * edge = calloc(1, sizeof(*edge));

    element_tmp = calloc(1, sizeof(*element_tmp));
    element_tmp->v = (void *) data_a;

    element_a = list_lookup(graph->vertexs, element_tmp, graph_compare_vertex) ;

    if (element_a == NULL) {
	memset(edge, 0x00, sizeof(*edge));
	free(edge);
	memset(element_tmp, 0x00, sizeof(*element_tmp));
	free(element_tmp);
	return GRAPH_VERTEX_NOT_FOUND;
    }

    element_tmp->v = (void *) data_b;

    element_b = list_lookup(graph->vertexs, element_tmp, graph_compare_vertex);

    memset(element_tmp, 0x00, sizeof(*element_tmp));
    free(element_tmp);

    if (element_b == NULL) {
	memset(edge, 0x00, sizeof(*edge));
	free(edge);
	return GRAPH_VERTEX_NOT_FOUND;
    }

    edge->cost = cost;
    edge->vertex = element_b;
    ++element_b->degree;

    list_ins_next(element_a->edges, NULL, edge, graph_compare_vertex);

    printf("Add [edge] ");
    graph->api.print(data_a);
    printf("-> ");
    graph->api.print(data_b);
    printf("[[Cost] %d ", edge->cost);
    printf("[Degree] %d]\n", element_b->degree);

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
	ret_vertex = list_lookup_next(graph->vertexs, NULL, graph_compare_vertex);
    } else {
	vertex = calloc(1, sizeof(*vertex));

	if (vertex == NULL) {
	    errno = GRAPH_FAIL_MALLOC;
	    return NULL;
	}

	vertex->v = data;
	ret_vertex = list_lookup_next(graph->vertexs, vertex, graph_compare_vertex);
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
    graph_edge_t * edge = NULL;

    graph_vertex_t * vertex_tmp = calloc(1, sizeof(*vertex_tmp));

    int32_t longestpath = 0;

    if (vertex_tmp == NULL)
	return GRAPH_FAIL_MALLOC;

    vertex_tmp->v = start_point;

    vertex = list_lookup(graph->vertexs, vertex_tmp, graph_compare_vertex);

    memset(vertex_tmp, 0x00, sizeof(*vertex_tmp));
    free(vertex_tmp);

    if (vertex == NULL)
	return GRAPH_VERTEX_NOT_FOUND;

    while ((reset = list_lookup_next(graph->vertexs, reset, graph_compare_vertex)) != NULL) {
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
    graph_print_vertex(vertex);
    printf("\n------------------------------------------\n");

    while ((vertex = queue_get(queue)) != NULL) {
	edge = NULL;
	while ((edge = list_lookup_next(vertex->edges, edge, graph_compare_edge)) != NULL) {
	    if (edge->vertex->bfs.status == GRAPH_BFS_NVISITED) {
		graph_print_vertex(edge->vertex);
		edge->vertex->bfs.parent = vertex;
		edge->vertex->bfs.distance = vertex->bfs.distance + 1;
		edge->vertex->bfs.status = GRAPH_BFS_VISTED;
		queue_add(queue, edge->vertex);

		if (longestpath < edge->vertex->bfs.distance)
		    longestpath = edge->vertex->bfs.distance;

		printf(" = distance: %d", edge->vertex->bfs.distance);
		printf("\n");
	    }
	}
    }

    queue_destroy(&queue, NULL);
    printf("------------------------------------------\n");
    return longestpath;
}

void graph_destroy_vertex(void ** data) {
    //FIXME: I don't know which approach would be the best one
    // to have access to the data from the first layer (main)
    graph_vertex_t *vertex = (graph_vertex_t *) *data;
    main_destroy(&(vertex->v));
    memset(vertex, 0x00, sizeof(*vertex));
    free(vertex);
    *data = NULL;
}

int32_t graph_compare_vertex(const void * const data_a, const void * const data_b) {
    //FIXME: I don't know which approach would be the best one
    // to have access to the data from the first layer (main)
    graph_vertex_t * vertex_a = (graph_vertex_t *) data_a;
    graph_vertex_t * vertex_b = (graph_vertex_t *) data_b;
    return main_compare(vertex_a->v, vertex_b->v);
}

void graph_print_vertex(const void * const data) {
    //FIXME: I don't know which approach would be the best one
    // to have access to the data from the first layer (main)
    graph_vertex_t * vertex = (graph_vertex_t *) data;
    main_print(vertex->v);
}

void graph_destroy_edge(void ** data) {
    graph_edge_t * edge_a = (graph_edge_t *) *data;
    memset(edge_a, 0x00, sizeof(*edge_a));
    free(edge_a);
    *data = NULL;
}

int32_t graph_compare_edge(const void * const data_a, const void * const data_b) {
    //FIXME: I don't know which approach would be the best one
    // to have access to the data from the first layer (main)
    graph_edge_t * edge_a = (graph_edge_t *) data_a;
    graph_edge_t * edge_b = (graph_edge_t *) data_b;
    graph_vertex_t * vertex_a = (graph_vertex_t *) edge_a->vertex;
    graph_vertex_t * vertex_b = (graph_vertex_t *) edge_b->vertex;
    return main_compare(vertex_a->v, vertex_b->v);
}

void graph_print_edge(const void * const data) {
    //FIXME: I don't know which approach would be the best one
    // to have access to the data from the first layer (main)
    graph_edge_t * edge = (graph_edge_t *) data;
    graph_vertex_t * vertex = (graph_vertex_t *) edge;
    printf("Cost: %d\n", edge->cost);
    main_print(vertex->v);
}


