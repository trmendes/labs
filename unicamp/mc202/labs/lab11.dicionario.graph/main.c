#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "graph.h"

int32_t main() {
    char word[BUFMAX];
    data_t * data_vertex_a = NULL;
    data_t * data_vertex_b = NULL;
    data_t * vertex = NULL;
    int32_t ret, hops = 0, hops_tmp = 0;
    size_t i;
    int8_t swaps;

    graph_t * dic = graph_init(main_print);

    while (1) {

	ret = scanf("%s ", word);

	if (ret == EOF)
	    break;

	data_vertex_a = calloc(1, sizeof(*data_vertex_a));
	data_vertex_a->word_size = strlen(word);
	strncpy(data_vertex_a->word, word, sizeof(data_vertex_a->word));

	if (graph_ins_vert(dic, data_vertex_a) == GRAPH_SUCCESS) {
	    data_vertex_b = NULL;
	    while ((data_vertex_b = graph_lookup_next_vertex(dic, data_vertex_b)) != NULL) {
		swaps = 0;
		if (data_vertex_b->word_size == strlen(word)) {
		    for (i = 0; i < strlen(word); ++i) {
			if (data_vertex_b->word[i] != word[i])
			    ++swaps;
			if (swaps > 1)
			    break;
		    }
		}
		if (swaps == 1) {
		    graph_ins_edge(dic, data_vertex_a, data_vertex_b);
		    graph_ins_edge(dic, data_vertex_b, data_vertex_a);
		}
	    }
	} else {
	    memset(data_vertex_a, 0x00, sizeof(*data_vertex_a));
	    free(data_vertex_a);
	}
    }

    vertex = NULL;
    while ((vertex = graph_lookup_next_vertex(dic, vertex)) != NULL) {
	hops_tmp = graph_bfs(dic, vertex);
	if (hops_tmp > hops)
	    hops = hops_tmp;
    }

    printf("%d\n", hops);
    graph_destroy(&dic);

    return EXIT_SUCCESS;
}

int32_t main_compare(const void * const key1, const void * const key2) {
    data_t * a = (data_t *)key1;
    data_t * b = (data_t *)key2;
    return strcmp(a->word, b->word);
}

void main_destroy(void **data) {
    data_t *tmp = (data_t *) *data;
    /* printf("Removed: %s [destroy]\n", tmp->word); */
    memset(tmp, 0x00, sizeof(*tmp));
    free(tmp);
    *data = NULL;
}

void main_print(const void * const data) {
    data_t * tmp = (data_t *) data;
    printf("%s ", tmp->word);
}
