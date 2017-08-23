#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "dvector.h"
#include "trace.h"

#define ARRAYSIZE 6

#define INSERT 14

int32_t main(int32_t argc, char **argv) {
    dvector * v = dv_create(ARRAYSIZE);
    
    time_t t;
    int32_t i = 0;
    /* Inicializa um gerador de numero randomico */
    srand((unsigned) time(&t));

    dv_print_array_info(v);

    printf("------------------------------------\n");
    printf("\t\tInserindo\n");
    printf("------------------------------------\n");
    for (i = 0; i < INSERT; i++) {
	switch (rand() %2) {
	    case 0:
		dv_insert_head(v, i+1);
		dv_print(v, "(Inserir HEAD): ");
		break;
	    case 1:
		dv_insert_tail(v, i+1);
		dv_print(v, "(Inserir TAIL): ");
		break;
	}
    }

    return EXIT_SUCCESS;

}
