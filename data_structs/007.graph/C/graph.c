#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "list.h"
#include "graph.h"

/* Private prototypes */
void graph_destroy_element(void **);

graph_t * graph_init(compare_ft compare, destroy_ft destroy, print_ft print) {
    if ((compare == NULL) || (destroy == NULL)) {
	errno = GRAPH_ARGS_NULL;
	return (graph_t *) NULL;
    }

    graph_t * graph = (graph_t *) calloc(1, sizeof(graph_t));

    if (graph == (graph_t *) NULL) {
	errno = GRAPH_FAIL_MALLOC;
	return (graph_t *) NULL;
    }

    graph->adjacents = list_init(destroy, compare, NULL);

    if (graph->adjacents == (list_t *) NULL) {
	memset(graph, 0x00, sizeof(graph_t));
	free(graph);
	errno = GRAPH_FAIL_MALLOC;
	return (graph_t *) NULL;
    }

    graph->compare = compare;
    graph->destroy = destroy;
    graph->print = print;

    errno = GRAPH_SUCCESS;
    return graph;
}

void graph_destroy(graph_t ** graph) {
    if (*graph == (graph_t *) NULL) {
	errno = GRAPH_ARGS_NULL;
	return;
    }

    graph_adj_t * element = (graph_adj_t *) NULL;

    while (1) {
	    list_rem_next((void *) ((*graph)->adjacents), NULL, (const void **) &element);
	    if (element == (graph_adj_t *) NULL)
		break;
	    while (1) {
		list_rem_next((void *) *graph, NULL, (const void **) &element);

	    }
    }
}

void graph_destroy_element(void ** data) {
    if (*data == (void *) NULL) {
	errno = GRAPH_ARGS_NULL;
	return;
    }

    graph_adj_t * element = (graph_adj_t *) *data;

    memset(element, 0x00, sizeof(graph_adj_t));
    free(element);
    *data = NULL;
}

int8_t graph_ins_vert(graph_t * graph, const void * data) {
    if ((graph == (graph_t *) NULL) || (data == (void *) NULL))
	return GRAPH_ARGS_NULL;

    node * element = (node *) NULL;
    int8_t retval;

    element = list_find_element(graph->adjacents, data);

    /* We do not allow repeated elements */
    if (element != (node *) NULL)
	return GRAPH_VERTEX_EXISTS;

    graph_adj_t * adj_element = (graph_adj_t *) calloc(1, sizeof(graph_adj_t));

    if (adj_element == (graph_adj_t *) NULL)
	return GRAPH_ARGS_NULL;

    adj_element->v = (void *) data;
    adj_element->adjacents = list_init(graph->destroy, graph->compare, NULL);

    if (adj_element->adjacents == NULL) {
	memset(adj_element, 0x00, sizeof(graph_adj_t));
	free(adj_element);
	return GRAPH_FAIL_MALLOC;
    }

    retval = list_ins_next(graph->adjacents, NULL, adj_element);

    if (retval != LST_SUCCESS) {
	memset(adj_element, 0x00, sizeof(graph_adj_t));
	free(adj_element);
	return GRAPH_FAIL_MALLOC;
    }

    ++graph->vcounter;

    printf("Adicionando Vertice %d -- [LEN: %ld]\n", *((int32_t *) data), graph->vcounter);

    return GRAPH_SUCCESS;
}

int8_t graph_ins_edge(graph_t * graph, const void * dataA, const void * dataB) {
    if ((graph == (graph_t *) NULL) || (dataA == (void *) NULL) || (dataB == (void *) NULL))
	return GRAPH_ARGS_NULL;

    int8_t retval;

    node * element_node = (node *) NULL;

    graph_adj_t * elementA = (graph_adj_t *) NULL;
    graph_adj_t * elementB = (graph_adj_t *) NULL;

    /* We are using elementB here as temp variable
     * latter on we will use it to hold the value of
     * dataB as it should (saving memory) */
    elementB = (graph_adj_t *) calloc(1, sizeof(graph_adj_t));
    elementB->v = (void *) dataA;

    element_node = list_find_element(graph->adjacents, elementB) ;

    if (element_node == (node *) NULL) {
	memset(elementB, 0x00, sizeof(graph_adj_t));
	free(elementB);
	return GRAPH_VERTEX_NOT_FOUND;
    }

    elementB->v = (void *) dataB;

    if (list_find_element(graph->adjacents, elementB) == (node *) NULL) {
	memset(elementB, 0x00, sizeof(graph_adj_t));
	free(elementB);
	return GRAPH_VERTEX_NOT_FOUND;
    }

    elementA = (graph_adj_t *) element_node->data;

    retval = list_ins_next(elementA->adjacents, NULL, elementB);

    if (retval != LST_SUCCESS) {
	memset(elementB, 0x00, sizeof(graph_adj_t));
	free(elementB);
	return GRAPH_FAIL_MALLOC;
    }

    ++graph->ecounter;

    printf("Adicionando aresta entre %d e %d-- [LEN: %ld]\n", *((int32_t *) dataA), *((int32_t *) dataB), graph->ecounter);

    return GRAPH_SUCCESS;
}

int8_t       graph_rem_vert (graph_t *, void **);
int8_t       graph_rem_edge (graph_t *, const void *, const void *);

int32_t      graph_vcount   (graph_t *);
int32_t      graph_ecount   (graph_t *);


