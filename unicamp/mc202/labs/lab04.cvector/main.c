#include <stdio.h>
#include <stdlib.h>
#include "cvec.h"

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

    cvector_t *baralho = NULL;
    cvector_t *descartadas = NULL;

    while (!feof(ifp)) {
	fscanf(ifp, "%d", &size);
	if (size == 0)
	    break;

	cv_destroy(&baralho);
	cv_destroy(&descartadas);

	baralho = cv_create(size);
	descartadas = cv_create(size);

	for (int i = 0; i < size; i++) {
	    cv_insert(baralho, i + 1);
	}

	while (cv_len(baralho) != 1) {
	    cv_insert(descartadas, cv_get(baralho));
	    cv_insert(baralho, cv_get(baralho));
	}

	printf("Cartas jogadas: ");
	cv_print(descartadas);
	printf("\nCarta restante: ");
	cv_print(baralho);
	printf("\n");

    }

    return EXIT_SUCCESS;
}
