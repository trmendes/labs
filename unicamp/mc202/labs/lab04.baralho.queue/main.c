#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, char **argv) {

    FILE *ifp;
    int size;

    if (argc < 2) {
	printf("Eh necessario especificar o arquivo para o teste\n");
	return EXIT_FAILURE;
    }

    ifp = fopen(argv[1], "r");

    if (ifp == NULL) {
	fprintf(stderr, "Nao consegui abrir o arquivo!\n");
	exit(1);
    }

    queue_t *baralho = qe_create();
    queue_t *descartadas = qe_create();

    while (!feof(ifp)) {
	fscanf(ifp, "%d", &size);
	if (size == 0)
	    break;

	qe_destroy(baralho);
	qe_destroy(descartadas);

	for (int i = 0; i < size; i++) {
	    node_t * carta = calloc(1, sizeof(node_t));
	    carta->id = i + 1;
	    qe_insert(baralho, carta);
	}

	while (qe_len(baralho) != 1) {
	    qe_insert(descartadas, qe_get(baralho));
	    qe_insert(baralho, qe_get(baralho));
	}

	printf("Cartas jogadas: ");
	qe_print(descartadas);
	printf("\nCarta restante: ");
	qe_print(baralho);
	printf("\n");

    }

    return EXIT_SUCCESS;
}
