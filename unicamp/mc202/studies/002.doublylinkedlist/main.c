#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "dllist.h"
#include "trace.h"

#define ELEMENTS 6

int32_t main(int32_t argc, char **argv) {
    int32_t i, iindex;
    time_t t;
    /* Inicializa um gerador de numero randomico */
    srand((unsigned) time(&t));


    dllist *l1 = dl_create();

    printf("------------------------------------\n");
    printf("\t\tInserindo\n");
    printf("------------------------------------\n");
    for (i = 0; i < ELEMENTS; i++) {
	switch (1) {
	    case 0:
		printf("--> Inserindo no fim da fila\n");
		break;
	    case 1:
		printf("--> Inserindo no inicio da fila\n");
		dl_insert_beginning(l1, i);
		break;
	    case 2:
		iindex = rand() % i;
		printf("--> Inserindo depois de %d\n", iindex);
		dl_insert_after(l1, iindex, i);
		break;
	    case 3:
		iindex = rand() % i;
		printf("--> Inserindo antes de %d\n", iindex);
		dl_insert_before(l1, iindex, i);
		break;
	}
    }

    node *teste = dl_get_index(l1, 2);
    printf("INDEX %d, DATA %d\n", teste->id, teste->data);

    return SUCCESS;

    printf("------------------------------------\n");
    printf("\t\tRemovendo\n");
    printf("------------------------------------\n");
    for (i = 0; i < ELEMENTS+10; i++) {
	switch (1) {
	    case 0:
		printf("--> Removendo do Inicio da lista\n");
		dl_remove_beginning(l1);
		break;
	    case 1:
		printf("--> Removendo do fim da lista\n");
		dl_remove_end(l1);
		break;
	}
    }
    printf("------------------------------------\n");
    printf("\t\tDestruindo\n");
    printf("------------------------------------\n");


    dl_destroy(&l1);
}


