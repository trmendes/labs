#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "dvector.h"
#include "trace.h"

#define ARRAYSIZE 18

#define INSERT 100

int32_t main(int32_t argc, char **argv) {
    dvector * v = dv_create(ARRAYSIZE);

    time_t t;
    int32_t i = 0;
    /* Inicializa um gerador de numero randomico */
    srand((unsigned) time(&t));

    dv_print_array_info(v);

    printf("------------------------------------\n");
    printf("\t\tInserindo e Removendo\n");
    printf("------------------------------------\n");
    for (i = 0; i < INSERT; i++) {
	switch (rand() % 4) {
	    case 0:
		dv_insert_head(v, i+1);
		dv_print(v, "(Inserir HEAD): ");
		break;
	    case 1:
		if (dv_remove_head(v) == NO_HEAD) {
		    dv_print(v, "(Remove HEAD): NO HEAD TO REMOVE");
		} else {
		    dv_print(v, "(Remove HEAD): ");
		}
		break;
	    case 2:
		dv_insert_tail(v, i+1);
		dv_print(v, "(Inserir TAIL): ");
		break;
	    case 3:
		if (dv_remove_tail(v) == NO_TAIL) {
		    dv_print(v, "(Remove TAIL): NO TAIL TO REMOVE");
		} else {
		    dv_print(v, "(Remove TAIL): ");
		}
		break;
	}
    }

    return EXIT_SUCCESS;

}
