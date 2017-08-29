#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define NELEMENTS 10

int main(int argc, char **argv) {
    queue_t *q = qe_create();
    for (int i = 0; i < NELEMENTS; i++) {
	node_t * element = calloc(1, sizeof(node_t));
	element->id = i + 1;
	qe_insert(q, element);
    }
    qe_print(q);
    for (int i = 0; i < NELEMENTS / 2; i++) {
	node_t * element = qe_get(q);
	printf("get %d\n", element->id);
	free(element);
    }
    qe_print(q);
    return EXIT_SUCCESS;
}
