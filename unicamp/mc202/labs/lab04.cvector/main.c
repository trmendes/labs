#include <stdio.h>
#include <stdlib.h>
#include "cvec.h"

int main(int argc, char **argv) {

    int size = 1, i = 0;

    cvector_t *baralho = NULL;
    cvector_t *descartadas = NULL;

    while (size > 0) {
	scanf("%d", &size);
	if (size == 0)
	    break;

	cv_destroy(&baralho);
	cv_destroy(&descartadas);

	baralho = cv_create(size);
	descartadas = cv_create(size);

	for (i = 0; i < size; i++) {
	    cv_insert(baralho, i + 1);
	}

	while (cv_len(baralho) != 1) {
	    cv_insert(descartadas, cv_get(baralho));
	    cv_insert(baralho, cv_get(baralho));
	}

	cv_print(descartadas, "Cartas jogadas:");
	cv_print(baralho, "Carta restante:");
    }

    cv_destroy(&baralho);
    cv_destroy(&descartadas);

    return EXIT_SUCCESS;
}
